#ifndef OOPS_SYMBOL_
#define OOPS_SYMBOL_

#include "util/bool.h"

typedef struct {
    int refcount;

    int hashcode;
    const char* str;
} Symbol;

void Symbol_ctor(Symbol*, const char*);
void Symbol_dtor(Symbol*);

void Symbol_link(Symbol*);
void Symbol_unlink(Symbol*);    

bool Symbol_equals(Symbol*, Symbol*);

#endif
