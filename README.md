easymock
========

Mock generator for C

    usage: easymockgen.py [-h] [--func FUNC] [--func-pfx FUNC] [--wrap FUNC]
                          [--wrap-pfx FUNC] [--wrap-all] [--include INCHDR]
                          [--include-all] [-o DIR]
                          header [header ...]

    Generates easymocks
    
    positional arguments:
      header                A header file(s) to generate mocks for
    
    optional arguments:
      -h, --help            show this help message and exit
      --func FUNC           create a mock for a function named FUNC
      --func-pfx FUNC       create mocks for functions named
                            with the prefix FUNC*
      --wrap FUNC           create __wrap_FUNC mock for a function named FUNC
      --wrap-pfx FUNC       create __wrap_* mocks for functions
                            named with the prefix FUNC*
      --wrap-all            create __wrap_* mocks for all functions
      --include INCHDR      generate mocks for functions defined
                            in the included header INCHDR
      --include-all         generate mocks for functions defined
                            in all included headers
      -o DIR, --outdir DIR  output directory (by default "." is used)

    Environment variables:
        EASYMOCK_GCC        Full path to a working GCC compiler
        EASYMOCK_CFLAGS     GCC CFLAGS (for example, -I<path_to_header>)
    
        PYTHONPATH          Python search path(s) for modules
                            (in addition to system locations).
                            If pycparser is not installed in the system,
                            the path to pycparser must be specified in PYTHONPATH.
