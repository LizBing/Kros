#ifndef OOPS_OOP_
#define OOPS_OOP_

#include "class.h"
#include "markWord.h"

typedef struct {
    MarkWord markWord;
    Class* class;
} OopDesc, *oop;

;

#endif
