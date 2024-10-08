#include "../inc/pathfinder.h"

static int **create_matrix(int n) {
    int **res = malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) res[i] = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) res[i][j] = INT_MAX;
    return res;
}

static int read_islands_amount(int fd, char *filename) {
    int eof = 0;
    int size = 0;
    char *line = mx_ut_cool_read_line(fd, &size, &eof, '\n');
    if (!line && size == 0) return mx_ut_handle_err(EMPTY, filename, 1);
    if (line == NULL) return -1;
    int result = mx_atoi(line);
    int strlen = mx_strlen(line);
    free(line);
    if (result < 1 || strlen != mx_numlen(result)) {
        return mx_ut_handle_err(FIRSTLINE, NULL, 1);
    }
    return result;
}

t_data *mx_ut_init_data(int fd, char *filename) {
    t_data *data = malloc(sizeof(t_data));
    if (!data) return NULL;
    data->error = NONE;
    data->nodes = NULL;
    // get islands amount
    data->amount = read_islands_amount(fd, filename);
    if (data->amount < 0) {
        free(data);
        return NULL;
    }
    // create graph
    data->graph = malloc(sizeof(t_graph));
    if (!data->graph) {
        free(data);
        return NULL;
    }
    data->graph->size = data->amount;
    data->graph->matrix = create_matrix(data->graph->size);
    if (!data->graph->matrix) {
        free(data->graph);
        free(data);
        return NULL;
    }
    return data;
}
