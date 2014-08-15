easymock
========

Mock generator for C

    usage: easymockgen.py [-h] [-f FUNC] [-w FUNC] [-W] [-o DIR]
                          headers [headers ...]
    
    Generates easymocks

    positional arguments:
      headers               A header file(s) to generate mocks for
    
    optional arguments:
      -h, --help            show this help message and exit
      -f FUNC, --func FUNC  generate a mock for a function named FUNC
      -w FUNC, --wrap FUNC  create __wrap_FUNC mock for a function named FUNC
      -W, --wrap-all        create __wrap_* mocks for all functions
      -o DIR, --outdir DIR  output directory (by default "." is used)
    
    Environment variables:
        EASYMOCK_GCC        Full path to a working GCC compiler
        EASYMOCK_CFLAGS     GCC CFLAGS (for example, -I<path_to_header>)
    
        PYTHONPATH          Python search path(s) for modules
                            (in addition to system locations).
                            If pycparser is not installed in the system,
                            the path to pycparser must be specified in PYTHONPATH.
