#include "easymock.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <sys/param.h>

//!
//! Types
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

/*
void  easymock_list_init(easymock_list *list);
int   easymock_list_size(easymock_list *list);
int   easymock_list_is_empty(easymock_list *list);
void* easymock_list_push_tail(easymock_list *list, void* data);
void* easymock_list_pop_head(easymock_list *list);
void* easymock_list_head(easymock_list *list);
void* easymock_list_tail(easymock_list *list);

easymock_iter easymock_list_begin(easymock_iter *list);
easymock_iter easymock_list_end();
void* easymock_list_next(easymock_iter* iter);
void* easymock_list_data(easymock_iter* iter);
*/

void easymock_list_init(easymock_list *list)
{
    memset(list, 0, sizeof(easymock_list));
}

int easymock_list_size(easymock_list *list)
{
    return list->size;
}

int easymock_list_is_empty(easymock_list *list)
{
    return easymock_list_size(list) == 0;
}

void* easymock_list_push_tail(easymock_list *list, void* data)
{
    void* data_old_tail = NULL;
    easymock_node* new_tail = malloc(sizeof(easymock_node));
    memset(new_tail, 0, sizeof(easymock_node));
    assert(data);
    new_tail->data = data;
    if (list->tail) {
        data_old_tail = list->tail->data;
        list->tail->next = new_tail;
    } else {
        list->head = new_tail;
    }
    list->tail = new_tail;
    list->size++;
    assert(list->size >= 0);
    assert((!!list->size) == (!!list->head));
    assert((!!list->head) == (!!list->tail));
    return data_old_tail;
}

void* easymock_list_pop_head(easymock_list *list)
{
    void* data_old_head = NULL;
    if (list->head) {
        easymock_node* old_head = list->head;
        data_old_head = list->head->data;
        list->head = list->head->next;
        free(old_head);
        list->size--;
        if (!list->head) {
            list->tail = NULL;
        }
    }
    assert(list->size >= 0);
    assert((!!list->size) == (!!list->head));
    assert((!!list->head) == (!!list->tail));
    return data_old_head;
}

void* easymock_list_head(easymock_list *list)
{
    return list->head ? list->head->data : NULL;
}

void* easymock_list_tail(easymock_list *list)
{
    return list->tail ? list->tail->data : NULL;
}

easymock_iter easymock_list_begin(easymock_list *list)
{
    return list->head;
}

easymock_iter easymock_list_end()
{
    return NULL;
}

void* easymock_list_next(easymock_iter* iter)
{
    void* data = NULL;
    if (*iter) {
        easymock_node* node = *iter;
        data = node->data;
        *iter = node->next;
    }
    return data;
}

void* easymock_list_data(easymock_iter iter)
{
    void* data = NULL;
    if (iter) {
        easymock_node* node = iter;
        data = node->data;
    }
    return data;
}

typedef struct {
    easymock_list ci_seq;
    easymock_iter ci_seq_curr;
    easymock_list errors;
    int           nb_seq_calls;
    int           nb_stc_calls;
    int           is_started;
} easymock;

//!
//! Global data
//!

static easymock gem;

//!
//! Easymock functions used in unit tests
//!

void easymock_start(void)
{
    gem.is_started = 1;
}

void easymock_stop(void)
{
    gem.is_started = 0;
    gem.nb_seq_calls = 0;
    while(!easymock_list_is_empty(&gem.ci_seq)) {
        easymock_call_instance_destroy(
            (easymock_call_instance*)easymock_list_pop_head(&gem.ci_seq));
    }
    while(!easymock_list_is_empty(&gem.errors)) {
        free((char*)easymock_list_pop_head(&gem.errors));
    }
}

int easymock_is_started(void)
{
    return gem.is_started;
}

int easymock_check()
{
    easymock_call_instance* ci = NULL;
    while ((ci = (easymock_call_instance*)
            easymock_list_next(&gem.ci_seq_curr)) != NULL) {
        easymock_error("Expected, but not called: %s\n", ci->func->name);
    }
    return easymock_list_size(&gem.errors);
}

