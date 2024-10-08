#include "../inc/pathfinder.h"

bool mx_checkerr(t_data *data) {
    if (!data) return true;  // error was processed in read func
    if (data->error == ISLANDS
    || mx_list_size(data->nodes) != data->amount) {
        mx_ut_handle_err(ISLANDS, NULL, 0);
        return true;
    }
    if (data->error == BRIDGES) {
        mx_ut_handle_err(BRIDGES, NULL, 0);
        return true;
    }
    if (data->error == LENGTH) {
        mx_ut_handle_err(LENGTH, NULL, 0);
        return true;
    }
    return false;
}
