#include "iterator.hpp"
#include "oops/oop.hpp"

inline void OopGraph2OopClosure::walkGraph(off_t off) { cl->do_oop(p->fieldAddr<oop>(off)); }