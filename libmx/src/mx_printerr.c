#include "libmx.h"

void mx_printerr(char *s) {
    write(2, s, mx_strlen(s));
}
