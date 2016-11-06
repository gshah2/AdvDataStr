#ifndef __ERROR_H__
#define __ERROR_H__

typedef int error_t;

const char *printerr(int errnumber);

enum error_type
{
  E_NONE,
  E_RESOURCES,
  E_ARGUMENTS,
  E_FSEEK,
  E_FREAD,
};

/*
 * Support for debug statements will be added in the next project under HW2
 */

#endif
