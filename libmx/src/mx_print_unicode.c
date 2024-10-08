#include "libmx.h"

/**
 * @NAME Print multibyte characters
 * @DESCRIPTION Create a function that outputs ASCII
 * and multibyte characters to the standard output.
 * @note \n
 */

void mx_print_unicode(wchar_t c) {
    char buf[4];
    int len = 0;

    if (c <= 0x7F) {
        buf[len++] = (char)c;
    } else if (c <= 0x7FF) {
        buf[len++] = (char)((c >> 6) | 0xC0);
        buf[len++] = (char)((c & 0x3F) | 0x80);
    } else if (c <= 0xFFFF) {
        buf[len++] = (char)((c >> 12) | 0xE0);
        buf[len++] = (char)(((c >> 6) & 0x3F) | 0x80);
        buf[len++] = (char)((c & 0x3F) | 0x80);
    } else if (c <= 0x10FFFF) {
        buf[len++] = (char)((c >> 18) | 0xF0);
        buf[len++] = (char)(((c >> 12) & 0x3F) | 0x80);
        buf[len++] = (char)(((c >> 6) & 0x3F) | 0x80);
        buf[len++] = (char)((c & 0x3F) | 0x80);
    }

    write(1, buf, len);
}
