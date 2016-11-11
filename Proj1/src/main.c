#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>
#include "../../infra/error.h"
#include "search.h"
#include "file_ops.h"

#define NUMBER_OF_ARGUMENTS 4
#define IN_MEM "--mem"
#define IN_MEM_LIN_SEARCH "--mem-lin"
#define IN_MEM_BIN_SEARCH "--mem-bin"
#define DISK_LIN_SEARCH "--disk-lin"
#define DISK_BIN_SEARCH "--disk-bin"
#define OUTPUT_FILE "./Proj1/output.txt"
#define SEC_TO_USEC 1000000L

int
main(int argc, char **argv)
{

  int *key_list = NULL; // Array to store the integers from key.db (argv[2])
  int *seek_list = NULL; // Array to store the integers from key.db (argv[3])
  int key_size = 0; // Size of the array, key_list
  int seek_size = 0; // Size of the array, seek_list
  int *hit = NULL; // Array to store hit values. Size is same as seek_size
  int iter = 0;
  long double time_elapsed = 0; // Calculate the time elapsed.
  error_t result = E_NONE;
  struct timeval start_time; // Start time for the operation.
  struct timeval end_time; // End time for the operation.
  struct timeval time_elapsed_str; // Display time elapsed in proper format.
  FILE *inp; // Input File Stream
  FILE *op; // Output File Stream

  // Check if the correct number of arguments are passed to the main function.
  if (argc != 4) {
    printf("ERROR: In %s: \n\t%s.\n", __FUNCTION__, printerr(E_ARGUMENTS));
    return (0);
  }

  // Start with the time calculations.
  gettimeofday(&start_time, NULL);

  /*
   * Open and read seek.db (or other relevant file) into an
   * appropriately-sized integer array, seek_list.
   */
  if (!(inp = fopen(argv[3], "rb"))) {
    printf("ERROR: In %s: \n\t%s: %s.\n", __FUNCTION__,
           argv[3], strerror(errno));
    return (0);
  }
  result = get_size_of_file(&inp, &seek_size);
  if (result != E_NONE) {
    printf("ERROR: In %s: \n\t%s: %s\n", __FUNCTION__, argv[3],
           strerror(result));
    return(0);
  }
  result = read_data_from_file(&inp, &seek_list, seek_size);
  if (result != E_NONE) {
    printf("ERROR: In %s: \n\t%s: %s\n", __FUNCTION__, argv[3],
           strerror(result));
    return(0);
  }
  fclose(inp); // Close seek.db

  // Open key.db (or other relevant file) for reading.
  if (!(inp = fopen(argv[2], "rb"))) {
    printf("ERROR: In %s: \n\t%s: %s.\n", __FUNCTION__,
           argv[2], strerror(errno));
    return (0);
  }
  result = get_size_of_file(&inp, &key_size);
  if (result != E_NONE) {
     printf("ERROR: In %s: \n\t%s: %s\n", __FUNCTION__, argv[2],
           strerror(result));
     return(0);
  }

  // Allocate memory for the hit array. Memset to 0.
  if ((hit = (int *)malloc(sizeof(int) * seek_size)) == NULL) {
      printf("ERROR: In %s: \n\tHit Array Init : %s\n", __FUNCTION__, strerror(errno));
      return (errno);
  }
  memset(hit, 0, sizeof(int) * seek_size);

  // Consider the various cases based on the search modes passed to the main
  if (strstr(argv[1], IN_MEM)) {
    result = read_data_from_file(&inp, &key_list, key_size);
    if (result != E_NONE) {
      printf("ERROR: In %s: \n\t%s: %s\n", __FUNCTION__, argv[2],
             strerror(result));
      return(0);
    }
    // Search mode is --mem-lin
    if (!strncmp(argv[1], IN_MEM_LIN_SEARCH, strlen(IN_MEM_LIN_SEARCH))) {
      linear_search_in_mem(key_list, key_size, seek_list, seek_size, &hit);
    // Search mode is --mem-bin
    } else if (!strncmp(argv[1], IN_MEM_BIN_SEARCH, strlen(IN_MEM_BIN_SEARCH))) {
      binary_search_in_mem(key_list, key_size, seek_list, seek_size, &hit);
    }
    // Search mode is --disk-lin
  } else if (!strncmp(argv[1], DISK_LIN_SEARCH, strlen(DISK_LIN_SEARCH))) {
    result = linear_search_disk(seek_list, seek_size, key_size, &hit, &inp);
    if (result != E_NONE) {
      printf("ERROR: In %s: \n\t%s\n", __FUNCTION__, strerror(result));
      return(0);
    }
    // Search mode is --disk-bin
  } else if (!strncmp(argv[1], DISK_BIN_SEARCH, strlen(DISK_BIN_SEARCH))) {
    result = binary_search_disk(seek_list, seek_size, key_size, &hit, &inp);
    if (result != E_NONE) {
      printf("ERROR: In %s: \n\t%s\n", __FUNCTION__, strerror(result));
      return(0);
    }
  }

  // Close the key.db (or the corresponding file)
  fclose(inp);

  // End the time measurements. Calculate the time elapsed.
  gettimeofday(&end_time, NULL);
  time_elapsed = (end_time.tv_sec - start_time.tv_sec) * SEC_TO_USEC +
    end_time.tv_usec - start_time.tv_usec;
  time_elapsed_str.tv_sec = time_elapsed / (long double)1000000L;
  time_elapsed_str.tv_usec = fmod(time_elapsed, SEC_TO_USEC);

  // Write the output of our computations to the text file.
  if (!(op = fopen(OUTPUT_FILE, "w"))) {
    printf("ERROR: In %s: \n\t%s: %s.\n", __FUNCTION__,
           argv[3], strerror(errno));
    return (0);
  }
  for (; iter < seek_size; iter++) {
    if (hit[iter]) {
      fprintf(op, "%12d: Yes\n", seek_list[iter]);
    } else {
      fprintf(op, "%12d: No\n", seek_list[iter]);
    }
  }
  fprintf(op, "Time: %ld.%06d\n", time_elapsed_str.tv_sec, time_elapsed_str.tv_usec);
  fclose(op);

  return 0;
}
