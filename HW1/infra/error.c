#include "error.h"

const char *
printerr(int errnumber) {

  switch(errnumber) {
      case E_RESOURCES:
          return ("Out of Resources");
          break;
      case E_ARGUMENTS:
          return ("Check the numnber of arguments passed");
          break;
      case E_FSEEK:
          return ("Bad fseek");
          break;
      case E_FREAD:
          return ("Bad fread");
      default:
          return ("Error string not defined");
          break;
  }
}
