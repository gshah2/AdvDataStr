#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define NUMBER_OF_ARGUMENTS 3
int
main (int argc, char **argv)
{
  if (argc != NUMBER_OF_ARGUMENTS) {
    printf("ERROR: In %s: \n\t%s.\n", __FUNCTION__, printerr(E_ARGUMENTS));
    return (0);
  }
