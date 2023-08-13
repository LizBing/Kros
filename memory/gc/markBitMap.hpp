#ifndef MEMORY_GC_MARKBITMAP_
#define MEMORY_GC_MARKBITMAP_

#include "memory/iterator.hpp"
#include "utils/bitMap.hpp"
#include "memory/memRegion.hpp"

class MarkBitMapClosure : OopClosure {
public:
    MarkBitMapClosure(MemRegion mr)
    : _memRegion(mr) {}

    MemRegion memRegion() { return _memRegion; }

private:
    MemRegion _memRegion;
};

class MarkBitMap {
public:
    MarkBitMap(MemRegion);
    MarkBitMap(MarkBitMap*, MemRegion);

    void set(oop);
    void reset(oop);
    void set_par(oop);
    void reset_par(oop);

    void clear(MemRegion);
    void clear() { clear(memRegion()); }

    MemRegion memRegion() { return _memRegion; }

    void oop_iterate(MarkBitMapClosure*);

private:
    BitMap bitMap;
    MemRegion _memRegion;
};


#endif