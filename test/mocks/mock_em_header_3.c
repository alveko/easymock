//! Generated by easymock

#include "mock_em_header_3.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//!
//! Mock for em_func_inside_header_3_b
//!

static easymock_param easymock_meta_params_of_em_func_inside_header_3_b[] =
{
    {
        .index = 1,
        .name = "x",
        .type = "int",
        .type_basic = "int",
        .offset = EASYMOCK_MEMBER_OFFSET(
            easymock_params_of_em_func_inside_header_3_b,
            x),
        .size = EASYMOCK_MEMBER_SIZE(
            easymock_params_of_em_func_inside_header_3_b,
            x),
        .fn_match = easymock_match_param_smart,
        .fn_print = easymock_print_param_smart,
    }
};

static easymock_params_of_em_func_inside_header_3_b*
easymock_create_params_of_em_func_inside_header_3_b()
{
    easymock_params_of_em_func_inside_header_3_b* _em_p = NULL;
    _em_p = malloc(sizeof(easymock_params_of_em_func_inside_header_3_b));
    memset(_em_p, 0, sizeof(easymock_params_of_em_func_inside_header_3_b));
    return _em_p;
}

static void easymock_destroy_params_of_em_func_inside_header_3_b(
    void* _em_params)
{
    easymock_params_of_em_func_inside_header_3_b* _em_p = _em_params;
    free(_em_p);
}

static void easymock_assign_params_of_em_func_inside_header_3_b(
    easymock_params_of_em_func_inside_header_3_b* _em_params,
    int x)
{
    _em_params->x = (int)x;
}

static easymock_func easymock_meta_func_of_em_func_inside_header_3_b =
{
    .name = "em_func_inside_header_3_b",
    .params = easymock_meta_params_of_em_func_inside_header_3_b,
    .params_size = EASYMOCK_SIZEOF_ARRAY(
        easymock_meta_params_of_em_func_inside_header_3_b),
    .fn_destroy_params = easymock_destroy_params_of_em_func_inside_header_3_b
};

easymock_func* easymock_meta_of_em_func_inside_header_3_b()
{
    return &easymock_meta_func_of_em_func_inside_header_3_b;
}

static easymock_result_of_em_func_inside_header_3_b*
easymock_create_result_of_em_func_inside_header_3_b()
{
    easymock_result_of_em_func_inside_header_3_b* _em_result = NULL;
    _em_result = malloc(sizeof(easymock_result_of_em_func_inside_header_3_b));
    memset(_em_result, 0, sizeof(easymock_result_of_em_func_inside_header_3_b));
    return _em_result;
}

static void easymock_assign_result_of_em_func_inside_header_3_b(
    easymock_result_of_em_func_inside_header_3_b* _em_result,
    easymock_return_type_of_em_func_inside_header_3_b _em_return_value)
{
    _em_result->return_value = _em_return_value;
}

static easymock_call_instance
easymock_static_call_instance_of_em_func_inside_header_3_b;

static easymock_call_instance*
easymock_static_ptr_call_instance_of_em_func_inside_header_3_b = NULL;

static easymock_params_of_em_func_inside_header_3_b
easymock_static_params_expected_of_em_func_inside_header_3_b;

static easymock_params_of_em_func_inside_header_3_b
easymock_static_params_received_of_em_func_inside_header_3_b;

static easymock_result_of_em_func_inside_header_3_b
easymock_static_result_of_em_func_inside_header_3_b;

static easymock_call_instance* easymock_new_static_em_func_inside_header_3_b()
{
    easymock_call_instance* ci = NULL;
    memset(&easymock_static_call_instance_of_em_func_inside_header_3_b, 0,
           sizeof(easymock_static_call_instance_of_em_func_inside_header_3_b));
    memset(&easymock_static_params_expected_of_em_func_inside_header_3_b, 0,
           sizeof(easymock_static_params_expected_of_em_func_inside_header_3_b));
    memset(&easymock_static_params_received_of_em_func_inside_header_3_b, 0,
           sizeof(easymock_static_params_received_of_em_func_inside_header_3_b));
    ci = &easymock_static_call_instance_of_em_func_inside_header_3_b;
    ci->params_expected =
        &easymock_static_params_expected_of_em_func_inside_header_3_b;
    ci->params_received =
        &easymock_static_params_received_of_em_func_inside_header_3_b;
    ci->result =
        &easymock_static_result_of_em_func_inside_header_3_b;
    ci->func = &easymock_meta_func_of_em_func_inside_header_3_b;
    return ci;
}

