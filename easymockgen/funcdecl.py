# Copyright (c) 2014, Alexander Korobeynikov
# https://github.com/alveko/easymock
# License: BSD

import os, re, sys
from collections import namedtuple

sys.path.extend(['/ericsson/tools/pycparser'])
from pycparser import c_parser, c_ast, parse_file, c_generator

FuncDecl = namedtuple('FuncDecl',
                      [ 'name', 'return_type', 'void', 'nonvoid',
                        'params', 'vargs', 'wrap', 'full_decl', 'file_line' ])

FuncParam = namedtuple('FuncParam',
                       [ 'name', 'type', 'type_nonconst', 'type_name',
                         'type_name_nonconst', 'type_basic' ])

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

        self.savefuncs = False
        self.visit(self.ast)

        self.savefuncs = True
        self.visit(self.ast)

    def fix_pointer_spaces(self, code):
        code = re.sub(r" +\*", r"*", code)
        code = re.sub(r"\*([^\* ])", r"* \1", code)
        return code

    def typename_to_type(self, typename, name):
        # remove array endings: type var[] -> type* var
        t, tprev = typename, ""
        while t != tprev:
            tprev = t
            t = re.sub(r"^(.+) " + name + r"(.*)\[\]$",
                       r"\1* " + name + r"\2", tprev)
        # remove parameter name
        t = re.sub(r"^(.+[^\w])" + name, r"\1", t).strip()
        return t

    def put_type(self, tname, ttype, overwrite=True):
        if not tname in self.typedefs or overwrite:
            self.typedefs[tname] = ttype

    def get_type(self, tname):
        if tname in self.typedefs:
            return self.typedefs[tname]
        else:
            return tname

    def type_to_basic_type(self, type):
        # remove all "const" from the type
        type = re.sub(r"\bconst\b", r"", type)
        type = re.sub(r"\s+", r" ", type).strip()

        # translate into basic type
        def typerepl(m):
            return self.get_type(m.group(1))

        type = re.sub(r"(struct \w+)", typerepl, type)
        type = re.sub(r"(union \w+)", typerepl, type)
        type = re.sub(r"(\w+)", typerepl, type)

        if "(*" in type:
            type = "function*"
        # fix pointers and return
        return self.fix_pointer_spaces(type)

    def visit_NS(self, node, ns):
        stype = ("custom_" if node.decls else "opaque_") + ns
        if node.name:
            sname = ns + " " + node.name
            self.put_type(sname, stype, node.decls)
            return self.get_type(sname)
        else:
            return stype

    def visit_Struct(self, node):
        return self.visit_NS(node, "struct")

    def visit_Union(self, node):
        return self.visit_NS(node, "union")

    def visit_Typedef(self, node):
        self.generic_visit(node)

        def resolve_typedecl(node):
            if isinstance(node.type, c_ast.Struct):
                return self.visit_Struct(node.type)
            elif isinstance(node.type, c_ast.Union):
                return self.visit_Union(node.type)
            elif isinstance(node.type, c_ast.Enum):
                return "int"
            else:
                return self.get_type(self.cgen.visit(node.type))

        if isinstance(node.type, c_ast.TypeDecl):
            self.put_type(node.name, resolve_typedecl(node.type))

        elif isinstance(node.type, c_ast.PtrDecl) and \
             isinstance(node.type.type, c_ast.TypeDecl):
            self.put_type(node.name, resolve_typedecl(node.type.type) + "*")

        else:
            self.put_type(node.name, "unresolved")

    def visit_Decl(self, node):
        self.generic_visit(node)
        if isinstance(node.type, c_ast.FuncDecl) and self.savefuncs:
            self.handle_FuncDecl(node)

    def handle_FuncDecl(self, node):
        func_name = node.name

        cond_func = (not self.args.func and not self.args.func_pfx or
                     func_name in self.args.func or
                     [ pfx for pfx in self.args.func_pfx
                       if func_name.startswith(pfx) ] )

        cond_wrap = (func_name in self.args.wrap or self.args.wrap_all or
                    [ pfx for pfx in self.args.wrap_pfx
                      if func_name.startswith(pfx) ] )

        cond_file = (self.args.include_all or
                     os.path.basename(node.coord.file) in self.args.include or
                     os.path.basename(node.coord.file) == self.filename)

        if (cond_file and (cond_func or cond_wrap)):

            # get rid of possible "extern" qualifiers
            node.storage = []

            file_line = str(node.coord.file) + ":" + str(node.coord.line)
            type_name = self.fix_pointer_spaces(self.cgen.visit_Typename(node.type))
            rtrn_type = self.typename_to_type(type_name, func_name)
            full_decl = self.fix_pointer_spaces(self.cgen.visit_Decl(node))
            full_decl = re.sub(r"([\(,])\s*", r"\1\n    ", full_decl)

            print("Function found: %s" % (func_name))
            func = FuncDecl(name        = func_name,
                            return_type = rtrn_type,
                            void        = (rtrn_type == 'void'),
                            nonvoid     = (rtrn_type != 'void'),
                            params      = [],
                            vargs       = ("..." in full_decl),
                            wrap        = cond_wrap,
                            full_decl   = full_decl,
                            file_line   = file_line)
            self.funcdecls.append(func)

            if node.type.args:
                for i, param in enumerate(node.type.args.params):

                    ptype_name = self.fix_pointer_spaces(self.cgen.visit(param))
                    if (hasattr(param, 'type') and \
                        hasattr(param.type, 'quals') and 'const' in param.type.quals):
                        param.type.quals.remove('const')
                    ptype_name_nonconst = \
                        self.fix_pointer_spaces(self.cgen.visit(param))

                    pname = ""
                    if isinstance(param, c_ast.Decl):
                        pname = param.name
                    if isinstance(param, c_ast.Typename) and ptype_name != 'void':
                        # name omitted in declaration
                        pname = "_em_param%d" % (i + 1)
                        ptype_name += " " + pname

                    if pname:
                        ptype          = self.typename_to_type(ptype_name, pname)
                        ptype_nonconst = self.typename_to_type(ptype_name_nonconst, pname)
                        ptype_basic    = self.type_to_basic_type(ptype)
                        if ptype_basic != "function*":
                            ptype_name_nonconst="%s %s" % (ptype_nonconst, pname)

                        fp = FuncParam(name = pname, type = ptype,
                                       type_nonconst      = ptype_nonconst,
                                       type_name          = ptype_name,
                                       type_name_nonconst = ptype_name_nonconst,
                                       type_basic         = ptype_basic)
                        func.params.append(fp)
