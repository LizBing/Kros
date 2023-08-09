#ifndef OOPS_OOP_
#define OOPS_OOP_

#include "memory/iterator.hpp"
#include "oops/markWord.hpp"

typedef class TypeDesc* Type;
typedef class OopDesc* oop;

class OopDesc {
private:
    volatile MarkWord _markWord;
    Type type;
    char _base[0];

public:
    template<class T>
    T fieldAddr(off_t off) { return *(T*)(actualBase() + off); }

    void oop_iterate(OopClosure*);
    char* actualBase(); 

    MarkWord markWord() { return _markWord.v; }
    ;
};

#endif