static easymock_call_instance* easymock_get_static_em_func_inside_header_3_b()
{
    return easymock_static_ptr_call_instance_of_em_func_inside_header_3_b;
}

static easymock_call_instance* easymock_new_em_func_inside_header_3_b()
{
    easymock_call_instance* ci = NULL;
    if (easymock_is_started()) {
        ci = easymock_call_instance_create();
        ci->params_expected =
            easymock_create_params_of_em_func_inside_header_3_b();
        ci->params_received =
            easymock_create_params_of_em_func_inside_header_3_b();
        ci->result =
            easymock_create_result_of_em_func_inside_header_3_b();
        ci->func = &easymock_meta_func_of_em_func_inside_header_3_b;
        easymock_call_instance_push(ci);
    } else {
        ci = easymock_new_static_em_func_inside_header_3_b();
        easymock_static_ptr_call_instance_of_em_func_inside_header_3_b = ci;
    }
    return ci;
}

void easymock_ignore_and_return_em_func_inside_header_3_b(
    easymock_return_type_of_em_func_inside_header_3_b _em_return_value)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_b();
    _em_ci->prm_mode = EASYMOCK_PRM_IGNORE;
    _em_ci->act_mode = EASYMOCK_ACT_RETURN;
    easymock_assign_result_of_em_func_inside_header_3_b(
        _em_ci->result, _em_return_value);
}

void easymock_ignore_and_callback_em_func_inside_header_3_b(
    easymock_fn_callback_em_func_inside_header_3_b _em_fn_callback,
    void* _em_arg_cb)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_b();
    _em_ci->prm_mode = EASYMOCK_PRM_IGNORE;
    _em_ci->act_mode = EASYMOCK_ACT_CALLBACK;
    _em_ci->fn_callback = _em_fn_callback;
    _em_ci->arg_callback = _em_arg_cb;
}

void easymock_match_and_return_em_func_inside_header_3_b(
    int x,
    easymock_return_type_of_em_func_inside_header_3_b _em_return_value)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_b();
    _em_ci->prm_mode = EASYMOCK_PRM_MATCH;
    _em_ci->act_mode = EASYMOCK_ACT_RETURN;
    easymock_assign_params_of_em_func_inside_header_3_b(
        _em_ci->params_expected,
        x);
    easymock_assign_result_of_em_func_inside_header_3_b(
        _em_ci->result, _em_return_value);
}

void easymock_match_and_callback_em_func_inside_header_3_b(
    int x,
    easymock_fn_callback_em_func_inside_header_3_b _em_fn_callback,
    void* _em_arg_cb)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_b();
    _em_ci->prm_mode = EASYMOCK_PRM_MATCH;
    _em_ci->act_mode = EASYMOCK_ACT_CALLBACK;
    easymock_assign_params_of_em_func_inside_header_3_b(
        _em_ci->params_expected,
        x);
    _em_ci->fn_callback = _em_fn_callback;
    _em_ci->arg_callback = _em_arg_cb;
}

void easymock_check_and_return_em_func_inside_header_3_b(
    easymock_fn_check_em_func_inside_header_3_b _em_fn_check,
    void* _em_arg_ch,
    easymock_return_type_of_em_func_inside_header_3_b _em_return_value)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_b();
    _em_ci->prm_mode = EASYMOCK_PRM_CHECK;
    _em_ci->act_mode = EASYMOCK_ACT_RETURN;
    _em_ci->fn_check = _em_fn_check;
    _em_ci->arg_check = _em_arg_ch;
    easymock_assign_result_of_em_func_inside_header_3_b(
        _em_ci->result, _em_return_value);
}

void easymock_check_and_callback_em_func_inside_header_3_b(
    easymock_fn_check_em_func_inside_header_3_b _em_fn_check,
    void* _em_arg_ch,
    easymock_fn_callback_em_func_inside_header_3_b _em_fn_callback,
    void* _em_arg_cb)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_b();
    _em_ci->prm_mode = EASYMOCK_PRM_CHECK;
    _em_ci->act_mode = EASYMOCK_ACT_CALLBACK;
    _em_ci->fn_check = _em_fn_check;
    _em_ci->fn_callback = _em_fn_callback;
    _em_ci->arg_check = _em_arg_ch;
    _em_ci->arg_callback = _em_arg_cb;
}

