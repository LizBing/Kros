#ifndef UTIL_HASHMAP_
#define UTIL_HASHMAP_

#include "util/any.h"
#include "util/bool.h"
#include "util/closure.h"
#include "oops/symbol.h"

typedef struct HashTable HashTable;

HashTable* new_HashTable();
void delete_HashTable(HashTable*);

void HashTable_put(HashTable*, const char*, Any);
Any HashTable_get(HashTable*, const char*);
bool HashTable_exist(HashTable*, const char*);

size_t HashTable_size(HashTable*);

void HashTable_erase(HashTable*, const char*);
void HashTable_clear(HashTable*);

// impl note: closure.func.this should be an instance of Pair<const char*, Any>
bool HashTable_iterate(HashTable*, Closure);

#endif