int easymock_errors_print(FILE *fp)
{
    int ri = 0;
    char* err = NULL;
    easymock_iter iter = easymock_list_begin(&gem.errors);
    while ((err = (char*)easymock_list_next(&iter)) != NULL) {
        ri += fprintf(fp, "%s", err);
    }
    return ri;
}

int easymock_error(const char* format, ...)
{
    char* err;
    char* perr;
    int len = 0;
    va_list args;

    va_start(args, format);
    len += snprintf(NULL, 0, "ERROR[%d], mock call[%02d:%02d]: ",
                    easymock_list_size(&gem.errors),
                    easymock_nb_seq_calls_get(),
                    easymock_nb_stc_calls_get());
    len += vsnprintf(NULL, 0, format, args);

    perr = err = malloc(len + 1);
    EASYMOCK_ABORTIF(!err, "malloc failed");
    perr += snprintf(err, len + 1,
                     "ERROR[%d], mock call[%02d:%02d]: ",
                     easymock_list_size(&gem.errors),
                     easymock_nb_seq_calls_get(),
                     easymock_nb_stc_calls_get());
    vsnprintf(perr, (len + 1) - (perr - err), format, args);
    va_end(args);

    easymock_log("%s", perr);
    easymock_list_push_tail(&gem.errors, err);
    return easymock_list_size(&gem.errors);
}

int easymock_log(const char* format, ...)
{
    int ri = 0;
    va_list args;
    va_start(args, format);
    ri += printf("EASYMOCK: Mock call[%02d:%02d]: ",
                 easymock_nb_seq_calls_get(),
                 easymock_nb_stc_calls_get());
    ri += vprintf(format, args);
    va_end(args);
    return ri;
}

//!
//! Functions to match parameters
//!

int easymock_match_param_memcmp(
    const easymock_param* param, const void* pp1, const void* pp2)
{
    return memcmp(pp1, pp2, param->size);
}

int easymock_match_param_memcmp_deref(
    const easymock_param* param, const void* pp1, const void* pp2)
{
    if (param->size_deref <= 0) {
        easymock_error("Matching failed! No dereferenced size for %s\n",
                       param->name);
        return -1;
    }
    const void* dp1 = *((const void**)pp1);
    const void* dp2 = *((const void**)pp2);
    if (dp1 == dp2) {
        return 0;
    }
    if (!dp1 || !dp2) {
        return -1;
    }
    return memcmp(dp1, dp2, param->size_deref);
}

int easymock_match_param_strcmp(
    const easymock_param* param, const void* pp1, const void* pp2)
{
    const char* cp1 = *((const char**)pp1);
    const char* cp2 = *((const char**)pp2);
    if (cp1 == cp2) {
        return 0;
    }
    if (!cp1 || !cp2) {
        return -1;
    }
    return strcmp(cp1, cp2);
}

int easymock_match_param_smart(
    const easymock_param* param, const void* pp1, const void* pp2)
{
    int rc = 0;
    if (strcmp(param->type_basic, "char*") == 0) {
        rc = easymock_match_param_strcmp(param, pp1, pp2);
    } else if (strcmp(param->type_basic, "custom_struct*") == 0) {
        rc = easymock_match_param_memcmp_deref(param, pp1, pp2);
    } else {
        rc = easymock_match_param_memcmp(param, pp1, pp2);
    }
    return rc;
}

//!
//! Functions to print parameters
//!

static int easymock_print_param_exprcv(
    const easymock_param* param,
    const void* ppexp, const void* pprcv,
    char* out, size_t out_size)
{
    int ri = 0;
    char sexp[EASYMOCK_MSG_PARAM_LENGTH_MAX] = "N/A";
    char srcv[EASYMOCK_MSG_PARAM_LENGTH_MAX] = "N/A";
    if (param->fn_print) {
        param->fn_print(param, ppexp, sexp, sizeof(sexp));
        param->fn_print(param, pprcv, srcv, sizeof(srcv));
    }
    ri = snprintf(out, out_size,
                  "    Parameter %-4d     : %s %s (basictype: %s)\n"
                  "        expected value : %s\n"
                  "        received value : %s\n",
                  param->index,
                  param->type, param->name,
                  param->type_basic, sexp, srcv);
    return ri;
}

