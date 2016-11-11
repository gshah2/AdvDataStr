#ifndef __FILE_OPS_H__
#define __FILE_OPS_H__

#include "../../infra/error.h"

error_t get_size_of_file(FILE **fp, int *size);

error_t read_data_from_file(FILE **fp, int **pointer, int size);

#endif
