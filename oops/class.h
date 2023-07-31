#ifndef OOPS_CLASS_
#define OOPS_CLASS_

#include "util/hashtable.h"

typedef struct Class Class;
struct Class {
    Class* super;
    HashTable* subclasses;
};

#endif
