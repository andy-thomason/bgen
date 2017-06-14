#ifndef MEM_H
#define MEM_H

#include <stdlib.h>
#include <string.h>

#include "../types.h"

// Duplicate a string.
inline static byte* ft_strdup(const byte *src)
{
    byte *str;
    byte *p;
    int   len = 0;

    while (src[len]) len++;
    str = malloc(len + 1);
    p   = str;

    while (*src) *p++ = *src++;
    *p = '\0';
    return str;
}

// Duplicate a string.
inline static byte* ft_strndup(const byte *src, inti size)
{
    byte *str = malloc(size);

    memcpy(str, src, size);
    return str;
}

inline static void MEMCPY(void *dst, byte **src, inti n)
{
    memcpy(dst, *src, n);
    *src = *src + n;
}

#endif /* end of include guard: MEM_H */
