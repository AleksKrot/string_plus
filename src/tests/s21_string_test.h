#ifndef S21_STRING_TEST_H
#define S21_STRING_TEST_H

#include "s21_string.h"
#include "s21_sprintf.h"

#include <check.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Suite *s21_memchr_suite(void);
Suite *s21_memcmp_suite(void);
Suite *s21_memcpy_suite(void);
Suite *s21_memset_suite(void);
Suite *s21_strchr_suite(void);
Suite *s21_strrchr_suite(void);
Suite *s21_strncat_suite(void);
Suite *s21_strncmp_suite(void);
Suite *s21_strncpy_suite(void);
Suite *s21_sprintf_suite(void);

#endif