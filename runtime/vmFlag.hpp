#ifndef RUNTIME_VMFLAG_
#define RUNTIME_VMFLAG_

#include "utils/int.h"
#include "utils/pair.hpp"

#define FLAGTYPES_DO(f) \
    f(bool) \
    f(int) \
    f(uint) \
    f(intx) \
    f(uintx) \
    f(vmlong) \
    f(vmulong) \
    f(size_t) \
    f(double) \

#define DECLARE_FLAGTYPE(t) TYPE_##t,

class VMFlag {
public:
    enum class Type { FLAGTYPES_DO(DECLARE_FLAGTYPE) };
    
    void* const addr;
    const Type type;
    const char* const name;
    const char* const brief;
};

#ifdef PRODUCT

#define DECLARE_VMFLAG(_type, _name, defaultValue, _brief, ...) \
const _type _name = defaultValue; \
VMFlag vf_##_name = { \
    .addr = (void*)&_name, \
    .type = VMFlag::Type:: DECLARE_FLAGTYPE(_type) \
    .name = #_name, \
    .brief = #_brief \
}

#else

#define DECLARE_VMFLAG(type, name, ...) \
extern "C" type name; \
extern "C" VMFlag vf_##name

#endif

#endif