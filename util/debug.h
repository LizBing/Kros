#ifndef UTIL_DEBUG_
#define UTIL_DEBUG_

#include <stdio.h>
#include <stdlib.h>

#define panic(...) \
    fprintf(stderr, "Kapok fatal error: " __VA_ARGS__); \
    exit(EXIT_FAILURE) \

#define warn_on(...) \
    fprintf(stderr, "Kapok warning: " __VA_ARGS__)

#endif