easymock
========

Mock generator for C

    usage: easymockgen.py [-h] [--func FUNC] [--func-pfx FUNC] [--wrap FUNC]
                          [--wrap-pfx FUNC] [--wrap-all] [--include INCHDR]
                          [--include-all] [-o DIR]
                          header [header ...]

    Generates mocks for functions found in the specified header file(s).
    The purpose of the mock functions is provide implementation for the functions
    that are covered with unit tests.
                                                                                                  x
    For example, foo.c file has a number of functions fooX(...). The foo.c file includes some
    headers (for example, bar.h) and the functions barX(...) from those headers are called from
    fooX(...). In order to unit test foo.c and all functions in it, the mock (or stub)
    implementation is required for all external functions barX(...) called from foo.c. Easymock 
    generates such mock functions barX(...) for you, as well as a set of helper functions that
    allow you to configure the behavior of the mock functions.
    
    For every function found in a header file it generates a mock implementation with the same
    prototype as the original one.
    
    For a function without parameters having the prototype `return_type barX(void);`,
    the following functions will be generated to configure the mock behavior:
    
    void easymock_expect_and_return_barX   (return_type return_value);
    void easymock_expect_and_callback_barX (fn_callback callback_ptr, void* arg_callback);
    void easymock_expect_and_callreal_barX ();
    
    For a function with parameters like `return_type barX(ptype1 p1, ..., ptypeN pN);`,
    the following functions will be generated to configure the mock behavior:
    
    void easymock_ignore_and_return_barX   (return_type return_value);
    void easymock_ignore_and_callback_barX (fn_callback callback_ptr, void* arg_callback);
    void easymock_ignore_and_callreal_barX ();

    void easymock_match_and_return_barX    (ptype1 p1, ..., ptype1 pN, return_type return_value);
    void easymock_match_and_callback_barX  (ptype1 p1, ..., ptype1 pN, 
                                            fn_callback callback_ptr, void* arg_callback);
    void easymock_match_and_callreal_barX  (ptype1 p1, ..., ptype1 pN);

    void easymock_check_and_return_barX    (fn_check check_ptr, void* arg_check, return_value);
    void easymock_check_and_callback_barX  (fn_check check_ptr, void* arg_check, 
                                            fn_callback callback_ptr, void* arg_callback);
    void easymock_check_and_callreal_barX  (fn_check check_ptr, void* arg_check);
    
    positional arguments:
      header                A header file(s) to generate mocks for
    
    optional arguments:
      -h, --help            show this help message and exit
      --func FUNC           create a mock for a function named FUNC
      --func-pfx FUNC       create mocks for functions named
                            with the prefix FUNC*
      --func-all            create mocks for all functions (default)
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
