//! Generated by easymock

#ifndef EASYMOCK_EM_HEADER_2_H
#define EASYMOCK_EM_HEADER_2_H

#include <easymock.h>
#include "em_header_2.h"

//!
//! Mock for em_open
//!

#include <stdarg.h>

easymock_func* easymock_meta_of_em_open(void);

typedef struct easymock_params_of_em_open_tag {
    const char* file;
    int oflag;
    char* _em_va_formatted;
    va_list _em_va_list;
} easymock_params_of_em_open;

typedef int easymock_return_type_of_em_open;

typedef struct easymock_result_of_em_open_tag {
    easymock_return_type_of_em_open return_value;
} easymock_result_of_em_open;

typedef int (*easymock_fn_callback_em_open)(
    const easymock_params_of_em_open*,
    void*);

typedef int (*easymock_fn_check_em_open)(
    const easymock_params_of_em_open*,
    void*);

void easymock_ignore_and_return_em_open(
    easymock_return_type_of_em_open _em_return_value);

void easymock_ignore_and_callback_em_open(
    easymock_fn_callback_em_open _em_fn_callback,
    void* _em_arg_cb);

void easymock_match_va_and_return_em_open(
    easymock_return_type_of_em_open _em_return_value,
    const char* file,
    int oflag,
    ...);

void easymock_match_va_and_callback_em_open(
    easymock_fn_callback_em_open _em_fn_callback,
    void* _em_arg_cb,
    const char* file,
    int oflag,
    ...);

void easymock_check_and_return_em_open(
    easymock_fn_check_em_open _em_fn_check,
    void* _em_arg_ch,
    easymock_return_type_of_em_open _em_return_value);

void easymock_check_and_callback_em_open(
    easymock_fn_check_em_open _em_fn_check,
    void* _em_arg_ch,
    easymock_fn_callback_em_open _em_fn_callback,
    void* _em_arg_cb);

/* Original function declaration:
int em_open(
    const char* file,
    int oflag,
    ...);
*/

//!
//! Mock for em_snprintf
//!

#include <stdarg.h>

easymock_func* easymock_meta_of_em_snprintf(void);

typedef struct easymock_params_of_em_snprintf_tag {
    char* str;
    size_t size;
    const char* format;
    char* _em_va_formatted;
    va_list _em_va_list;
} easymock_params_of_em_snprintf;

typedef int easymock_return_type_of_em_snprintf;

typedef struct easymock_result_of_em_snprintf_tag {
    easymock_return_type_of_em_snprintf return_value;
} easymock_result_of_em_snprintf;

typedef int (*easymock_fn_callback_em_snprintf)(
    const easymock_params_of_em_snprintf*,
    void*);

typedef int (*easymock_fn_check_em_snprintf)(
    const easymock_params_of_em_snprintf*,
    void*);

void easymock_ignore_and_return_em_snprintf(
    easymock_return_type_of_em_snprintf _em_return_value);

void easymock_ignore_and_callback_em_snprintf(
    easymock_fn_callback_em_snprintf _em_fn_callback,
    void* _em_arg_cb);

void easymock_match_va_and_return_em_snprintf(
    easymock_return_type_of_em_snprintf _em_return_value,
    char* str,
    size_t size,
    const char* format,
    ...);

void easymock_match_va_and_callback_em_snprintf(
    easymock_fn_callback_em_snprintf _em_fn_callback,
    void* _em_arg_cb,
    char* str,
    size_t size,
    const char* format,
    ...);

void easymock_check_and_return_em_snprintf(
    easymock_fn_check_em_snprintf _em_fn_check,
    void* _em_arg_ch,
    easymock_return_type_of_em_snprintf _em_return_value);

void easymock_check_and_callback_em_snprintf(
    easymock_fn_check_em_snprintf _em_fn_check,
    void* _em_arg_ch,
    easymock_fn_callback_em_snprintf _em_fn_callback,
    void* _em_arg_cb);

/* Original function declaration:
int em_snprintf(
    char* str,
    size_t size,
    const char* format,
    ...);
*/

#endif