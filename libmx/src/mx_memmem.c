#include "libmx.h"

/**
 * @NAME Locate block of bytes
 * @DESCRIPTION Create a function that has the same behavior
 * as the standard libc function memmem.\n
 * @note \n
 */

void *mx_memmem(const void *big, size_t big_len,
                const void *little, size_t little_len) {
    mx_printint((int)little_len);
    mx_printchar('\n');
    if (little_len == 0) return (void *)big;
    if (big_len < little_len) return NULL;
    const unsigned char *b = (const unsigned char *)big;
    const unsigned char *l = (const unsigned char *)little;
    for (size_t i = 0; i <= big_len - little_len; ++i)
        if (mx_memcmp(b + i, l, little_len) == 0)
            return (void *)(b + i);
    return NULL;
}
