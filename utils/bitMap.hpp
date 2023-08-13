#ifndef UTILS_BITMAP_
#define UTILS_BITMAP_

#include "memory/allocation.hpp"
#include "memory/iterator.hpp"
#include "utils/globals.h"
#include "utils/int.h"
#include "utils/align.h"
#include "runtime/debug.h"

struct BitMapWordClosure : Closure {
    // return false if you want to stop the iteration
    virtual bool getIndexInBits(int) = 0;
};

// per 64 bits
class BitMapWord {
private:
    union {
        uint64_t word;
        char bytes[bytesPerVMLong];
    };

public:
    BitMapWord()
    : word(0) {}

    bool empty() { return !word; }
    static size_t capacity() { return bitsPerVMLong; }

    bool test(int indexInBits);
    void set(int indexInBits);
    void set(int start, size_t bits);
    void reset(int indexInBits);
    void reset(int start, size_t bits);
    
    bool test_par(int indexInBits);
    void set_par(int indexInBits);
    void reset_par(int indexInBits);

    void iterate(BitMapWordClosure*);
};

struct BitMapClosure : Closure {
    // return false if you want to stop the iteration
    virtual bool getIndexInBits(long) = 0;
};

class BitMap : CHeapObj {
    static size_t computeSizeInWords(size_t sizeInBits);

public:
    BitMap(size_t sizeInBits) {
        _capacity = align_up(sizeInBits, BitMapWord::capacity());
        words = new BitMapWord[capacity()];
        assert(words, "out of memory");
    }

    BitMap(BitMap*, long indexInBits, size_t sizeInBits);

    ~BitMap() { delete words; }

    // size in bits
    size_t capacity() { return _capacity; }

    void clear() { reset(0, capacity()); }

    bool test(long indexInBits); 
    void set(long indexInBits);
    void set(long start, size_t bits);
    void reset(long indexInBits);
    void reset(long start, size_t bits);

    bool test_par(long indexInBits);
    void set_par(long indexInBits);
    void reset_par(long indexInBits);

private:
    BitMapWord* words;
    size_t _capacity;
};


#endif