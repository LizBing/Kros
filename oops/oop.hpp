#ifndef OOPS_OOP_
#define OOPS_OOP_

#include "oops/markWord.hpp"

class Class;

typedef class OopDesc* oop;
class OopDesc {
private:
    MarkWord markWord;

public:
    Class* klass;

    ;

private:
};

#endif