static int easymock_print_param_hex_dump(
    const void* mptr, size_t msize, char* out, size_t out_size)
{
    size_t i;
    unsigned char ascii[17];
    const unsigned char* pc = (unsigned char*)mptr;
    char* pout = out;
    char prefix[26];
    memset(prefix, ' ', sizeof(prefix));
    prefix[25] = '\0';

    for (i = 0; i < msize; i++) {
        if ((i % 16) == 0) {
            // don't print ASCII for the zeroth line.
            if (i != 0) {
                pout += snprintf(pout, MAX(0, (int)out_size - (pout - out)),
                                 "  %s\n", ascii);
            }
            // address offset
            pout += snprintf(pout, MAX(0, (int)out_size - (pout - out)),
                             "%s", prefix);
            pout += snprintf(pout, MAX(0, (int)out_size - (pout - out)),
                             "%04x:", i);
        }
        // the hex code for the specific byte
        pout += snprintf(pout, MAX(0, (int)out_size - (pout - out)),
                         "%s%02x", ((i & 1) ? "" : " "), pc[i]);
        // ascii character for later
        ascii[(i % 16)] = (isprint(pc[i])) ? pc[i] : '.';
        ascii[(i % 16) + 1] = '\0';
    }

    // pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        pout += snprintf(pout, MAX(0, (int)out_size - (pout - out)),
                         "%s  ", ((i & 1) ? "" : " "));
        i++;
    }
    // print the final ASCII line
    pout += snprintf(pout, MAX(0, (int)out_size - (pout - out)),
                     "  %s", ascii);
    return pout - out;
}

int easymock_print_param_smart(
    const easymock_param* param, const void* pval, char* out, size_t out_size)
{
    int ri = 0;
    if (!pval) {
        ri += snprintf(out, out_size, "NULL");
    // int
    } else if (strcmp(param->type_basic, "int") == 0) {
        ri += snprintf(out, out_size, "%d", *((int*)pval));
    } else if (strcmp(param->type_basic, "unsigned int") == 0) {
        ri += snprintf(out, out_size, "%u", *((unsigned int*)pval));
    // short int
    } else if (strcmp(param->type_basic, "short int") == 0) {
        ri += snprintf(out, out_size, "%hd", *((short int*)pval));
    } else if (strcmp(param->type_basic, "unsigned short int") == 0) {
        ri += snprintf(out, out_size, "%hu", *((unsigned short int*)pval));
    // long int
    } else if (strcmp(param->type_basic, "long int") == 0) {
        ri += snprintf(out, out_size, "%ld", *((long int*)pval));
    } else if (strcmp(param->type_basic, "unsigned long int") == 0) {
        ri += snprintf(out, out_size, "%lu", *((unsigned long int*)pval));
    // long long int
    } else if (strcmp(param->type_basic, "long long int") == 0) {
        ri += snprintf(out, out_size, "%lld", *((long long int*)pval));
    } else if (strcmp(param->type_basic, "unsigned long long int") == 0) {
        ri += snprintf(out, out_size, "%llu", *((unsigned long long int*)pval));
    // char
    } else if (strcmp(param->type_basic, "signed char") == 0 ||
               strcmp(param->type_basic, "char") == 0) {
        ri += snprintf(out, out_size, "%hhd", *((char*)pval));
    } else if (strcmp(param->type_basic, "unsigned char") == 0) {
        ri += snprintf(out, out_size, "%hhu", *((unsigned char*)pval));
    // double
    } else if (strcmp(param->type_basic, "double") == 0) {
        ri += snprintf(out, out_size, "%f", *((double*)pval));
    } else if (strcmp(param->type_basic, "long double") == 0) {
        ri += snprintf(out, out_size, "%Lf", *((long double*)pval));
    // size_t
    } else if (strcmp(param->type, "size_t") == 0) {
        ri += snprintf(out, out_size, "%zd", *((size_t*)pval));
    // string (char*)
    } else if (strcmp(param->type_basic, "char*") == 0) {
        char* cp = *((char**)pval);
        ri += snprintf(out, out_size, "char* = %s", (cp) ? cp : "NULL");
    // pointer
    } else if (param->type_basic[strlen(param->type_basic)-1] == '*') {
        void* dp = *((void**)pval);
        char* pout = out;
        pout += snprintf(pout, MAX(0, (int)out_size - (pout - out)),
                         "ptr = %p", dp);
        if (dp && strcmp(param->type_basic, "custom_struct*") == 0) {
            pout += snprintf(pout, MAX(0, (int)out_size - (pout - out)),
                             ", size = %d\n", param->size_deref);
            pout += easymock_print_param_hex_dump(
                dp, param->size_deref, pout,
                MAX(0, (int)out_size - (pout - out)));
        }
        ri += pout - out;
    // by default, print memory in hex
    } else {
        char* pout = out;
        pout += snprintf(pout, MAX(0, (int)out_size - (pout - out)),
                         "size = %d\n", param->size);
        pout += easymock_print_param_hex_dump(
            pval, param->size, pout, MAX(0, (int)out_size - (pout - out)));
        ri += pout - out;
    }
    return ri;
}
int easymock_print_param_int(
    const easymock_param* param, const void* pval, char* out, size_t out_size)
{
    int ri = 0;
    if (!pval) {
        ri += snprintf(out, out_size, "NULL");
    } else {
        ri += snprintf(out, out_size, "%d", *((int*)pval));
    }
    return ri;
}

