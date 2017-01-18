//
// Created by doublemine on 17/1/18.
//


#include "check_env.h"

#ifdef __cplusplus
extern "C" {
#endif
long get_current_time() {
    return time(NULL);
}

/**
 *  return false when out of date
 */
bool check_status(long unix_time) {
    return unix_time >= get_current_time();
}


long get_end_time_point() {
    /*2017/3/31 22:30:00*/
    return 1490970600;
}


void check_env_status() {
    if (!check_status(get_end_time_point())) {
        exit(0);
    }
}
#ifdef __cplusplus
}
#endif