int em_func_inside_header_3_b(
    int x)
{
    static char _em_sparams[EASYMOCK_MSG_ERROR_LENGTH_MAX] =
        "    (no params)\n";

    easymock_call_instance* _em_ci = NULL;
    int _em_is_unexpected = 0;
    int _em_is_seq_call = 0;

    // 1) try to get a sequence-configured call instance
    _em_ci = easymock_call_instance_pop("em_func_inside_header_3_b");
    if (_em_ci) {
        easymock_nb_seq_calls_inc();
        _em_is_seq_call = 1;
    } else {
        // 2) try to get a static-configured call instance
        _em_ci = easymock_get_static_em_func_inside_header_3_b();
        if (_em_ci) {
            easymock_nb_stc_calls_inc();
        } else {
            // 3) get a dummy all-zero static call instance
            _em_ci = easymock_new_static_em_func_inside_header_3_b();
            _em_is_unexpected = easymock_is_started();
        }
    }
    assert(_em_ci);

    easymock_assign_params_of_em_func_inside_header_3_b(
        _em_ci->params_received,
        x);

    if (_em_is_unexpected) {
        // print the received params
        easymock_call_instance_print_params(
            _em_ci, _em_sparams, sizeof(_em_sparams));

        easymock_error(
            "%s: Called - UNEXPECTED!\n%s", "em_func_inside_header_3_b",
            _em_sparams);
    } else {
        if (_em_is_seq_call) {
            easymock_log("%s: Called - OK\n", "em_func_inside_header_3_b");
        }

        // === match params
        if (_em_ci->prm_mode == EASYMOCK_PRM_MATCH) {
            easymock_call_instance_match_params(_em_ci);
        }
        // === check params
        else if (_em_ci->prm_mode == EASYMOCK_PRM_CHECK) {
            assert(_em_ci->fn_check);
            int _em_rc = ((easymock_fn_check_em_func_inside_header_3_b)_em_ci->fn_check)(
                (easymock_params_of_em_func_inside_header_3_b*)_em_ci->params_received,
                _em_ci->arg_check);
            easymock_call_instance_print_params(
                _em_ci, _em_sparams, sizeof(_em_sparams));
            if (_em_rc == 0) {
                easymock_log(
                    "%s: Check - OK\n%s",
                    "em_func_inside_header_3_b", _em_sparams);
            } else {
                easymock_error(
                    "%s: Check - FAILED!\n%s",
                    "em_func_inside_header_3_b", _em_sparams);
            }
        }
        // === call the provided callback
        if (_em_ci->act_mode == EASYMOCK_ACT_CALLBACK) {
            assert(_em_ci->fn_callback);
            return ((easymock_fn_callback_em_func_inside_header_3_b)
                _em_ci->fn_callback)(
                    (easymock_params_of_em_func_inside_header_3_b*)
                    _em_ci->params_received,
                    _em_ci->arg_callback);
        }
    }
    // === return the result
    return ((easymock_result_of_em_func_inside_header_3_b*)
            _em_ci->result)->return_value;
}

//!
//! Mock for em_func_inside_header_3_a
//!

static easymock_param easymock_meta_params_of_em_func_inside_header_3_a[] =
{
    {
        .index = 1,
        .name = "x",
        .type = "int",
        .type_basic = "int",
        .offset = EASYMOCK_MEMBER_OFFSET(
            easymock_params_of_em_func_inside_header_3_a,
            x),
        .size = EASYMOCK_MEMBER_SIZE(
            easymock_params_of_em_func_inside_header_3_a,
            x),
        .fn_match = easymock_match_param_smart,
        .fn_print = easymock_print_param_smart,
    }
};

static easymock_params_of_em_func_inside_header_3_a*
easymock_create_params_of_em_func_inside_header_3_a()
{
    easymock_params_of_em_func_inside_header_3_a* _em_p = NULL;
    _em_p = malloc(sizeof(easymock_params_of_em_func_inside_header_3_a));
    memset(_em_p, 0, sizeof(easymock_params_of_em_func_inside_header_3_a));
    return _em_p;
}

static void easymock_destroy_params_of_em_func_inside_header_3_a(
    void* _em_params)
{
    easymock_params_of_em_func_inside_header_3_a* _em_p = _em_params;
    free(_em_p);
}

