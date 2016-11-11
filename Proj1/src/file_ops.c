#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "file_ops.h"

error_t
get_size_of_file (FILE **fp, int *size)
{
  error_t result = E_NONE;
  long int start_of_file, end_of_file;

  start_of_file = end_of_file = 0;

  // Know the end of the file
  if(!fseek(*fp, 0, SEEK_END)) {
    end_of_file = ftell(*fp);
  } else {
    printf("ERROR: In %s: \n\t%s. %s\n", __FUNCTION__, printerr(E_FSEEK),
           strerror(errno));
    return (errno);
  }

  // Know the start of the file
  if(!fseek(*fp, 0, SEEK_SET)) {
    start_of_file = ftell(*fp);
  } else {
    printf("ERROR: In %s: \n\t%s. %s\n", __FUNCTION__, printerr(E_FSEEK),
           strerror(errno));
    return (errno);
  }

  // Calculate number of integers in the file
  *size = (end_of_file - start_of_file) / sizeof(int);

  return (result);
}

error_t
read_data_from_file (FILE **fp, int **pointer, int size)
{
  error_t result = E_NONE;

  // Allocate memory for these integers in our program
  if ((*pointer = (int *)malloc(sizeof(int) * size)) == NULL) {
    printf("ERROR: In %s: \n\t%s. %s\n", __FUNCTION__, printerr(E_RESOURCES),
           strerror(errno));
      return (errno);
  }

  // Read the entire file into the buffer pointed to by the pointer.
  if (fread(*pointer, sizeof(int), size, *fp) != size) {
    printf("ERROR: In %s: \n\t%s. %s\n", __FUNCTION__, printerr(E_FREAD),
           strerror(errno));
    return (errno);
  }

  return (result);
}
