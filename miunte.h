#ifndef MIUNTE_H
#define MIUNTE_H

#include <stdio.h>

#ifndef MIUNTE_STOP_ON_FAILURE
#  define MIUNTE_STOP_ON_FAILURE (0)
#endif

// #if (!defined MIUNTE_TA_PASSED && !defined MIUNTE_TA_FAILED && !defined
// MIUNTE_TA_CLEAR)
#ifdef MIUNTE_NO_TA
#  define MIUNTE_TA_PASSED ""
#  define MIUNTE_TA_FAILED ""
#  define MILO_TA_CLEAR    ""
#else
#  define MIUNTE_TA_PASSED "\033[0;32m"
#  define MIUNTE_TA_FAILED "\033[0;31m"
#  define MIUNTE_TA_CLEAR  "\033[0m"
#endif
// #endif

typedef struct MiunteResult {
    char const *const fn_name;
    char const *const err_msg;
} MiunteResult;
typedef MiunteResult (*MiunteTest)();

#define miunte_test(setup, teardown, ...)                                      \
    {                                                                          \
        MiunteTest const _setup = (setup), _teardown = (teardown);             \
                                                                               \
        MiunteTest const tests[] = __VA_ARGS__;                                \
        size_t const test_count = sizeof(tests) / sizeof(*tests);              \
                                                                               \
        int main_result = 0;                                                   \
        for (MiunteTest const *test = tests; test < tests + test_count;        \
             test++) {                                                         \
            if (_setup != NULL) {                                              \
                MiunteResult const result = _setup();                          \
                if (result.err_msg != NULL) {                                  \
                    printf(                                                    \
                        "%s " MIUNTE_TA_FAILED "failed: %s" MIUNTE_TA_CLEAR    \
                        "\n",                                                  \
                        result.fn_name,                                        \
                        result.err_msg                                         \
                    );                                                         \
                    return 1;                                                  \
                }                                                              \
            }                                                                  \
            {                                                                  \
                MiunteResult const result = (*test)();                         \
                if (result.err_msg != NULL) {                                  \
                    printf(                                                    \
                        "%s " MIUNTE_TA_FAILED "failed: %s" MIUNTE_TA_CLEAR    \
                        "\n",                                                  \
                        result.fn_name,                                        \
                        result.err_msg                                         \
                    );                                                         \
                    if (MIUNTE_STOP_ON_FAILURE) {                              \
                        return 1;                                              \
                    } else {                                                   \
                        main_result = 1;                                       \
                    }                                                          \
                } else {                                                       \
                    printf(                                                    \
                        "%s " MIUNTE_TA_PASSED "passed!" MIUNTE_TA_CLEAR "\n", \
                        result.fn_name                                         \
                    );                                                         \
                }                                                              \
            }                                                                  \
            if (_teardown != NULL) {                                           \
                MiunteResult const result = _teardown();                       \
                if (result.err_msg != NULL) {                                  \
                    printf(                                                    \
                        "%s " MIUNTE_TA_FAILED "failed: %s" MIUNTE_TA_CLEAR    \
                        "\n",                                                  \
                        result.fn_name,                                        \
                        result.err_msg                                         \
                    );                                                         \
                    if (MIUNTE_STOP_ON_FAILURE) {                              \
                        return 1;                                              \
                    } else {                                                   \
                        main_result = 1;                                       \
                    }                                                          \
                }                                                              \
            }                                                                  \
        }                                                                      \
                                                                               \
        return main_result;                                                    \
    }                                                                          \
    ((void)0)

#define miunte_expect(cond, message)                                           \
    {                                                                          \
        if (!(cond))                                                           \
            return (MiunteResult){.fn_name = __func__, .err_msg = (message)};  \
    }                                                                          \
    ((void)0)

#define miunte_pass()                                                          \
    { return (MiunteResult){.fn_name = __func__}; }                            \
    ((void)0)

#endif
