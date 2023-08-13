#include "vmFlagTable.hpp"
#include <cstring>

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