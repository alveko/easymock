//! Generated by easymock

#ifndef EASYMOCK_EM_HEADER_4_H
#define EASYMOCK_EM_HEADER_4_H

#include <easymock.h>
#include "em_header_4.h"

//!
//! Mock for em_func_inside_header_4_b
//!

easymock_func* easymock_meta_of_em_func_inside_header_4_b(void);

typedef struct easymock_params_of_em_func_inside_header_4_b_tag {
    int x;
} easymock_params_of_em_func_inside_header_4_b;

typedef int easymock_return_type_of_em_func_inside_header_4_b;

typedef struct easymock_result_of_em_func_inside_header_4_b_tag {
    easymock_return_type_of_em_func_inside_header_4_b return_value;
} easymock_result_of_em_func_inside_header_4_b;

typedef int (*easymock_fn_callback_em_func_inside_header_4_b)(
    const easymock_params_of_em_func_inside_header_4_b*,
    void*);

typedef int (*easymock_fn_check_em_func_inside_header_4_b)(
    const easymock_params_of_em_func_inside_header_4_b*,
    void*);

void easymock_ignore_and_return_em_func_inside_header_4_b(
    easymock_return_type_of_em_func_inside_header_4_b _em_return_value);

void easymock_ignore_and_callback_em_func_inside_header_4_b(
    easymock_fn_callback_em_func_inside_header_4_b _em_fn_callback,
    void* _em_arg_cb);

void easymock_match_and_return_em_func_inside_header_4_b(
    int x,
    easymock_return_type_of_em_func_inside_header_4_b _em_return_value);

void easymock_match_and_callback_em_func_inside_header_4_b(
    int x,
    easymock_fn_callback_em_func_inside_header_4_b _em_fn_callback,
    void* _em_arg_cb);

void easymock_check_and_return_em_func_inside_header_4_b(
    easymock_fn_check_em_func_inside_header_4_b _em_fn_check,
    void* _em_arg_ch,
    easymock_return_type_of_em_func_inside_header_4_b _em_return_value);

void easymock_check_and_callback_em_func_inside_header_4_b(
    easymock_fn_check_em_func_inside_header_4_b _em_fn_check,
    void* _em_arg_ch,
    easymock_fn_callback_em_func_inside_header_4_b _em_fn_callback,
    void* _em_arg_cb);

/* Original function declaration:
int em_func_inside_header_4_b(
    int x);
*/

//!
//! Mock for em_func_inside_header_4
//!

easymock_func* easymock_meta_of_em_func_inside_header_4(void);

typedef struct easymock_params_of_em_func_inside_header_4_tag {
    int x;
} easymock_params_of_em_func_inside_header_4;

typedef int easymock_return_type_of_em_func_inside_header_4;

typedef struct easymock_result_of_em_func_inside_header_4_tag {
    easymock_return_type_of_em_func_inside_header_4 return_value;
} easymock_result_of_em_func_inside_header_4;

typedef int (*easymock_fn_callback_em_func_inside_header_4)(
    const easymock_params_of_em_func_inside_header_4*,
    void*);

typedef int (*easymock_fn_check_em_func_inside_header_4)(
    const easymock_params_of_em_func_inside_header_4*,
    void*);

void easymock_ignore_and_return_em_func_inside_header_4(
    easymock_return_type_of_em_func_inside_header_4 _em_return_value);

void easymock_ignore_and_callback_em_func_inside_header_4(
    easymock_fn_callback_em_func_inside_header_4 _em_fn_callback,
    void* _em_arg_cb);

void easymock_match_and_return_em_func_inside_header_4(
    int x,
    easymock_return_type_of_em_func_inside_header_4 _em_return_value);

void easymock_match_and_callback_em_func_inside_header_4(
    int x,
    easymock_fn_callback_em_func_inside_header_4 _em_fn_callback,
    void* _em_arg_cb);

void easymock_check_and_return_em_func_inside_header_4(
    easymock_fn_check_em_func_inside_header_4 _em_fn_check,
    void* _em_arg_ch,
    easymock_return_type_of_em_func_inside_header_4 _em_return_value);

void easymock_check_and_callback_em_func_inside_header_4(
    easymock_fn_check_em_func_inside_header_4 _em_fn_check,
    void* _em_arg_ch,
    easymock_fn_callback_em_func_inside_header_4 _em_fn_callback,
    void* _em_arg_cb);

/* Original function declaration:
int em_func_inside_header_4(
    int x);
*/

#endif