int easymock_print_param_ptr(
    const easymock_param* param, const void* pval, char* out, size_t out_size)
{
    int ri = 0;
    if (!pval) {
        ri += snprintf(out, out_size, "NULL");
    } else {
        ri += snprintf(out, out_size, "%p", *((void**)pval));
    }
    return ri;
}

int easymock_print_param_str(
    const easymock_param* param, const void* pval, char* out, size_t out_size)
{
    int ri = 0;
    if (!pval) {
        ri += snprintf(out, out_size, "NULL");
    } else {
        char* cp = *((char**)pval);
        ri += snprintf(out, out_size, "%s", (cp) ? cp : "NULL");;
    }
    return ri;
}

//!
//! Functions managing call instances
//!

int easymock_nb_seq_calls_get()
{
    return gem.nb_seq_calls;
}

int easymock_nb_stc_calls_get()
{
    return gem.nb_stc_calls;
}

int easymock_nb_seq_calls_inc()
{
    return ++gem.nb_seq_calls;
}

int easymock_nb_stc_calls_inc()
{
    return ++gem.nb_stc_calls;
}

easymock_call_instance* easymock_call_instance_create()
{
    easymock_call_instance* ci = NULL;
    ci = malloc(sizeof(easymock_call_instance));
    memset(ci, 0, sizeof(easymock_call_instance));
    return ci;
}

void easymock_call_instance_destroy(easymock_call_instance* ci)
{
    if (ci) {
        if (ci->params_expected) {
            free(ci->params_expected);
            ci->params_expected = NULL;
        }
        if (ci->params_received) {
            free(ci->params_received);
            ci->params_received = NULL;
        }
        if (ci->result) {
            free(ci->result);
            ci->result = NULL;
        }
        free(ci);
        ci = NULL;
    }
}

void easymock_call_instance_push(easymock_call_instance* ci)
{
    if (gem.is_started) {
        easymock_list_push_tail(&gem.ci_seq, ci);
        if (easymock_list_size(&gem.ci_seq) == 1) {
            // the first ci was just added => set ci_seq_curr
            gem.ci_seq_curr = easymock_list_begin(&gem.ci_seq);
        }
    }
}

easymock_call_instance* easymock_call_instance_pop(const char* funcname)
{
    easymock_call_instance* ci = NULL;
    if (gem.is_started) {
        ci = easymock_list_data(gem.ci_seq_curr);
        if (ci && strcmp(ci->func->name, funcname) == 0) {
            easymock_list_next(&gem.ci_seq_curr);
        } else {
            ci = NULL;
        }
    }
    return ci;
}

easymock_call_instance* easymock_call_instance_curr()
{
    if (gem.is_started) {
        return easymock_list_data(gem.ci_seq_curr);
    }
    return NULL;
}

