#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

#define s21_SIZE_T unsigned long long
#define s21_NULL ((void *)0)
#define SIZE 4096
/// sscanf
#define N 1000
#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0

#define S21_MAX_LLINT 9223372036854775807
#define S21_MAX_LINT 2147483647

#define NONE 0
#define SHORT_SHORT 1
#define SHORT_INT 2
#define LONG 3
#define LONG_LONG 4
#define LONG_DOUBLE 5

#define UNSIGNED 6

void *s21_memchr(const void *str, int c, s21_SIZE_T n);

int s21_memcmp(const void *str1, const void *str2, s21_SIZE_T n);

void *s21_memcpy(void *dest, const void *str, s21_SIZE_T n);

void *s21_memmove(void *dest, const void *str, s21_SIZE_T n);

void *s21_memset(void *str, int ch, s21_SIZE_T n);

char *s21_strcat(char *dest, const char *src);

char *s21_strncat(char *dest, const char *src, s21_SIZE_T n);

char *s21_strchr(const char *str, int c);

int s21_strcmp(const char *str1, const char *str2);

int s21_strncmp(const char *str1, const char *str2, s21_SIZE_T n);

// special string processing functions

void *s21_insert(const char *src, const char *str, s21_SIZE_T start_index);

char *s21_strcpy(char *dest, const char *src);

char *s21_strncpy(char *dest, const char *src, s21_SIZE_T n);

s21_SIZE_T s21_strcspn(const char *str1, const char *str2);

char *s21_strerror(int errnum);

s21_SIZE_T s21_strlen(const char *str);

char *s21_strpbrk(const char *str1, const char *str2);

char *s21_strrchr(const char *str, int c);

s21_SIZE_T s21_strspn(const char *str1, const char *str2);

char *s21_strstr(const char *haystack, const char *needle);

char *s21_strtok(char *str, const char *delim);

void *s21_to_upper(const char *str);

void *s21_to_lower(const char *str);

void *s21_trim(const char *src, const char *trim_chars);

void s21_itoc(int number, char *result);

typedef struct options {
  // %[*][width][length]specifier
  int suppress;
  int width;
  int length;
  int sign;
  // flags
  int null_buf;
  int percent;
  int error;
  int withoutDigit;
  int invalid;
  int iterStr;
  int read;
  int null_read;
} spec;

int is_space(char c);
int is_digit(char c);
int is_A_to_F(char c);
int is_a_to_f(char c);
void skip_spaces(char *buf, spec *opt);
int is_null(char c);

void reset_options(spec *opt);

// int
long int s21_integer(char *buf, spec *opt, int base);
unsigned long int s21_unsigned_integer(char *buf, spec *opt, int base);
long long int s21_ll_integer(char *buf, spec *opt, int base);
unsigned long long int s21_unsigned_ll_integer(char *buf, spec *opt, int base);
int options_integer(char *buf, spec *opt, int base, va_list *args);
// char
char s21_char(char *buf, spec *opt);
int options_char(char *buf, spec *opt, va_list *args);
// n
int options_n(spec *opt, va_list *args);
// pointer
int options_pointer(char *buf, spec *opt, va_list *args);
// string
char *s21_str(char *buf, spec *opt);
int options_str(char *buf, spec *opt, va_list *args);
// float
long double s21_long_double(char *buf, spec *opt);
int options_float(char *buf, spec *opt, va_list *args);

int pars(char *buf, const char *format, spec *opt, va_list *args);
int s21_sscanf(char *buf, const char *format, ...);

/////////////////////// sprintf

typedef struct {
  int stringError;  // для вывода ошибок

  int minus;  // sprintf Флаги |1|
  int plus;   // sprintf Флаги |2|
  int space;  // sprintf Флаги |3|
  int grill;  // sprintf Флаги |4|
  int zero;   // sprintf Флаги |5|

  int minNum;  // sprintf Ширина (для целых чисел) |1|

  int fractionalMinNum;  // sprintf Точность (для дробных чисел) |1|
  int fractionalZero;

  char length;  // sprintf Длина (доп флаг для (i, d, o, u, x и X))

  char specifier;  // sprintf Спецификаторы (основной флаг для printf)

  char mass[SIZE];  // итоговый массив после применения спецификатора и всех
                    // флагов
} ParserString;

// %[флаги][ширина][.точность][длина]спецификатор

int s21_sprintf(char *str, const char *format, ...);

void WideCharacter(wchar_t *pwcs, char *line);

void WideSymbol(wchar_t wc, int *n);

void IntToChar(long int n, char *line);

void UnsignedIntToChar(unsigned long int n, char *line);

void ReverseChar(char *line);

void flag_d(long int a, ParserString *parser);

