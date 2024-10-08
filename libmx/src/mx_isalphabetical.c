#include "libmx.h"

bool mx_isalphabetical(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