static void easymock_assign_params_of_em_func_inside_header_3_a(
    easymock_params_of_em_func_inside_header_3_a* _em_params,
    int x)
{
    _em_params->x = (int)x;
}

static easymock_func easymock_meta_func_of_em_func_inside_header_3_a =
{
    .name = "em_func_inside_header_3_a",
    .params = easymock_meta_params_of_em_func_inside_header_3_a,
    .params_size = EASYMOCK_SIZEOF_ARRAY(
        easymock_meta_params_of_em_func_inside_header_3_a),
    .fn_destroy_params = easymock_destroy_params_of_em_func_inside_header_3_a
};

easymock_func* easymock_meta_of_em_func_inside_header_3_a()
{
    return &easymock_meta_func_of_em_func_inside_header_3_a;
}

static easymock_result_of_em_func_inside_header_3_a*
easymock_create_result_of_em_func_inside_header_3_a()
{
    easymock_result_of_em_func_inside_header_3_a* _em_result = NULL;
    _em_result = malloc(sizeof(easymock_result_of_em_func_inside_header_3_a));
    memset(_em_result, 0, sizeof(easymock_result_of_em_func_inside_header_3_a));
    return _em_result;
}

static void easymock_assign_result_of_em_func_inside_header_3_a(
    easymock_result_of_em_func_inside_header_3_a* _em_result,
    easymock_return_type_of_em_func_inside_header_3_a _em_return_value)
{
    _em_result->return_value = _em_return_value;
}

static easymock_call_instance
easymock_static_call_instance_of_em_func_inside_header_3_a;

static easymock_call_instance*
easymock_static_ptr_call_instance_of_em_func_inside_header_3_a = NULL;

static easymock_params_of_em_func_inside_header_3_a
easymock_static_params_expected_of_em_func_inside_header_3_a;

static easymock_params_of_em_func_inside_header_3_a
easymock_static_params_received_of_em_func_inside_header_3_a;

static easymock_result_of_em_func_inside_header_3_a
easymock_static_result_of_em_func_inside_header_3_a;

static easymock_call_instance* easymock_new_static_em_func_inside_header_3_a()
{
    easymock_call_instance* ci = NULL;
    memset(&easymock_static_call_instance_of_em_func_inside_header_3_a, 0,
           sizeof(easymock_static_call_instance_of_em_func_inside_header_3_a));
    memset(&easymock_static_params_expected_of_em_func_inside_header_3_a, 0,
           sizeof(easymock_static_params_expected_of_em_func_inside_header_3_a));
    memset(&easymock_static_params_received_of_em_func_inside_header_3_a, 0,
           sizeof(easymock_static_params_received_of_em_func_inside_header_3_a));
    ci = &easymock_static_call_instance_of_em_func_inside_header_3_a;
    ci->params_expected =
        &easymock_static_params_expected_of_em_func_inside_header_3_a;
    ci->params_received =
        &easymock_static_params_received_of_em_func_inside_header_3_a;
    ci->result =
        &easymock_static_result_of_em_func_inside_header_3_a;
    ci->func = &easymock_meta_func_of_em_func_inside_header_3_a;
    return ci;
}

static easymock_call_instance* easymock_get_static_em_func_inside_header_3_a()
{
    return easymock_static_ptr_call_instance_of_em_func_inside_header_3_a;
}

static easymock_call_instance* easymock_new_em_func_inside_header_3_a()
{
    easymock_call_instance* ci = NULL;
    if (easymock_is_started()) {
        ci = easymock_call_instance_create();
        ci->params_expected =
            easymock_create_params_of_em_func_inside_header_3_a();
        ci->params_received =
            easymock_create_params_of_em_func_inside_header_3_a();
        ci->result =
            easymock_create_result_of_em_func_inside_header_3_a();
        ci->func = &easymock_meta_func_of_em_func_inside_header_3_a;
        easymock_call_instance_push(ci);
    } else {
        ci = easymock_new_static_em_func_inside_header_3_a();
        easymock_static_ptr_call_instance_of_em_func_inside_header_3_a = ci;
    }
    return ci;
}

void easymock_ignore_and_return_em_func_inside_header_3_a(
    easymock_return_type_of_em_func_inside_header_3_a _em_return_value)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_a();
    _em_ci->prm_mode = EASYMOCK_PRM_IGNORE;
    _em_ci->act_mode = EASYMOCK_ACT_RETURN;
    easymock_assign_result_of_em_func_inside_header_3_a(
        _em_ci->result, _em_return_value);
}

