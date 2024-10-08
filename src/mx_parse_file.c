#include "../inc/pathfinder.h"

static t_node *create_node(int index, char *name) {
    t_node *result = malloc(sizeof(t_node));
    result->name = name;
    result->id = index;
    return result;
}

static int id_by_name(t_list **nodes_list, const char *name) {
    if (!*nodes_list)
        mx_push_back(nodes_list, create_node(0, mx_strdup(name)));
    int id = 0;
    for (t_list *copy = *nodes_list; copy; copy = copy->next) {
        if (mx_strcmp(((t_node *)copy->data)->name, name) == 0)
            return ((t_node *)copy->data)->id;
        ++id;
    }
    mx_push_back(nodes_list, create_node(id, mx_strdup(name)));
    return id;
}

static bool is_word_alphabetical(const char *word) {
    if (word == NULL) return false;
    for (int i = 0; word[i] != '\0'; i++)
        if (!mx_isalphabetical(word[i])) return false;
    return true;
}

static char **handle_line(const char *line, int line_num) {
    // parse
    int d1i = mx_get_char_index(line, '-');
    int d2i = mx_get_char_index(line, ',');
    if (d1i < 1 || d2i < d1i || d2i > mx_strlen(line) - 2 || d1i + 1 == d2i) {
        mx_ut_handle_err(LINE, NULL, line_num);
        return NULL;
    }
    char **arr = malloc(4 * sizeof(char *));
    arr[0] = mx_strndup(line, d1i);
    arr[1] = mx_strndup(line + d1i + 1, d2i - d1i - 1);
    arr[2] = mx_strndup(line + d2i + 1, mx_strlen(line) - d2i -1);
    arr[3] = NULL;
    int len = mx_atoi(arr[2]);

    if (mx_strlen(arr[0]) < 1 || mx_strlen(arr[1]) < 1
        || mx_strcmp(arr[0], arr[1]) == 0 || !is_word_alphabetical(arr[0])
        || !is_word_alphabetical(arr[1])
        || (((mx_strlen(arr[2]) != mx_numlen(len) || len < 1))
        && len != -2)) {
        mx_del_strarr(&arr);
        mx_ut_handle_err(LINE, NULL, line_num);
        return NULL;
    }
    return arr;
}

static char **process_line(int fd, int *eof, const int *num) {
    int size = 0;
    char *line = mx_ut_cool_read_line(fd, &size, eof, '\n');
    if (*eof > 0) {
        free(line);
        return NULL;
    }
    char **arr = handle_line(line, *num);
    free(line);
    if (!arr) return NULL;
    return arr;
}

static int process_ids(t_data **data, char **names, int *i, int *j) {
    *i = id_by_name(&(*data)->nodes, names[0]);
    *j = id_by_name(&(*data)->nodes, names[1]);
    if (*i >= (*data)->graph->size || *j >= (*data)->graph->size)
        (*data)->error = ISLANDS;
    return (*i != -1 && *j != -1);
}

static int check_bridge_length(char *len_str, int num, t_data *data) {
    int len = mx_atoi(len_str);
    if (len == -2 && data->error >= LENGTH) {
        data->error = LENGTH;
        return 0;
    }
    else if (len < 1) return mx_ut_handle_err(LINE, NULL, num);
    return len;
}

static void update_graph_matrix(t_data **data, int i, int j, int len) {
    if ((*data)->graph->matrix[i][j] != INT_MAX && (*data)->error >= BRIDGES)
        (*data)->error = BRIDGES;
    (*data)->graph->matrix[i][j] = len;
    (*data)->graph->matrix[j][i] = len;
}

static t_data *exit_error(t_data **data, int fd) {
    if (data) mx_ut_free_data(*data);
    close(fd);
    return NULL;
}

t_data *mx_parse_file(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        mx_ut_handle_err(NAME, filename, 0);
        return NULL;
    }
    t_data *data = mx_ut_init_data(fd, filename);
    if (!data) return exit_error(NULL, fd);
    int eof = 0;
    int num = 2;  // line counter
    long long int sum = 0;
    while(1) {
        char **arr = process_line(fd, &eof, &num);
        if (!arr && eof) break;
        if (!arr) return exit_error(&data, fd);
        int i, j;
        if (!process_ids(&data, arr, &i, &j)) {
            mx_del_strarr(&arr);
            return exit_error(&data, fd);
        }
        int len = check_bridge_length(arr[2], num, data);
        mx_del_strarr(&arr);
        if (len < 0) return exit_error(&data, fd);
        if (data->error != ISLANDS) update_graph_matrix(&data, i, j, len);
        sum += len;
        num++;
    }
    if (sum > INT_MAX && data->error >= LENGTH) data->error = LENGTH;
    close(fd);
    return data;
}
