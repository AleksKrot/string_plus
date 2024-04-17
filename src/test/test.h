#ifndef TEST_H
#define TEST_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

void run_testcase(Suite *testscase, int counter_testcase);
void run_tests();

Suite *s21_memchr_suite(void);
Suite *s21_memcmp_suite(void);
Suite *s21_memcpy_suite(void);
Suite *s21_memset_suite(void);
Suite *s21_strncat_suite(void);
Suite *s21_strchr_suite(void);
Suite *s21_strncmp_suite(void);
Suite *s21_strncpy_suite(void);

Suite *s21_strlen_suite(void);

Suite *s21_sprintf_d_suite(void);
#endif