#include "../inc/pathfinder.h"

static char *name_by_id(t_list *islands, int id) {
    for (t_list *copy = islands; copy; copy = copy->next)
        if (id == ((t_node *)copy->data)->id)
            return ((t_node *)copy->data)->name;
    return NULL;
}

static void print_path(t_path_list *all_paths, t_data *data, int path_ind) {
    mx_printstr("Path: ");
    mx_printstr(name_by_id(data->nodes, all_paths->paths[path_ind].vertices[0]));
    mx_printstr(" -> ");
    mx_printstr(name_by_id(data->nodes,all_paths->paths[path_ind].vertices
    [all_paths->paths[path_ind].length - 1]));
}

static void print_route(t_path_list *all_paths, t_data *data, int path_ind) {
    mx_printstr("\nRoute: ");
    for (int j = 0; j < all_paths->paths[path_ind].length - 1; j++) {
        char *from = name_by_id(data->nodes,
                              all_paths->paths[path_ind].vertices[j]);
        mx_printstr(from);
        mx_printstr(" -> ");
    }
    char *to = name_by_id(data->nodes, all_paths->paths[path_ind].vertices
    [all_paths->paths[path_ind].length - 1]);
    mx_printstr(to);
}

static void print_distance(t_path_list *all_paths, t_data *data, int path_ind) {
    mx_printstr("\nDistance: ");
    if (all_paths->paths[path_ind].length == 2)
        mx_printint(all_paths->min_len);
    else {
        for (int j = 0; j < all_paths->paths[path_ind].length - 1; j++) {
            int x = all_paths->paths[path_ind].vertices[j];
            int y = all_paths->paths[path_ind].vertices[j + 1];
            mx_printint(data->graph->matrix[x][y]);
            if (j < all_paths->paths[path_ind].length - 2) mx_printstr(" + ");
        }
        mx_printstr(" = ");
        mx_printint(all_paths->min_len);
    }
    mx_printstr("\n");
}

void mx_print(t_path_list *all_paths, t_data *data) {
    for (int i = 0; i < all_paths->count; i++) {
        mx_printstr("========================================\n");
        print_path(all_paths, data, i);
        print_route(all_paths, data, i);
        print_distance(all_paths, data, i);
        mx_printstr("========================================\n");
    }
}
