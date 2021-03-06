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
                self.header_file = os.path.basename(header)

                # try to locate the header in -I paths
                if not os.path.isfile(self.header_orig):
                    for x in os.environ.get('EASYMOCK_CFLAGS').split():
                        if x.startswith("-I"):
                            inc_header = "%s/%s" % (x[2:], header)
                            if os.path.isfile(inc_header):
                                self.header_orig = inc_header
                                self.header_file = header
                if not os.path.isfile(self.header_orig):
                    raise Exception("ERROR: Cannot read: %s" % self.header_orig)

                self.header_prep = self.header_orig
                self.header_name = re.sub(r"\.[\w]+$", r"", self.header_file)
                self.header_name = re.sub(r"/", r"_", self.header_name)
                self.filemock_h = ("mock_%s.h") % (self.header_name)
                self.filemock_c = ("mock_%s.c") % (self.header_name)
                self.tempdir = tempfile.mkdtemp(prefix='easymock.')
                self.mockh = None
                self.mockc = None

            def run_system(self, cmd):
                print(cmd)
                rc = os.system(cmd)
                if rc != 0:
                    raise Exception("ERROR: Command failed: %s" % cmd)

            def preprocess(self):
                if self.args.no_preprocess:
                    return
                gcc = os.environ.get('EASYMOCK_GCC')
                cflags = os.environ.get('EASYMOCK_CFLAGS')
                self.header_prep = \
                    "%s/%s" % (self.tempdir, os.path.basename(self.header_file))
                incext = os.path.realpath(os.path.dirname(__file__) +
                                          "/../src/easymock_ext.h")

                print("\n=== Preprocessing header : %s" % self.header_orig)
                print("EASYMOCK_GCC = %s" % gcc)
                print("EASYMOCK_CFLAGS = %s" % cflags)

                self.run_system("%s %s -include %s -E %s -o %s" % \
                                (gcc, cflags, incext,
                                 self.header_orig, self.header_prep))
                print("Preprocessed header : %s" % self.header_prep)

            def generate(self):
                print("=== Generating mocks for %s" % self.header_file)
                cwd_stored = os.getcwd()
                scriptdir = os.path.dirname(os.path.realpath(__file__))

                print("Parsing file...")
                os.chdir(self.tempdir)
                fdv = FuncDeclVisitor(self.args)
                fdv.parse(os.path.realpath(self.header_prep))

                if self.args.print_ast:
                    # pprint(v.funcdecls)
                    fdv.ast.show(attrnames=True, nodenames=True)

                if fdv.funcdecls:
                    HFile = collections.namedtuple(
                        'File', ['name', 'incl', 'funcs'])
                    file = HFile(name=self.header_name,
                                 incl=self.header_file,
                                 funcs=fdv.funcdecls)
                    os.chdir(scriptdir + "/../tmpl")
                    print("Generating %s" % (self.filemock_h))
                    self.mockh = Template("file.h.tmpl")
                    self.mockh.render({'file': file})
                    print("Generating %s" % (self.filemock_c))
                    self.mockc = Template("file.c.tmpl")
                    self.mockc.render({'file': file})
                else:
                    print("No function declarations found in %s" % (self.header_file))

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

    parser.add_argument('--func', metavar='FUNC', type=str,
                        action='append', default=[],
                        help='create a mock for a function named FUNC')

    parser.add_argument('--func-pfx', metavar='FPFX', type=str,
                        action='append', default=[],
                        help='create mocks for functions named\n'
                        'with the prefix FPFX*')

    parser.add_argument('--func-all', action='store_true',
                        help='create mocks for all functions (default)')

    parser.add_argument('--wrap', metavar='FUNC', type=str,
                        action='append', default=[],
                        help='create __wrap_FUNC mock for a function named FUNC')

    parser.add_argument('--wrap-pfx', metavar='WPFX', type=str,
                        action='append', default=[],
                        help='create __wrap_* mocks for functions\n'
                        'named with the prefix WPFX*')

    parser.add_argument('--wrap-all', action='store_true',
                        help='create __wrap_* mocks for all functions')

    parser.add_argument('--include', metavar='INCHDR', type=str,
                        action='append', default=[],
                        help='generate mocks for functions defined\n'
                        'in the included header INCHDR')

    parser.add_argument('--include-all', action='store_true',
                        help='generate mocks for functions defined\n'
                        'in all included headers')

    parser.add_argument('-o', '--outdir', metavar='DIR',
                        action=writable_dir, default='.',
                        help='output directory (by default "%(default)s" is used)')

    parser.add_argument('--add-func-pfx', metavar='PFX', type=str, default='',
                        help='Add PFX to the names of mock functions generated')

    #parser.add_argument('--add-file-pfx', metavar='PFX', type=str, default='',
    #                    help='Add PFX to the names of files generated')

    parser.add_argument('--no-preprocess', action='store_true',
                        help=argparse.SUPPRESS)

    parser.add_argument('--no-rm', action='store_true',
                        help=argparse.SUPPRESS)

    parser.add_argument('-a', '--print-ast', action='store_true',
                        help=argparse.SUPPRESS)

    parser.add_argument('header', type=str, nargs='+', default=[],
                        help='A header file(s) to generate mocks for')

    args = parser.parse_args()

    if (not args.no_preprocess and
        (not os.environ.get('EASYMOCK_GCC') or
         not os.environ.get('EASYMOCK_CFLAGS'))):
        print("EASYMOCK_GCC and/or EASYMOCK_CFLAGS are not set!")
        parser.print_help()
        exit(1)

    for header in args.header:
        with EasyMockGenResourse(args, header) as emg:
            emg.preprocess()
            emg.generate()
            emg.save()
