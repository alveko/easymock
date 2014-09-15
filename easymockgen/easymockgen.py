#!/usr/bin/env python
# Copyright (c) 2014, Alexander Korobeynikov
# https://github.com/alveko/easymock
# License: BSD

import sys, os, re, collections, argparse
import tempfile, shutil

from template import Template
from funcdecl import FuncDecl, FuncParam, FuncDeclVisitor

class EasyMockGenResourse:
    def __init__(self, args, header):
        self.args = args
        self.header = header

    def __enter__(self):

        class EasyMockGen:
            def __init__(self, args, header):
                self.args = args
                self.header_orig = header
                self.header_prep = header
                self.header_base = os.path.basename(header)
                self.header_name = re.sub(r"\.[\w]+$", r"", self.header_base)
                self.filemock_h = ("mock_%s.h") % (self.header_name)
                self.filemock_c = ("mock_%s.c") % (self.header_name)
                self.tempdir = tempfile.mkdtemp(prefix='easymock.')
                self.mockh = None
                self.mockc = None
                pass

            def run_system(self, cmd):
                print(cmd)
                rc = os.system(cmd)
                if rc != 0:
                    raise Exception("ERROR: Command failed: %s" % cmd)

            def preprocess(self):
                if self.args.no_preprocess:
                    return
                print("\n=== Preprocessing header : %s" % self.header_orig)
                gcc = os.environ.get('EASYMOCK_GCC')
                cflags = os.environ.get('EASYMOCK_CFLAGS')
                print("EASYMOCK_GCC = %s" % gcc)
                print("EASYMOCK_CFLAGS = %s" % cflags)

                self.header_prep = ("%s/%s") % (self.tempdir, self.header_base)
                header_temp = ("%s/%s.temp") % (self.tempdir, self.header_base)

                self.run_system("%s %s -E %s -o %s" % \
                                (gcc, cflags, self.header_orig, header_temp))

                sedcmd = ("sed "
                          "-e 's/__attribute__[^(]*((*[^)]*))*//g' "
                          "-e 's/__asm__[^(]*((*[^)]*))*//g' "
                          "-e 's/__asm__//g' "
                          "-e 's/__extension__//g' "
                          "-e 's/__inline__//g' "
                          "-e 's/__inline//g' "
                          "-e 's/__const /const /g' "
                          "-e 's/__restrict //g' "
                          "-e 's/__restrict$//g' "
                          "-e 's/__restrict,/,/g' "
                          "-e 's/__builtin_va_list/int/g' "
                          "%s > %s ")

                self.run_system(sedcmd % (header_temp, self.header_prep))
                print("Preprocessed header : %s" % self.header_prep)

            def generate(self):
                print("=== Generating mocks for %s" % self.header_base)
                header_prep_full = os.path.realpath(self.header_prep)
                cwd_stored = os.getcwd()
                scriptdir = os.path.dirname(os.path.realpath(__file__))

                print("Parsing file...")
                os.chdir(self.tempdir)
                fdv = FuncDeclVisitor(self.args)
                fdv.parse(header_prep_full)

                if self.args.print_ast:
                    # pprint(v.funcdecls)
                    fdv.ast.show(attrnames=True, nodenames=True)

                if fdv.funcdecls:
                    HFile = collections.namedtuple('File', ['name', 'funcs'])
                    file = HFile(name=self.header_base, funcs=fdv.funcdecls)
                    os.chdir(scriptdir + "/../templates")
                    print("Generating %s" % (self.filemock_h))
                    self.mockh = Template("file.h.templ")
                    self.mockh.render({'file': file})
                    print("Generating %s" % (self.filemock_c))
                    self.mockc = Template("file.c.templ")
                    self.mockc.render({'file': file})
                else:
                    print("No function declarations found in %s" % (self.header_base))

                # restore cwd
                os.chdir(cwd_stored)

            def save(self):
                if self.mockh and self.mockc:
                    mockh_file = "%s/%s" % (self.args.outdir, self.filemock_h)
                    mockc_file = "%s/%s" % (self.args.outdir, self.filemock_c)
                    print("Saving %s" % os.path.realpath(mockh_file))
                    self.mockh.save(mockh_file)
                    print("Saving %s" % os.path.realpath(mockc_file))
                    self.mockc.save(mockc_file)

            def cleanup(self):
                if self.tempdir and not self.args.no_rm:
                    shutil.rmtree(self.tempdir)

        self.emg = EasyMockGen(self.args, self.header)
        return self.emg

    def __exit__(self, type, value, traceback):
        self.emg.cleanup()

class writable_dir(argparse.Action):
    def __call__(self,parser, namespace, values, option_string=None):
        dir=values
        if not os.path.isdir(dir):
            raise argparse.ArgumentError(self, "directory not found: {}".format(dir))
        if os.access(dir, os.R_OK|os.W_OK):
            setattr(namespace,self.dest,dir)
        else:
            raise argparse.ArgumentError(
                self, "cannot write to the direcotry: {}".format(dir))

#!
#! Main
#!

epilog = \
"""
Environment variables:
    EASYMOCK_GCC        Full path to a working GCC compiler
    EASYMOCK_CFLAGS     GCC CFLAGS (for example, -I<path_to_header>)

    PYTHONPATH          Python search path(s) for modules
                        (in addition to system locations).
                        If pycparser is not installed in the system,
                        the path to pycparser must be specified in PYTHONPATH.
"""

if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        description='Generates easymocks',
        epilog=epilog,
        formatter_class=argparse.RawTextHelpFormatter)

    parser.add_argument('-f', '--func', metavar='FUNC', type=str,
                        action='append', default=[],
                        help='generate a mock for a function named FUNC')

    parser.add_argument('-w', '--wrap', metavar='FUNC', type=str,
                        action='append', default=[],
                        help='create __wrap_FUNC mock for a function named FUNC')

    parser.add_argument('-W', '--wrap-all', action='store_true',
                        help='create __wrap_* mocks for all functions')

    parser.add_argument('-o', '--outdir', metavar='DIR',
                        action=writable_dir, default='.',
                        help='output directory (by default "%(default)s" is used)')

    parser.add_argument('--no-preprocess', action='store_true',
                        help=argparse.SUPPRESS)

    parser.add_argument('--no-rm', action='store_true',
                        help=argparse.SUPPRESS)

    parser.add_argument('-a', '--print-ast', action='store_true',
                        help=argparse.SUPPRESS)

    parser.add_argument('headers', type=argparse.FileType(mode='r'), nargs='+',
                        help='A header file(s) to generate mocks for')

    args = parser.parse_args()

    if (not args.no_preprocess and
        (not os.environ.get('EASYMOCK_GCC') or
         not os.environ.get('EASYMOCK_CFLAGS'))):
        print("EASYMOCK_GCC and/or EASYMOCK_CFLAGS are not set!")
        parser.print_help()
        exit(1)

    for header in args.headers:
        with EasyMockGenResourse(args, header.name) as emg:
            emg.preprocess()
            emg.generate()
            emg.save()