void easymock_ignore_and_callback_em_func_inside_header_3_a(
    easymock_fn_callback_em_func_inside_header_3_a _em_fn_callback,
    void* _em_arg_cb)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_a();
    _em_ci->prm_mode = EASYMOCK_PRM_IGNORE;
    _em_ci->act_mode = EASYMOCK_ACT_CALLBACK;
    _em_ci->fn_callback = _em_fn_callback;
    _em_ci->arg_callback = _em_arg_cb;
}

void easymock_match_and_return_em_func_inside_header_3_a(
    int x,
    easymock_return_type_of_em_func_inside_header_3_a _em_return_value)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_a();
    _em_ci->prm_mode = EASYMOCK_PRM_MATCH;
    _em_ci->act_mode = EASYMOCK_ACT_RETURN;
    easymock_assign_params_of_em_func_inside_header_3_a(
        _em_ci->params_expected,
        x);
    easymock_assign_result_of_em_func_inside_header_3_a(
        _em_ci->result, _em_return_value);
}

void easymock_match_and_callback_em_func_inside_header_3_a(
    int x,
    easymock_fn_callback_em_func_inside_header_3_a _em_fn_callback,
    void* _em_arg_cb)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_a();
    _em_ci->prm_mode = EASYMOCK_PRM_MATCH;
    _em_ci->act_mode = EASYMOCK_ACT_CALLBACK;
    easymock_assign_params_of_em_func_inside_header_3_a(
        _em_ci->params_expected,
        x);
    _em_ci->fn_callback = _em_fn_callback;
    _em_ci->arg_callback = _em_arg_cb;
}

void easymock_check_and_return_em_func_inside_header_3_a(
    easymock_fn_check_em_func_inside_header_3_a _em_fn_check,
    void* _em_arg_ch,
    easymock_return_type_of_em_func_inside_header_3_a _em_return_value)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_a();
    _em_ci->prm_mode = EASYMOCK_PRM_CHECK;
    _em_ci->act_mode = EASYMOCK_ACT_RETURN;
    _em_ci->fn_check = _em_fn_check;
    _em_ci->arg_check = _em_arg_ch;
    easymock_assign_result_of_em_func_inside_header_3_a(
        _em_ci->result, _em_return_value);
}

void easymock_check_and_callback_em_func_inside_header_3_a(
    easymock_fn_check_em_func_inside_header_3_a _em_fn_check,
    void* _em_arg_ch,
    easymock_fn_callback_em_func_inside_header_3_a _em_fn_callback,
    void* _em_arg_cb)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3_a();
    _em_ci->prm_mode = EASYMOCK_PRM_CHECK;
    _em_ci->act_mode = EASYMOCK_ACT_CALLBACK;
    _em_ci->fn_check = _em_fn_check;
    _em_ci->fn_callback = _em_fn_callback;
    _em_ci->arg_check = _em_arg_ch;
    _em_ci->arg_callback = _em_arg_cb;
}

