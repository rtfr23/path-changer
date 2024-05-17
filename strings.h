#ifndef STRINGS_H
#define STRINGS_H
#include <stddef.h>
int sncmp(const char *s1, const char *s2, size_t n);
char *schr(const char *s, int c);
char *sncpy(char *dest, const char *src, size_t n);
size_t scspn(const char *s, const char *reject);
char *stok(char *str, const char *delim);
size_t slen(const char *s);
#endif
