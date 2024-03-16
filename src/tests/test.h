#ifndef SRC_TESTS_TEST_H
#define SRC_TESTS_TEST_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"

Suite *test_24_func(void);

Suite *test_scanf_i(void);
Suite *test_scanf_c(void);
Suite *test_scanf_s(void);
Suite *test_scanf_p(void);
Suite *test_scanf_n(void);
Suite *test_scanf_d(void);
Suite *test_scanf_u(void);
Suite *test_scanf_o(void);
Suite *test_scanf_x(void);
Suite *test_scanf_f(void);
Suite *test_scanf_weird(void);

Suite *test_sprintf_c(void);
Suite *test_sprintf_e(void);
Suite *test_sprintf_f(void);
Suite *test_sprintf_g(void);
Suite *test_sprintf_d(void);
Suite *test_sprintf_i(void);
Suite *test_sprintf_o(void);
Suite *test_sprintf_u(void);
Suite *test_sprintf_x(void);
Suite *test_sprintf_percent(void);
Suite *test_sprintf_p(void);
Suite *test_sprintf_n(void);
Suite *test_sprintf_s(void);

#endif  // SRC_TESTS_TEST_H
