#include "s21_string.h"
#include <string.h>

void test(char *str1, char *str2, size_t size) {
  s21_memcpy((void *)str1, (void *)str2, size);
  memcpy((void *)str1, (void *)str2, size);
  // printf("%d %d\n", res1, res2);
}

int main() {
  // test("                       ", "1232", 4);

  char str1[256] = "This is a test string";
  char str1_copy[256] = "This is a test string";
  const char str2[4] = "";

  s21_strncat(str1, str2, 4);
  printf("%s\n", str1);
  strncat(str1_copy, str2, 4);
  printf("%s", str1_copy);
}