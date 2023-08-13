#ifndef RUNTIME_VMFLAGTABLE_
#define RUNTIME_VMFLAGTABLE_

#include "memory/allStatic.hpp"
#include "vmFlag.hpp"
#include "allFlags.h"

#define VMFLAG_ENUM(name) VMFLAG_##name##_ENUM
#define VMFLAG_ENUM_(name) VMFLAG_ENUM(name),

#define DEFINE_VMFLAG_ENUM(type, name, ...) VMFLAG_ENUM_(name)

enum VMFlagEnum {
    INVAILD_VMFLAG = -1,
    ALLFLAGS(DEFINE_VMFLAG_ENUM)
    VMFLAG_NUM
};

class VMFlagTable : AllStatic {
private:
    static const int BUCKETS_NUM = 277;

    short buckets[BUCKETS_NUM];
    short table[VMFLAG_NUM];
    ushort hashes[VMFLAG_NUM];

public:
    static VMFlag flags[];

private:
    static constexpr size_t strlen(const char* s) {
        size_t ret_val = 0;
        for(; *s; ++s)
            ++ret_val;
        return ret_val;
    }

    static constexpr uint32_t hashCode(const char* s) {
        auto len = strlen(s);
        uint32_t ret_val = 0;

        while(len--) {
            ret_val = ret_val * 31 + *s;
            ++s;
        }

        return ret_val;
    }

public:
    constexpr VMFlagTable();    // compile-time hash table

    VMFlag* find(const char*) const;
};


#endif