#ifndef MIUNTE_H
#define MIUNTE_H

#include <stdio.h>

#ifndef MIUNTE_STOP_ON_FAILURE
#  define MIUNTE_STOP_ON_FAILURE (0)
#endif

#if (!defined MIUNTE_TA_PASSED && !defined MIUNTE_TA_FAILED && !defined MIUNTE_TA_CLEAR)
#  ifdef MIUNTE_NO_TA
#    define MIUNTE_TA_PASSED ""
#    define MIUNTE_TA_FAILED ""
#    define MILO_TA_CLEAR    ""
#  else
#    define MIUNTE_TA_PASSED "\033[0;32m"
#    define MIUNTE_TA_FAILED "\033[0;31m"
#    define MIUNTE_TA_CLEAR  "\033[0m"
#  endif
#endif

typedef struct MiunteResult {
    char const *fn_name;
    char const *err_msg;
    int err_line;
} MiunteResult;

typedef MiunteResult MiunteTest(void);

static inline int miunte_run(
    MiunteTest *const setup,
    MiunteTest *const teardown,
    MiunteTest *const tests[],
    size_t const tests_len
) {
    int res = 0;

    for (MiunteTest *const *test_ptr = tests; test_ptr < tests + tests_len; test_ptr++) {
        if (setup) {
            MiunteResult const setup_res = setup();
            if (setup_res.err_msg) {
                printf(
                    "%s " MIUNTE_TA_FAILED "setup failed at line %i: %s" MIUNTE_TA_CLEAR "\n",
                    setup_res.fn_name,
                    setup_res.err_line,
                    setup_res.err_msg
                );
                res = 1;
                if (MIUNTE_STOP_ON_FAILURE) return res;
            }
        }

        MiunteResult const test_res = (*test_ptr)();
        if (test_res.err_msg) {
            printf(
                "%s " MIUNTE_TA_FAILED "failed at line %i: %s" MIUNTE_TA_CLEAR "\n",
                test_res.fn_name,
                test_res.err_line,
                test_res.err_msg
            );

            res = 1;
            if (MIUNTE_STOP_ON_FAILURE) return res;
        } else {
            printf("%s " MIUNTE_TA_PASSED "passed" MIUNTE_TA_CLEAR "\n", test_res.fn_name);
        }

        if (teardown) {
            MiunteResult const teardown_res = teardown();
            if (teardown_res.err_msg != NULL) {
                printf(
                    "%s " MIUNTE_TA_FAILED "teardown failed at line %i: %s" MIUNTE_TA_CLEAR "\n",
                    teardown_res.fn_name,
                    teardown_res.err_line,
                    teardown_res.err_msg
                );

                res = 1;
                if (MIUNTE_STOP_ON_FAILURE) return res;
            }
        }
    }

    return res;
}

/// Runs all tests, surrounding each with `setup` and `teardown`.
///   `setup` - function to call before every test
///   `teardown` - function to call after every test
///   `...` - array of test functions
#define MIUNTE_RUN(SETUP_, TEARDOWN_, ...)                                                          \
    {                                                                                               \
        MiunteTest *const tests[] = __VA_ARGS__;                                                    \
        miunte_run((SETUP_), (TEARDOWN_), tests, sizeof(tests) / sizeof(tests[0]));                 \
    }                                                                                               \
    ((void)0)

/// If `cond` is false, mark test as failed with `msg`.
///   `cond` - condition to test
///   `msg`
#define MIUNTE_EXPECT(COND_, MSG_)                                                                  \
    {                                                                                               \
        if (!(COND_))                                                                               \
            return (MiunteResult){.fn_name = __func__, .err_msg = (MSG_), .err_line = __LINE__};    \
    }                                                                                               \
    ((void)0)

/// Mark test as passed.
#define MIUNTE_PASS()                                                                               \
    { return (MiunteResult){.fn_name = __func__}; }                                                 \
    ((void)0)

#endif
