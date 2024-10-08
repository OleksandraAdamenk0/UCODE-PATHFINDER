#include "../inc/pathfinder.h"

char *mx_ut_cool_read_line(int fd, int *size, int *eof, char delim) {
    char buffer[256];
    *size = 0;
    *eof = 0;
    int res = (int)read(fd, &buffer[*size], 1);
    while (res > 0) {
        if (buffer[*size] == delim) {
            char *str = mx_strnew(*size);
            mx_strncpy(str, buffer, *size);
            return str;
        }
        (*size)++;
        res = (int)read(fd, &buffer[*size], 1);
    }
    *eof = 1;
    return NULL;
}