void flag_s(char *line, ParserString *parser);

void flag_c(int ArgvC, ParserString *parser);

void flag_f(long double adress, ParserString *parser);

void flag_xX(long int a, ParserString *parser);

void flag_o(long int a, ParserString *parser);

void flag_p(void *adress, ParserString *parser);

void flag_eE(long double adress, ParserString *parser);

void flag_gG(double adress, ParserString *parser);

void flag_f_converter(long double adress, ParserString *parser);

void flag_e_converter(long double adress, ParserString *parser);

void post_converter(int znak, ParserString *parser, char *copyMass);

void round_e(ParserString *parser);

#if defined(__linux__)
#define MAX_ERROR 134
#define MASS_ERROR                                      \
  {"Success",                                           \
   "Operation not permitted",                           \
   "No such file or directory",                         \
   "No such process",                                   \
   "Interrupted system call",                           \
   "Input/output error",                                \
   "No such device or address",                         \
   "Argument list too long",                            \
   "Exec format error",                                 \
   "Bad file descriptor",                               \
   "No child processes",                                \
   "Resource temporarily unavailable",                  \
   "Cannot allocate memory",                            \
   "Permission denied",                                 \
   "Bad address",                                       \
   "Block device required",                             \
   "Device or resource busy",                           \
   "File exists",                                       \
   "Invalid cross-device link",                         \
   "No such device",                                    \
   "Not a directory",                                   \
   "Is a directory",                                    \
   "Invalid argument",                                  \
   "Too many open files in system",                     \
   "Too many open files",                               \
   "Inappropriate ioctl for device",                    \
   "Text file busy",                                    \
   "File too large",                                    \
   "No space left on device",                           \
   "Illegal seek",                                      \
   "Read-only file system",                             \
   "Too many links",                                    \
   "Broken pipe",                                       \
   "Numerical argument out of domain",                  \
   "Numerical result out of range",                     \
   "Resource deadlock avoided",                         \
   "File name too long",                                \
   "No locks available",                                \
   "Function not implemented",                          \
   "Directory not empty",                               \
   "Too many levels of symbolic links",                 \
   "Unknown error 41",                                  \
   "No message of desired type",                        \
   "Identifier removed",                                \
   "Channel number out of range",                       \
   "Level 2 not synchronized",                          \
   "Level 3 halted",                                    \
   "Level 3 reset",                                     \
   "Link number out of range",                          \
   "Protocol driver not attached",                      \
   "No CSI structure available",                        \
   "Level 2 halted",                                    \
   "Invalid exchange",                                  \
   "Invalid request descriptor",                        \
   "Exchange full",                                     \
   "No anode",                                          \
   "Invalid request code",                              \
   "Invalid slot",                                      \
   "Unknown error 58",                                  \
   "Bad font file format",                              \
   "Device not a stream",                               \
   "No data available",                                 \
   "Timer expired",                                     \
   "Out of streams resources",                          \
   "Machine is not on the network",                     \
   "Package not installed",                             \
   "Object is remote",                                  \
   "Link has been severed",                             \
   "Advertise error",                                   \
   "Srmount error",                                     \
   "Communication error on send",                       \
   "Protocol error",                                    \
   "Multihop attempted",                                \
   "RFS specific error",                                \
   "Bad message",                                       \
   "Value too large for defined data type",             \
   "Name not unique on network",                        \
   "File descriptor in bad state",                      \
   "Remote address changed",                            \
   "Can not access a needed shared library",            \
   "Accessing a corrupted shared library",              \
   ".lib section in a.out corrupted",                   \
   "Attempting to link in too many shared libraries",   \
   "Cannot exec a shared library directly",             \
   "Invalid or incomplete multibyte or wide character", \
   "Interrupted system call should be restarted",       \
   "Streams pipe error",                                \
   "Too many users",                                    \
   "Socket operation on non-socket",                    \
   "Destination address required",                      \
   "Message too long",                                  \
   "Protocol wrong type for socket",                    \
   "Protocol not available",                            \
   "Protocol not supported",                            \
   "Socket type not supported",                         \
   "Operation not supported",                           \
   "Protocol family not supported",                     \
   "Address family not supported by protocol",          \
   "Address already in use",                            \
   "Cannot assign requested address",                   \
   "Network is down",                                   \
   "Network is unreachable",                            \
   "Network dropped connection on reset",               \
   "Software caused connection abort",                  \
   "Connection reset by peer",                          \
   "No buffer space available",                         \
   "Transport endpoint is already connected",           \
   "Transport endpoint is not connected",               \
   "Cannot send after transport endpoint shutdown",     \
   "Too many references: cannot splice",                \
   "Connection timed out",                              \
   "Connection refused",                                \
   "Host is down",                                      \
   "No route to host",                                  \
   "Operation already in progress",                     \
   "Operation now in progress",                         \
   "Stale file handle",                                 \
   "Structure needs cleaning",                          \
   "Not a XENIX named type file",                       \
   "No XENIX semaphores available",                     \
   "Is a named type file",                              \
   "Remote I/O error",                                  \
   "Disk quota exceeded",                               \
   "No medium found",                                   \
   "Wrong medium type",                                 \
   "Operation canceled",                                \
   "Required key not available",                        \
   "Key has expired",                                   \
   "Key has been revoked",                              \
   "Key was rejected by service",                       \
   "Owner died",                                        \
   "State not recoverable",                             \
   "Operation not possible due to RF-kill",             \
   "Memory page has hardware error"};
