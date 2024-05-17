#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
size_t slen(const char *s)
{
    const char *p = s;
    while (*p)
    {
        p++;
    }
    return p - s;
}
char *schr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == (char)c)
        {
            return (char *)s;
        }
        s++;
    }
    return NULL;
}

int sncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2))
    {
        ++s1;
        ++s2;
        --n;
    }
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
}

char *sncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    for (; i < n; i++)
    {
        dest[i] = '\0';
    }
    return dest;
}

size_t scspn(const char *s, const char *reject)
{
    const char *p, *r;
    size_t count = 0;
    for (p = s; *p != '\0'; p++)
    {
        for (r = reject; *r != '\0'; r++)
        {
            if (*p == *r)
            {
                return count;
            }
        }
        count++;
    }
    return count;
}

char *stok(char *str, const char *delim)
{
    static char *last;
    if (str == NULL)
    {
        str = last;
    }
    if (str == NULL)
    {
        return NULL;
    }

    // Skip leading delimiters
    while (*str && schr(delim, *str))
    {
        str++;
    }
    if (*str == '\0')
    {
        last = NULL;
        return NULL;
    }

    char *token = str;
    while (*str && !schr(delim, *str))
    {
        str++;
    }
    if (*str)
    {
        *str = '\0';
        last = str + 1;
    }
    else
    {
        last = NULL;
    }

    return token;
}