easymock_call_instance* easymock_call_instance_last()
{
    if (gem.is_started) {
        return easymock_list_tail(&gem.ci_seq);
    }
    return NULL;
}

void easymock_label(const char* label)
{
    easymock_call_instance* ci = easymock_call_instance_last();
    assert(ci);
    ci->label = label;
}

void* easymock_params_get_by_label(const char* label)
{
    void* params = NULL;
    easymock_call_instance* ci = easymock_call_instance_get_by_label(label);
    if (ci) {
        params = ci->params_received;
    }
    return params;
}

void* easymock_params_get_by_name(const char* funcname)
{
    void* params = NULL;
    easymock_call_instance* ci = easymock_call_instance_get_by_name(funcname);
    if (ci) {
        params = ci->params_received;
    }
    return params;
}

easymock_call_instance* easymock_call_instance_get_by_label(const char* label)
{
    easymock_call_instance* ci = NULL;
    easymock_iter iter = easymock_list_begin(&gem.ci_seq);
    while ((ci = (easymock_call_instance*)
            easymock_list_next(&iter)) != NULL) {
        if (ci->label && strcmp(ci->label, label) == 0) {
            return ci;
        }
    }
    return NULL;
}

easymock_call_instance* easymock_call_instance_get_by_name(const char* funcname)
{
    easymock_call_instance* ci = NULL;
    easymock_iter iter = easymock_list_begin(&gem.ci_seq);
    while ((ci = (easymock_call_instance*)
            easymock_list_next(&iter)) != NULL) {
        if (ci->func && ci->func->name &&
            strcmp(ci->func->name, funcname) == 0) {
            return ci;
        }
    }
    return NULL;
}

int easymock_call_instance_print_params(
    const easymock_call_instance* ci, char* out, size_t out_size)
{
    int i;
    char* pout = out;
    for (i = 0; i < ci->func->params_size; i++) {
        easymock_param* param = &ci->func->params[i];
        char* ppexp = ((ci->params_expected) ?
                       (char*)ci->params_expected + param->offset : NULL);
        char* pprcv = ((ci->params_received) ?
                       (char*)ci->params_received + param->offset : NULL);
        pout += easymock_print_param_exprcv(
            param, ppexp, pprcv,
            pout, MAX(0, (int)out_size - (pout - out)));
    }
    return pout - out;
}

int easymock_call_instance_match_params(
    const easymock_call_instance* ci)
{
    int rc = 0, i = 0;
    if (!ci->params_expected || !ci->params_received) {
        easymock_log("%s: All parameters ingored\n", ci->func->name);
        return 0;
    }
    for (i = 0; i < ci->func->params_size; i++) {
        const easymock_param* param = &ci->func->params[i];

        char sprm[EASYMOCK_MSG_PARAM_LENGTH_MAX * 2] = "";
        char* ppexp = ((ci->params_expected) ?
                       (char*)ci->params_expected + param->offset : NULL);
        char* pprcv = ((ci->params_received) ?
                       (char*)ci->params_received + param->offset : NULL);
        easymock_print_param_exprcv(param, ppexp, pprcv,
                                    sprm, sizeof(sprm));

        if (param->fn_match) {
            int match = param->fn_match(param, ppexp, pprcv);

            if (match == 0) {
                easymock_log("%s: Paramter %d - match OK\n%s",
                             ci->func->name, param->index, sprm);
            } else {
                easymock_error("%s: Paramter %d - match FAILED\n%s",
                               ci->func->name, param->index, sprm);
                rc++;
            }
        } else {
            easymock_log("%s: Paramter %d - ignored\n%s",
                         ci->func->name, param->index, sprm);
        }
    }
    return rc;
}

//!
//! Auxiliary structs to wrap 2-3 arguments into one
//! - useful in check and callback modes
//!

em2args* make2args(void* arg1, void* arg2)
{
    em2args* p = malloc(sizeof(em2args));
    p->arg1 = arg1;
    p->arg2 = arg2;
    return p;
}

em3args* make3args(void* arg1, void* arg2, void* arg3)
{
    em3args* p = malloc(sizeof(em3args));
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->arg3 = arg3;
    return p;
}