int em_func_inside_header_3_a(
    int x)
{
    static char _em_sparams[EASYMOCK_MSG_ERROR_LENGTH_MAX] =
        "    (no params)\n";

    easymock_call_instance* _em_ci = NULL;
    int _em_is_unexpected = 0;
    int _em_is_seq_call = 0;

    // 1) try to get a sequence-configured call instance
    _em_ci = easymock_call_instance_pop("em_func_inside_header_3_a");
    if (_em_ci) {
        easymock_nb_seq_calls_inc();
        _em_is_seq_call = 1;
    } else {
        // 2) try to get a static-configured call instance
        _em_ci = easymock_get_static_em_func_inside_header_3_a();
        if (_em_ci) {
            easymock_nb_stc_calls_inc();
        } else {
            // 3) get a dummy all-zero static call instance
            _em_ci = easymock_new_static_em_func_inside_header_3_a();
            _em_is_unexpected = easymock_is_started();
        }
    }
    assert(_em_ci);

    easymock_assign_params_of_em_func_inside_header_3_a(
        _em_ci->params_received,
        x);

    if (_em_is_unexpected) {
        // print the received params
        easymock_call_instance_print_params(
            _em_ci, _em_sparams, sizeof(_em_sparams));

        easymock_error(
            "%s: Called - UNEXPECTED!\n%s", "em_func_inside_header_3_a",
            _em_sparams);
    } else {
        if (_em_is_seq_call) {
            easymock_log("%s: Called - OK\n", "em_func_inside_header_3_a");
        }

        // === match params
        if (_em_ci->prm_mode == EASYMOCK_PRM_MATCH) {
            easymock_call_instance_match_params(_em_ci);
        }
        // === check params
        else if (_em_ci->prm_mode == EASYMOCK_PRM_CHECK) {
            assert(_em_ci->fn_check);
            int _em_rc = ((easymock_fn_check_em_func_inside_header_3_a)_em_ci->fn_check)(
                (easymock_params_of_em_func_inside_header_3_a*)_em_ci->params_received,
                _em_ci->arg_check);
            easymock_call_instance_print_params(
                _em_ci, _em_sparams, sizeof(_em_sparams));
            if (_em_rc == 0) {
                easymock_log(
                    "%s: Check - OK\n%s",
                    "em_func_inside_header_3_a", _em_sparams);
            } else {
                easymock_error(
                    "%s: Check - FAILED!\n%s",
                    "em_func_inside_header_3_a", _em_sparams);
            }
        }
        // === call the provided callback
        if (_em_ci->act_mode == EASYMOCK_ACT_CALLBACK) {
            assert(_em_ci->fn_callback);
            return ((easymock_fn_callback_em_func_inside_header_3_a)
                _em_ci->fn_callback)(
                    (easymock_params_of_em_func_inside_header_3_a*)
                    _em_ci->params_received,
                    _em_ci->arg_callback);
        }
    }
    // === return the result
    return ((easymock_result_of_em_func_inside_header_3_a*)
            _em_ci->result)->return_value;
}

//!
//! Mock for em_func_inside_header_3
//!

static easymock_param easymock_meta_params_of_em_func_inside_header_3[] =
{
    {
        .index = 1,
        .name = "x",
        .type = "int",
        .type_basic = "int",
        .offset = EASYMOCK_MEMBER_OFFSET(
            easymock_params_of_em_func_inside_header_3,
            x),
        .size = EASYMOCK_MEMBER_SIZE(
            easymock_params_of_em_func_inside_header_3,
            x),
        .fn_match = easymock_match_param_smart,
        .fn_print = easymock_print_param_smart,
    }
};

static easymock_params_of_em_func_inside_header_3*
easymock_create_params_of_em_func_inside_header_3()
{
    easymock_params_of_em_func_inside_header_3* _em_p = NULL;
    _em_p = malloc(sizeof(easymock_params_of_em_func_inside_header_3));
    memset(_em_p, 0, sizeof(easymock_params_of_em_func_inside_header_3));
    return _em_p;
}

static void easymock_destroy_params_of_em_func_inside_header_3(
    void* _em_params)
{
    easymock_params_of_em_func_inside_header_3* _em_p = _em_params;
    free(_em_p);
}

static void easymock_assign_params_of_em_func_inside_header_3(
    easymock_params_of_em_func_inside_header_3* _em_params,
    int x)
{
    _em_params->x = (int)x;
}

static easymock_func easymock_meta_func_of_em_func_inside_header_3 =
{
    .name = "em_func_inside_header_3",
    .params = easymock_meta_params_of_em_func_inside_header_3,
    .params_size = EASYMOCK_SIZEOF_ARRAY(
        easymock_meta_params_of_em_func_inside_header_3),
    .fn_destroy_params = easymock_destroy_params_of_em_func_inside_header_3
};

easymock_func* easymock_meta_of_em_func_inside_header_3()
{
    return &easymock_meta_func_of_em_func_inside_header_3;
}

static easymock_result_of_em_func_inside_header_3*
easymock_create_result_of_em_func_inside_header_3()
{
    easymock_result_of_em_func_inside_header_3* _em_result = NULL;
    _em_result = malloc(sizeof(easymock_result_of_em_func_inside_header_3));
    memset(_em_result, 0, sizeof(easymock_result_of_em_func_inside_header_3));
    return _em_result;
}

static void easymock_assign_result_of_em_func_inside_header_3(
    easymock_result_of_em_func_inside_header_3* _em_result,
    easymock_return_type_of_em_func_inside_header_3 _em_return_value)
{
    _em_result->return_value = _em_return_value;
}

