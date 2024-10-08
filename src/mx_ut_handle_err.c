#include "../inc/pathfinder.h"

static void handle_args_error(void) {
    mx_printerr("usage: ./pathfinder [filename]\n");
}

static void handle_filename_error(char *filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" does not exist\n");
}

static void handle_empty_file_error(char *filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" is empty\n");
}

static void handle_firstline_error(void) {
    mx_printerr("error: line 1 is not valid\n");
}

static void handle_line_error(int line) {
    mx_printerr("error: line ");
    mx_printerr(mx_itoa(line));
    mx_printerr(" is not valid\n");
}

static void handle_islands_error(void) {
    mx_printerr("error: invalid number of islands\n");
}

static void handle_bridges_error(void) {
    mx_printerr("error: duplicate bridges\n");
}

static void handle_length_error(void) {
    mx_printerr("error: sum of bridges lengths is too big\n");
}

int mx_ut_handle_err(t_errors error, char *filename, int line) {
    if (error == NONE) return 0;
    else if (error == ARGS) handle_args_error();
    else if (error == NAME) handle_filename_error(filename);
    else if (error == EMPTY) handle_empty_file_error(filename);
    else if (error == FIRSTLINE) handle_firstline_error();
    else if (error == LINE) handle_line_error(line);
    else if (error == ISLANDS) handle_islands_error();
    else if (error == BRIDGES) handle_bridges_error();
    else if (error == LENGTH) handle_length_error();
    return -1;
}
