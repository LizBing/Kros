#include "vmFlagTable.hpp"
#include <cstring>

#define CREATE_VMFLAG(type, name, defaultValue, doc) \
    VMFlag(&name, VMFlag::Type::TYPE_##type, #name, doc)

#define DO_HASH(flagEnum, flagName) { \
    auto hash = hashCode(flagName); \
    auto bucketIndex = hash % BUCKETS_NUM; \
    hashes[flagEnum] = (ushort)hash; \
    table[flagEnum] = buckets[bucketIndex]; \
    buckets[bucketIndex] = flagEnum; \
}

#define DO_FLAG(type, name, ...) DO_HASH(VMFLAG_ENUM(name), #name)

VMFlag VMFlagTable::flags[] = {
    ALLFLAGS(CREATE_VMFLAG)
};

constexpr VMFlagTable::VMFlagTable()
: buckets(), table(), hashes() {
    for(auto i = 0; i < BUCKETS_NUM; ++i)
        buckets[i] = INVAILD_VMFLAG;

    ALLFLAGS(DO_FLAG);
}

VMFlag* VMFlagTable::find(const char* name) const {
    auto hash = hashCode(name);
    auto bucketIndex = hash % BUCKETS_NUM;

    for(
        auto flagEnum = buckets[bucketIndex]; 
        flagEnum != INVAILD_VMFLAG; 
        flagEnum = table[flagEnum]
    ) {
        if(hashes[flagEnum] == (ushort)hash) {
            auto flag = flags + flagEnum;
            if(!strcmp(name, flag->name()))
                return flag;
        }
    }

    return NULL;
}