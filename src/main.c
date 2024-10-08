#include "../inc/pathfinder.h"

int main(int argc, char *argv[]) {
    if (argc != 2) return mx_ut_handle_err(ARGS, NULL, 0);
    t_data *data = mx_parse_file(argv[1]);
    if (mx_checkerr(data) == true) {
        mx_ut_free_data(data);
        return -1;
    }
    mx_pathfinder(data);
    mx_ut_free_data(data);
    return 0;
}
