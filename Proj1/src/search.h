#ifndef __IN_MEMORY_H__
#define __IN_MEMORY_H__

#include "../../infra/error.h"

void linear_search_in_mem(int *key_list, int key_size, int *seek_list,
                          int seek_size, int **hit);

void binary_search_in_mem(int *key_list, int key_size, int *seek_list,
                          int seek_size, int **hit);

error_t linear_search_disk(int *seek_list, int seek_size, int key_size,
                           int **hit, FILE **fp);

error_t binary_search_disk(int *seek_list, int seek_size, int key_size,
                           int **hit, FILE **fp);

#endif