static easymock_call_instance
easymock_static_call_instance_of_em_func_inside_header_3;

static easymock_call_instance*
easymock_static_ptr_call_instance_of_em_func_inside_header_3 = NULL;

static easymock_params_of_em_func_inside_header_3
easymock_static_params_expected_of_em_func_inside_header_3;

static easymock_params_of_em_func_inside_header_3
easymock_static_params_received_of_em_func_inside_header_3;

static easymock_result_of_em_func_inside_header_3
easymock_static_result_of_em_func_inside_header_3;

static easymock_call_instance* easymock_new_static_em_func_inside_header_3()
{
    easymock_call_instance* ci = NULL;
    memset(&easymock_static_call_instance_of_em_func_inside_header_3, 0,
           sizeof(easymock_static_call_instance_of_em_func_inside_header_3));
    memset(&easymock_static_params_expected_of_em_func_inside_header_3, 0,
           sizeof(easymock_static_params_expected_of_em_func_inside_header_3));
    memset(&easymock_static_params_received_of_em_func_inside_header_3, 0,
           sizeof(easymock_static_params_received_of_em_func_inside_header_3));
    ci = &easymock_static_call_instance_of_em_func_inside_header_3;
    ci->params_expected =
        &easymock_static_params_expected_of_em_func_inside_header_3;
    ci->params_received =
        &easymock_static_params_received_of_em_func_inside_header_3;
    ci->result =
        &easymock_static_result_of_em_func_inside_header_3;
    ci->func = &easymock_meta_func_of_em_func_inside_header_3;
    return ci;
}

static easymock_call_instance* easymock_get_static_em_func_inside_header_3()
{
    return easymock_static_ptr_call_instance_of_em_func_inside_header_3;
}

static easymock_call_instance* easymock_new_em_func_inside_header_3()
{
    easymock_call_instance* ci = NULL;
    if (easymock_is_started()) {
        ci = easymock_call_instance_create();
        ci->params_expected =
            easymock_create_params_of_em_func_inside_header_3();
        ci->params_received =
            easymock_create_params_of_em_func_inside_header_3();
        ci->result =
            easymock_create_result_of_em_func_inside_header_3();
        ci->func = &easymock_meta_func_of_em_func_inside_header_3;
        easymock_call_instance_push(ci);
    } else {
        ci = easymock_new_static_em_func_inside_header_3();
        easymock_static_ptr_call_instance_of_em_func_inside_header_3 = ci;
    }
    return ci;
}

void easymock_ignore_and_return_em_func_inside_header_3(
    easymock_return_type_of_em_func_inside_header_3 _em_return_value)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3();
    _em_ci->prm_mode = EASYMOCK_PRM_IGNORE;
    _em_ci->act_mode = EASYMOCK_ACT_RETURN;
    easymock_assign_result_of_em_func_inside_header_3(
        _em_ci->result, _em_return_value);
}

void easymock_ignore_and_callback_em_func_inside_header_3(
    easymock_fn_callback_em_func_inside_header_3 _em_fn_callback,
    void* _em_arg_cb)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3();
    _em_ci->prm_mode = EASYMOCK_PRM_IGNORE;
    _em_ci->act_mode = EASYMOCK_ACT_CALLBACK;
    _em_ci->fn_callback = _em_fn_callback;
    _em_ci->arg_callback = _em_arg_cb;
}

void easymock_match_and_return_em_func_inside_header_3(
    int x,
    easymock_return_type_of_em_func_inside_header_3 _em_return_value)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3();
    _em_ci->prm_mode = EASYMOCK_PRM_MATCH;
    _em_ci->act_mode = EASYMOCK_ACT_RETURN;
    easymock_assign_params_of_em_func_inside_header_3(
        _em_ci->params_expected,
        x);
    easymock_assign_result_of_em_func_inside_header_3(
        _em_ci->result, _em_return_value);
}

void easymock_match_and_callback_em_func_inside_header_3(
    int x,
    easymock_fn_callback_em_func_inside_header_3 _em_fn_callback,
    void* _em_arg_cb)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3();
    _em_ci->prm_mode = EASYMOCK_PRM_MATCH;
    _em_ci->act_mode = EASYMOCK_ACT_CALLBACK;
    easymock_assign_params_of_em_func_inside_header_3(
        _em_ci->params_expected,
        x);
    _em_ci->fn_callback = _em_fn_callback;
    _em_ci->arg_callback = _em_arg_cb;
}

