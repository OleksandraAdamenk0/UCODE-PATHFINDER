#include "../inc/pathfinder.h"

static void free_island_list(t_list **islands) {
    if (!islands || !*islands) return;
    t_list *copy = *islands;
    while (copy) {
        t_list *next = copy->next;
        if (((t_node *) copy->data)->name) {
            free(((t_node *) copy->data)->name);
        }
        free(copy->data);
        free(copy);
        copy = next;
    }
    *islands = NULL;
}

static void free_matrix(int **matrix, int n) {
    for (int i = 0; i < n; ++i) free(matrix[i]);
    free(matrix);
}

void mx_ut_free_data(t_data *data) {
    if (!data) return;
    free_island_list(&data->nodes);
    if (data->graph) {
        free_matrix(data->graph->matrix, data->graph->size);
        free(data->graph);
    }
    free(data);
}
