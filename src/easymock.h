//! Copyright (c) 2014, Alexander Korobeynikov
//! https://github.com/alveko/easymock
//! License: BSD

#ifndef EASYMOCK_H
#define EASYMOCK_H

#include <stdio.h>
#include <stddef.h>

//!
//! Macros
//!

#define EASYMOCK_MSG_PARAM_LENGTH_MAX  (4096)
#define EASYMOCK_MSG_ERROR_LENGTH_MAX  (EASYMOCK_MSG_PARAM_LENGTH_MAX * 10)

#define EASYMOCK_SIZEOF_ARRAY(a)       (sizeof(a)/sizeof(a[0]))

#define EASYMOCK_MEMBER_OFFSET(type, member)     offsetof(type, member)
#define EASYMOCK_MEMBER_SIZE(type, member)       sizeof(((type*)0)->member)
#define EASYMOCK_MEMBER_SIZE_DEREF(type, member) sizeof(*(((type*)0)->member))

#define EASYMOCK_DEFINE_PRINT_PARAM_FUNC(funcname, param_type, param_format) \
static int funcname(const void* pval, char* out, size_t out_size) \
{ \
    return snprintf(out, out_size, param_format, *((param_type*)pval)); \
}

#define EASYMOCK_ABORTIF(x, ...) { if (x) { easymock_log(__VA_ARGS__); abort(); } }

#define EASYMOCK_REAL(x) __real_ ## x
#define EASYMOCK_WRAP(x) __wrap_ ## x

#define EASYMOCK_UNUSED(x) (void)x;

//!
//! Types
//!

typedef enum {
    EASYMOCK_PARAM_1 = 0,
    EASYMOCK_PARAM_2 = 1,
    EASYMOCK_PARAM_3 = 2,
    EASYMOCK_PARAM_4 = 3,
    EASYMOCK_PARAM_5 = 4,
    EASYMOCK_PARAM_6 = 5,
    EASYMOCK_PARAM_7 = 6,
    EASYMOCK_PARAM_8 = 7,
    EASYMOCK_PARAM_9 = 8,
    EASYMOCK_PARAM_10 = 9,
} easymock_param_id;

struct easymock_param_tag;

typedef int (*easymock_fn_match_param)
    (const struct easymock_param_tag*, const void*, const void*);
typedef int (*easymock_fn_print_param)
    (const struct easymock_param_tag*, const void*, char*, size_t);
typedef void (*easymock_fn_destroy_params)
    (void*);

typedef struct easymock_param_tag {
    int         index;
    const char* name;
    const char* type;
    const char* type_basic;
    size_t offset;
    size_t size;
    size_t size_deref;
    easymock_fn_match_param fn_match;
    easymock_fn_print_param fn_print;
} easymock_param;

typedef struct easymock_func_tag {
    const char*     name;
    easymock_param* params;
    int             params_size;
    easymock_fn_destroy_params fn_destroy_params;
} easymock_func;

typedef enum {
    EASYMOCK_PRM_IGNORE = 0,
    EASYMOCK_PRM_MATCH,
    EASYMOCK_PRM_CHECK,
} easymock_prm_mode;

typedef enum {
    EASYMOCK_ACT_RETURN = 0,
    EASYMOCK_ACT_CALLBACK,
    EASYMOCK_ACT_CALLREAL,
} easymock_act_mode;

struct easymock_call_instance_tag;
typedef struct easymock_call_instance_tag {
    easymock_func*    func;
    easymock_prm_mode prm_mode;
    easymock_act_mode act_mode;
    const char*       label;

    void* params_expected;
    void* params_received;
    void* result;
    void* fn_callback;
    void* fn_check;
    void* arg_callback;
    void* arg_check;
} easymock_call_instance;

//!
//! Easymock functions used in unit tests
//!

void easymock_start(void);
void easymock_stop(void);
int  easymock_is_started(void);

int easymock_check(void);
int easymock_errors_print(FILE *fp);
int easymock_error(const char* format, ...);
int easymock_log(const char* format, ...);

// Matchers
int easymock_match_param_memcmp(
    const easymock_param* param, const void* pp1, const void* pp2);
int easymock_match_param_memcmp_deref(
    const easymock_param* param, const void* pp1, const void* pp2);
int easymock_match_param_strcmp(
    const easymock_param* param, const void* pp1, const void* pp2);
int easymock_match_param_smart(
    const easymock_param* param, const void* pp1, const void* pp2);

// Printers
int easymock_print_param_int(
    const easymock_param* param, const void* pval, char* out, size_t out_size);
int easymock_print_param_ptr(
    const easymock_param* param, const void* pval, char* out, size_t out_size);
int easymock_print_param_str(
    const easymock_param* param, const void* pval, char* out, size_t out_size);
int easymock_print_param_smart(
    const easymock_param* param, const void* pval, char* out, size_t out_size);

//!
//! Easymock functions used in generated mocks
//!

// Call instance create/destroy
easymock_call_instance* easymock_call_instance_create(void);
void easymock_call_instance_destroy(easymock_call_instance* ci);

// Call instance push/pop/top/last
void easymock_call_instance_push(easymock_call_instance* ci);
easymock_call_instance* easymock_call_instance_pop(const char* funcname);
easymock_call_instance* easymock_call_instance_top(void);
easymock_call_instance* easymock_call_instance_curr(void);
easymock_call_instance* easymock_call_instance_last(void);

// Call instance print/match params
int easymock_call_instance_print_params(
    const easymock_call_instance* ci, char* out, size_t out_size);
int easymock_call_instance_match_params(
    const easymock_call_instance* ci);

// Call instance get by name/index
easymock_call_instance* easymock_call_instance_get_by_label(const char* label);
easymock_call_instance* easymock_call_instance_get_by_name(const char* funcname);

void easymock_label(const char* label);
void* easymock_params_get_by_label(const char* label);
void* easymock_params_get_by_name(const char* label);

int easymock_nb_seq_calls_get(void);
int easymock_nb_seq_calls_inc(void);
int easymock_nb_stc_calls_inc(void);
int easymock_nb_stc_calls_get(void);

//!
//! Auxiliary structs to wrap 2-3 arguments into one
//! - useful in check and callback modes
//!

typedef struct {
    void* arg1;
    void* arg2;
} em2args;

typedef struct {
    void* arg1;
    void* arg2;
    void* arg3;
} em3args;

em2args* make2args(void* arg1, void* arg2);
em3args* make3args(void* arg1, void* arg2, void* arg3);

//!
//! Auxiliary single-linked list
//!

struct easymock_node_tag;
typedef struct easymock_node_tag {
    struct easymock_node_tag* next;
    void* data;
} easymock_node;

typedef struct easymock_list_tag {
    easymock_node* head;
    easymock_node* tail;
    int            size;
} easymock_list;

typedef void* easymock_iter;

void  easymock_list_init(easymock_list* list);
int   easymock_list_size(easymock_list* list);
int   easymock_list_is_empty(easymock_list* list);
void* easymock_list_push_tail(easymock_list* list, void* data);
void* easymock_list_pop_head(easymock_list* list);
void* easymock_list_head(easymock_list* list);
void* easymock_list_tail(easymock_list* list);

easymock_iter easymock_list_begin(easymock_list* list);
easymock_iter easymock_list_end(void);
void* easymock_list_data(easymock_iter iter);
void* easymock_list_next(easymock_iter* iter);

#endif