#endif

#if defined(__APPLE__)
#define MAX_ERROR 107
#define MASS_ERROR                                    \
  {"Undefined error: 0",                              \
   "Operation not permitted",                         \
   "No such file or directory",                       \
   "No such process",                                 \
   "Interrupted system call",                         \
   "Input/output error",                              \
   "Device not configured",                           \
   "Argument list too long",                          \
   "Exec format error",                               \
   "Bad file descriptor",                             \
   "No child processes",                              \
   "Resource deadlock avoided",                       \
   "Cannot allocate memory",                          \
   "Permission denied",                               \
   "Bad address",                                     \
   "Block device required",                           \
   "Resource busy",                                   \
   "File exists",                                     \
   "Cross-device link",                               \
   "Operation not supported by device",               \
   "Not a directory",                                 \
   "Is a directory",                                  \
   "Invalid argument",                                \
   "Too many open files in system",                   \
   "Too many open files",                             \
   "Inappropriate ioctl for device",                  \
   "Text file busy",                                  \
   "File too large",                                  \
   "No space left on device",                         \
   "Illegal seek",                                    \
   "Read-only file system",                           \
   "Too many links",                                  \
   "Broken pipe",                                     \
   "Numerical argument out of domain",                \
   "Result too large",                                \
   "Resource temporarily unavailable",                \
   "Operation now in progress",                       \
   "Operation already in progress",                   \
   "Socket operation on non-socket",                  \
   "Destination address required",                    \
   "Message too long",                                \
   "Protocol wrong type for socket",                  \
   "Protocol not available",                          \
   "Protocol not supported",                          \
   "Socket type not supported",                       \
   "Operation not supported",                         \
   "Protocol family not supported",                   \
   "Address family not supported by protocol family", \
   "Address already in use",                          \
   "Can't assign requested address",                  \
   "Network is down",                                 \
   "Network is unreachable",                          \
   "Network dropped connection on reset",             \
   "Software caused connection abort",                \
   "Connection reset by peer",                        \
   "No buffer space available",                       \
   "Socket is already connected",                     \
   "Socket is not connected",                         \
   "Can\'t send after socket shutdown",               \
   "Too many references: can\'t splice",              \
   "Operation timed out",                             \
   "Connection refused",                              \
   "Too many levels of symbolic links",               \
   "File name too long",                              \
   "Host is down",                                    \
   "No route to host",                                \
   "Directory not empty",                             \
   "Too many processes",                              \
   "Too many users",                                  \
   "Disc quota exceeded",                             \
   "Stale NFS file handle",                           \
   "Too many levels of remote in path",               \
   "RPC struct is bad",                               \
   "RPC version wrong",                               \
   "RPC prog. not avail",                             \
   "Program version wrong",                           \
   "Bad procedure for program",                       \
   "No locks available",                              \
   "Function not implemented",                        \
   "Inappropriate file type or format",               \
   "Authentication error",                            \
   "Need authenticator",                              \
   "Device power is off",                             \
   "Device error",                                    \
   "Value too large to be stored in data type",       \
   "Bad executable (or shared library)",              \
   "Bad CPU type in executable",                      \
   "Shared library version mismatch",                 \
   "Malformed Mach-o file",                           \
   "Operation canceled",                              \
   "Identifier removed",                              \
   "No message of desired type",                      \
   "Illegal byte sequence",                           \
   "Attribute not found",                             \
   "Bad message",                                     \
   "EMULTIHOP (Reserved)",                            \
   "No message available on STREAM",                  \
   "ENOLINK (Reserved)",                              \
   "No STREAM resources",                             \
   "Not a STREAM",                                    \
   "Protocol error",                                  \
   "STREAM ioctl timeout",                            \
   "Operation not supported on socket",               \
   "Policy not found",                                \
   "State not recoverable",                           \
   "Previous owner died",                             \
   "Interface output queue is full"};
#endif

#endif  // S21_STRING_H