void easymock_check_and_return_em_func_inside_header_3(
    easymock_fn_check_em_func_inside_header_3 _em_fn_check,
    void* _em_arg_ch,
    easymock_return_type_of_em_func_inside_header_3 _em_return_value)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3();
    _em_ci->prm_mode = EASYMOCK_PRM_CHECK;
    _em_ci->act_mode = EASYMOCK_ACT_RETURN;
    _em_ci->fn_check = _em_fn_check;
    _em_ci->arg_check = _em_arg_ch;
    easymock_assign_result_of_em_func_inside_header_3(
        _em_ci->result, _em_return_value);
}

void easymock_check_and_callback_em_func_inside_header_3(
    easymock_fn_check_em_func_inside_header_3 _em_fn_check,
    void* _em_arg_ch,
    easymock_fn_callback_em_func_inside_header_3 _em_fn_callback,
    void* _em_arg_cb)
{
    easymock_call_instance* _em_ci = easymock_new_em_func_inside_header_3();
    _em_ci->prm_mode = EASYMOCK_PRM_CHECK;
    _em_ci->act_mode = EASYMOCK_ACT_CALLBACK;
    _em_ci->fn_check = _em_fn_check;
    _em_ci->fn_callback = _em_fn_callback;
    _em_ci->arg_check = _em_arg_ch;
    _em_ci->arg_callback = _em_arg_cb;
}

int em_func_inside_header_3(
    int x)
{
    static char _em_sparams[EASYMOCK_MSG_ERROR_LENGTH_MAX] =
        "    (no params)\n";

    easymock_call_instance* _em_ci = NULL;
    int _em_is_unexpected = 0;
    int _em_is_seq_call = 0;

    // 1) try to get a sequence-configured call instance
    _em_ci = easymock_call_instance_pop("em_func_inside_header_3");
    if (_em_ci) {
        easymock_nb_seq_calls_inc();
        _em_is_seq_call = 1;
    } else {
        // 2) try to get a static-configured call instance
        _em_ci = easymock_get_static_em_func_inside_header_3();
        if (_em_ci) {
            easymock_nb_stc_calls_inc();
        } else {
            // 3) get a dummy all-zero static call instance
            _em_ci = easymock_new_static_em_func_inside_header_3();
            _em_is_unexpected = easymock_is_started();
        }
    }
    assert(_em_ci);

    easymock_assign_params_of_em_func_inside_header_3(
        _em_ci->params_received,
        x);

    if (_em_is_unexpected) {
        // print the received params
        easymock_call_instance_print_params(
            _em_ci, _em_sparams, sizeof(_em_sparams));

        easymock_error(
            "%s: Called - UNEXPECTED!\n%s", "em_func_inside_header_3",
            _em_sparams);
    } else {
        if (_em_is_seq_call) {
            easymock_log("%s: Called - OK\n", "em_func_inside_header_3");
        }

        // === match params
        if (_em_ci->prm_mode == EASYMOCK_PRM_MATCH) {
            easymock_call_instance_match_params(_em_ci);
        }
        // === check params
        else if (_em_ci->prm_mode == EASYMOCK_PRM_CHECK) {
            assert(_em_ci->fn_check);
            int _em_rc = ((easymock_fn_check_em_func_inside_header_3)_em_ci->fn_check)(
                (easymock_params_of_em_func_inside_header_3*)_em_ci->params_received,
                _em_ci->arg_check);
            easymock_call_instance_print_params(
                _em_ci, _em_sparams, sizeof(_em_sparams));
            if (_em_rc == 0) {
                easymock_log(
                    "%s: Check - OK\n%s",
                    "em_func_inside_header_3", _em_sparams);
            } else {
                easymock_error(
                    "%s: Check - FAILED!\n%s",
                    "em_func_inside_header_3", _em_sparams);
            }
        }
        // === call the provided callback
        if (_em_ci->act_mode == EASYMOCK_ACT_CALLBACK) {
            assert(_em_ci->fn_callback);
            return ((easymock_fn_callback_em_func_inside_header_3)
                _em_ci->fn_callback)(
                    (easymock_params_of_em_func_inside_header_3*)
                    _em_ci->params_received,
                    _em_ci->arg_callback);
        }
    }
    // === return the result
    return ((easymock_result_of_em_func_inside_header_3*)
            _em_ci->result)->return_value;
}
