#ifndef UTIL_DEBUG_
#define UTIL_DEBUG_

#include <stdio.h>
#include "exit.h"

#define assert(expr, ...) \
do if(!(expr)) { \
    fprintf(stderr, "Kros fatal error: " __VA_ARGS__); \
    vm_exit(); \
} while(0)

#define warn_on(...) \
    fprintf(stderr, "Kros warning: " __VA_ARGS__)

#endif