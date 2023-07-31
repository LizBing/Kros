#ifndef UTIL_HASHMAP_
#define UTIL_HASHMAP_

#include "util/any.h"
#include "util/bool.h"
#include "util/closure.h"

typedef struct HashMap HashMap;
typedef const char* HashMapKey;

void HashMap_put(HashMap*, HashMapKey, Any);
Any HashMap_get(HashMap*, HashMapKey);
bool HashMap_exist(HashMap*, HashMapKey);

bool HashMap_empty(HashMap*);

void HashMap_erase(HashMap*, HashMapKey);
void HashMap_clear(HashMap*);

bool HashMap_iterate(HashMap*, Closure*);

#endif
