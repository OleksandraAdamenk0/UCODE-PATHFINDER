#include "../inc/pathfinder.h"

static void find_all_from_to(int *cords, t_data *data,
                             t_path_info *path_info, t_path_list *all_paths);

t_path_info * create_path_info(int num_vertices) {
    t_path_info * path_info = (t_path_info *)malloc(sizeof(t_path_info));
    path_info->visited = (int*)calloc(num_vertices, sizeof(int));
    path_info->path = (int*)malloc(num_vertices * sizeof(int));
    path_info->path_index = 0;
    path_info->weight = 0;
    return path_info;
}

t_path_list * create_paths(void) {
    t_path_list * paths = (t_path_list *)malloc(sizeof(t_path_list));
    paths->paths = NULL;
    paths->count = 0;
    paths->min_len = INT_MAX;
    return paths;
}

void free_paths(t_path_list *all_paths) {
    for (int i = 0; i < all_paths->count; i++)
        free(all_paths->paths[i].vertices);
    free(all_paths->paths);
    free(all_paths);
}

void free_path_info(t_path_info * path_info) {
    free(path_info->visited);
    free(path_info->path);
    free(path_info);
}

void add_path(t_path_list * all_paths, int* current_path, int length) {
    all_paths->paths = (t_path *)mx_realloc(all_paths->paths,(all_paths->count + 1) * sizeof(t_path_list));
    all_paths->paths[all_paths->count].vertices = (int*)malloc(length * sizeof(int));
    all_paths->paths[all_paths->count].length = length;
    for (int i = 0; i < length; i++)
        all_paths->paths[all_paths->count].vertices[i] = current_path[i];
    all_paths->count++;
}

static void reached_destination(t_path_info *path_info, t_path_list *all_paths) {
    if (path_info->weight < all_paths->min_len){
        for (int i = 0; i < all_paths->count; i++)
            free(all_paths->paths[i].vertices);
        free(all_paths->paths);
        all_paths->paths = NULL;
        all_paths->count = 0;
    }
    add_path(all_paths, path_info->path, path_info->path_index);
    all_paths->min_len = path_info->weight;
}

static void explore_neighbors(int *cords, t_data *data,
                              t_path_info *path_info, t_path_list *all_paths) {
    int from = cords[0];
    int to = cords[1];
    for (int i = 0; i < data->graph->size; i++) {
        int weight = data->graph->matrix[from][i];
        if ( weight != INIT && !path_info->visited[i]) {
            path_info->weight += weight;
            int new_cords[2] = {i, to};
            find_all_from_to(new_cords, data, path_info, all_paths);
            path_info->weight -= weight;
        }
    }
}

static void find_all_from_to(int *cords, t_data *data,
                             t_path_info *path_info, t_path_list *all_paths) {
    int from = cords[0];
    int to = cords[1];
    path_info->visited[from] = 1;
    path_info->path[path_info->path_index] = from;
    path_info->path_index++;
    if (all_paths->count > 0 && path_info->weight > all_paths->min_len) {
        path_info->visited[from] = 0;
        path_info->path_index--;
        return;
    }
    if (from == to) reached_destination(path_info, all_paths);
    else explore_neighbors(cords, data, path_info, all_paths);
    path_info->path_index--;
    path_info->visited[from] = 0;
}

static void find_all_from(t_list *start, t_data *data) {
    for (t_list *copy = start->next; copy; copy = copy->next) {
        t_path_info * path_info = create_path_info(data->graph->size);
        t_path_list * all_paths = create_paths();
        int cords[2];
        cords[0] = ((t_node *) start->data)->id;
        cords[1] = ((t_node *) copy->data)->id;
        find_all_from_to(cords, data, path_info, all_paths);
        mx_print(all_paths, data);
        free_path_info(path_info);
        free_paths(all_paths);
    }
}

void mx_pathfinder(t_data *data) {
    for (t_list *current = data->nodes; current; current = current->next)
        find_all_from(current, data);
}
