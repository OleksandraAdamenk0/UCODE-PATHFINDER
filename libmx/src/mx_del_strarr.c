#include "libmx.h"

/**
 * @NAME Delete array of strings
 * @DESCRIPTION Create a function that:\n
 *  takes a pointer to a NULL-terminated array of strings \n
 *  deletes the contents of the array \n
 *  frees array memory with free \n
 *  sets a pointer to NULL
 * @note \n
 */

void mx_del_strarr(char ***arr) {
    if (!arr|| !(*arr)) return;
    for (int i = 0; (*arr)[i] != NULL; ++i) mx_strdel(&(*arr)[i]);
    free(*arr);
    *arr = NULL;
}
