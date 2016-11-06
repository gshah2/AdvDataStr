#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "search.h"

void
linear_search_in_mem (int *key_list, int key_size, int* seek_list,
               int seek_size, int **hit)
{
  int iter_seek = 0;
  int iter_key = 0;

  for (; iter_seek < seek_size; iter_seek++) {
    for (iter_key = 0; iter_key < key_size; iter_key++) {
      if (key_list[iter_key] == seek_list[iter_seek]) {
        (*hit)[iter_seek] = 1;
        break;
      }
    }
  }
}

void
binary_search_in_mem (int *key_list, int key_size, int* seek_list,
                     int seek_size, int **hit)
{
  int iter_seek;

  for (iter_seek = 0; iter_seek < seek_size; iter_seek++) {
    int left = 0;
    int right = key_size - 1;
    int middle = 0;

    while (left <= right) {
      middle = (right + left) / 2;
      if (seek_list[iter_seek] == key_list[middle]) {
        (*hit)[iter_seek] = 1;
        break;
      } else if (seek_list[iter_seek] > key_list[middle]) {
        left = middle + 1;
      } else {
        right = middle - 1;
      }
    }
  }
}

error_t
linear_search_disk (int *seek_list, int seek_size, int key_size,
                    int **hit, FILE **fp)
{
  int iter_seek = 0;
  int iter_key = 0;
  int key_elem = 0;
  error_t result = E_NONE;

  for (; iter_seek < seek_size; iter_seek++) {
    for (; iter_key < key_size; iter_key++) {
      if (!fread(&key_elem, sizeof(int), 1, *fp)) {
        printf("ERROR: In %s: \n\t%s. %s\n", __FUNCTION__, printerr(E_FREAD),
               strerror(errno));
        return (errno);
      }
      if (key_elem == seek_list[iter_seek]) {
        (*hit)[iter_seek] = 1;
        break;
      }
    }
    iter_key = 0;
    if(fseek(*fp, 0, SEEK_SET)) {
      printf("ERROR: In %s: \n\t%s. %s\n", __FUNCTION__, printerr(E_FSEEK),
             strerror(errno));
        return (errno);
    }
  }

  return (result);
}

error_t
binary_search_disk (int *seek_list, int seek_size, int key_size,
                    int **hit, FILE **fp)
{
  error_t result = E_NONE;
  int iter_seek;
  int key_elem = 0;

  for (iter_seek = 0; iter_seek < seek_size; iter_seek++) {
    int left = 0;
    int right = key_size - 1;
    int middle = 0;

    while (left <= right) {
      middle = (right + left) / 2;

      if(fseek(*fp, sizeof(int) * middle, SEEK_SET)) {
        printf("ERROR: In %s: \n\t%s. %s\n", __FUNCTION__, printerr(E_FSEEK),
               strerror(errno));
        return (errno);
      }
      if (!fread(&key_elem, sizeof(int), 1, *fp)) {
        printf("ERROR: In %s: \n\t%s. %s\n", __FUNCTION__, printerr(E_FREAD),
               strerror(errno));
        return (errno);
      }

      if (seek_list[iter_seek] == key_elem) {
        (*hit)[iter_seek] = 1;
        break;
      } else if (seek_list[iter_seek] > key_elem) {
        left = middle + 1;
      } else {
        right = middle - 1;
      }
    }
  }

  return (result);
}
