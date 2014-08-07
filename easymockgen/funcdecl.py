import os
import re
from collections import namedtuple
import sys

sys.path.extend(['/ericsson/tools/pycparser'])
from pycparser import c_parser, c_ast, parse_file, c_generator

FuncDecl = namedtuple('FuncDecl', [ 'name', 'return_type',
                                    'void', 'nonvoid', 'params', 'wrap',
                                    'full_decl', 'file_line' ])

FuncParam = namedtuple('FuncParam', [ 'name',
                                      'type', 'type_nonconst',
                                      'type_name', 'type_name_nonconst',
                                      'type_basic' ])

class FuncDeclVisitor(c_ast.NodeVisitor):

    def __init__(self, args):
        self.args = args
        self.filename = ""
        self.filebase = ""
        self.funcdecls = []
        self.ast = None
        self.typedefs = {}
        self.cgen = c_generator.CGenerator()

    def parse(self, fileprep):
        self.funcdecls = []
        self.fileprep = fileprep
        self.filename = re.sub(r"(\w+.[ch]).*$", r"\1",
                               os.path.basename(fileprep))

        # parse and visit functions
        self.ast = parse_file(self.fileprep)
        super(FuncDeclVisitor, self).visit(self.ast)

    def fix_pointer_spaces(self, code):
        code = re.sub(r" \*", r"*", code)
        code = re.sub(r"\*([^\*])", r"* \1", code)
        return code

    def typename_to_type(self, typename, name):
        # remove array endings: type var[] -> type* var
        t, tprev = typename, ""
        while t != tprev:
            tprev = t
            t = re.sub(r"^(.+) " + name + r"(.*)\[\]$",
                       r"\1*" + name + r"\2", tprev)
        # remove parameter name
        t = re.sub(r"^(.+[^\w])" + name, r"\1", t).strip()
        return t

    def type_to_nonconst_type(self, type):
        # remove const qualifier from the beginning
        return re.sub(r"^\s*const\s+", r"", type)

    def type_to_basic_type(self, type):
        # remove const if any
        type = self.type_to_nonconst_type(type)
        # translate into basic type
        def typerepl(m):
            t = m.group(1)
            t = self.typedefs[t] if t in self.typedefs else t
            return t
        type = re.sub(r"(\w+)", typerepl, type)
        if "(*" in type:
            type = "custom_func*"
        # fix pointers and return
        return self.fix_pointer_spaces(type)

    def visit_Typedef(self, node):
        m = re.match(r"^typedef (.+[^\w])" + node.name + r"$",
                     self.cgen.visit_Typedef(node), re.DOTALL)
        if m:
            tp = m.group(1).strip()
            if tp.startswith("struct"):
                self.typedefs[node.name] = "custom_struct"
            elif tp.startswith("union"):
                self.typedefs[node.name] = "custom_union"
            elif tp.startswith("enum"):
                self.typedefs[node.name] = "int"
            else:
                self.typedefs[node.name] = self.type_to_basic_type(tp)
        elif type(node.type) is c_ast.PtrDecl and \
             type(node.type.type) is c_ast.FuncDecl:
            self.typedefs[node.name] = "custom_func*"
        elif type(node.type) is c_ast.FuncDecl:
            self.typedefs[node.name] = "custom_func_notptr"
        elif type(node.type) is c_ast.ArrayDecl:
            self.typedefs[node.name] = "custom_array*"
        else:
            self.typedefs[node.name] = "unknown"

    def visit_Decl(self, node):

        is_funcdelc = (isinstance(node.type, c_ast.FuncDecl) and
                       self.filename in node.coord.file)
        is_wrap = (node.name in self.args.wrap)
        is_func = (node.name in self.args.func or not self.args.func)

        if (is_funcdelc and (is_func or is_wrap)):
            # get rid of possible "extern" qualifiers
            node.storage = []
            cgen = c_generator.CGenerator()
            node_funcdecl = node.type

            type_name = self.fix_pointer_spaces(cgen.visit_Typename(node_funcdecl))
            rtype = self.typename_to_type(type_name, node.name)
            tvoid = (rtype == 'void')
            fdecl = self.fix_pointer_spaces(cgen.visit_Decl(node))
            fdecl = re.sub(r"([\(,])\s*", r"\1\n    ", fdecl)

            if "..." in fdecl:
                print("Function ignored (va lists not supported): %s" % (node.name))
                return

            print("Function found: %s" % (node.name))
            func = FuncDecl(name=node.name,
                            return_type=rtype,
                            void=tvoid,
                            nonvoid=(not tvoid),
                            params=[],
                            wrap=(self.args.wrap_all or is_wrap),
                            full_decl=fdecl,
                            file_line=str(node.coord.file) + ":" + str(node.coord.line))
            self.funcdecls.append(func)

            if node_funcdecl.args:
                for i, param in enumerate(node_funcdecl.args.params):
                    type_name = self.fix_pointer_spaces(cgen.visit(param))
                    if type_name != 'void':
                        pname = param.name
                        ptype = self.typename_to_type(type_name, param.name)

                        type_nonconst=self.type_to_nonconst_type(ptype)
                        type_basic=self.type_to_basic_type(ptype)

                        if type_basic != "custom_func*":
                            type_name_nonconst="%s %s" % (type_nonconst, pname)
                        else:
                            type_name_nonconst=type_name

                        fp = FuncParam(name=pname,
                                       type=ptype,
                                       type_nonconst=type_nonconst,
                                       type_name=type_name,
                                       type_name_nonconst=type_name_nonconst,
                                       type_basic=type_basic)
                        func.params.append(fp)
