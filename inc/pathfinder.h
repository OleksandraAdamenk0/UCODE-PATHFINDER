#ifndef OADAMENKO_181_PATHFINDER_H
#define OADAMENKO_181_PATHFINDER_H

#include "../libmx/inc/libmx.h"
#include <limits.h>

#define INIT INT_MAX

typedef enum e_errors {
    ARGS, NAME, EMPTY, FIRSTLINE, LINE, ISLANDS, BRIDGES, LENGTH, NONE
} t_errors;

typedef struct s_node {
    int id;
    char *name;
} t_node;

typedef struct s_path {
    int *vertices;
    int length;
} t_path;

typedef struct s_path_list {
    t_path *paths;
    int count;
    int min_len;
} t_path_list;

typedef struct s_path_info {
    int *visited;
    int *path;
    int path_index;
    int weight;
} t_path_info;

typedef struct s_graph {
    int size;
    int **matrix;
} t_graph;

typedef struct s_data {
    int amount;
    t_list *nodes;
    t_graph *graph;
    t_errors error;
} t_data;

// ut - utils
// =============================================================

int mx_ut_handle_err(t_errors error, char *filename, int line);

char *mx_ut_cool_read_line(int fd, int *size, int *eof, char delim);

void mx_ut_free_data(t_data *data);

t_data *mx_ut_init_data(int fd, char *filename);

// =============================================================

t_data *mx_parse_file(char *filename);

bool mx_checkerr(t_data *data);

void mx_pathfinder(t_data *data);

void mx_print(t_path_list *all_paths, t_data *data);

#endif //OADAMENKO_181_PATHFINDER_H
