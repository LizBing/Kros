#ifndef MEMORY_GC_MARKBITMAP_
#define MEMORY_GC_MARKBITMAP_

#include "utils/bitMap.hpp"

class MarkBitMap {
public:
    MarkBitMap();

    ;

private:
    BitMap bitMap;
};


#endif