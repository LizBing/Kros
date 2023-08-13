#ifndef RUNTIME_VMFLAG_
#define RUNTIME_VMFLAG_

#include "utils/globals.h"
#include "utils/pair.hpp"

#define NONSTRING_VMFLAGTYPES_DO(f) \
    f(bool) \
    f(int) \
    f(uint) \
    f(intx) \
    f(uintx) \
    f(vmlong) \
    f(vmulong) \
    f(size_t) \
    f(double) \

#define DECLARE_VMFLAGTYPE(t) TYPE_##t,
#define VMFLAGTYPE_ACCESSOR(t) \
    bool is_##t() const { return _type == Type::TYPE_##t; } \
    t get_##t() const { return *(t*)_addr; } 

class VMFlagTable;

class VMFlag {
public:
    enum class Type { 
        NONSTRING_VMFLAGTYPES_DO(DECLARE_VMFLAGTYPE) 
        TYPE_str,
    };

public:
    constexpr VMFlag(void* addr, Type type, const char* name, const char* doc)
    : _addr(addr), _type(type), _name(name), _doc(doc) {}

    const char* name() const { return _name; }

    template<class T>
    T get() const { return *(T*)_addr; }

    template<class T>
    void set(T v) const { *(T*)_addr = v; }

    NONSTRING_VMFLAGTYPES_DO(VMFLAGTYPE_ACCESSOR);

    bool is_str() const { return _type == Type::TYPE_str; }
    str get_str() const { return get<str>(); }
    void set_str(str v) const { set<str>(v); }

private:
    void* _addr;
    Type _type;
    const char* _name;
    const char* _doc;
};

#define RANGE(...)  // no range checking

#ifdef PRODUCT

#define DECLARE_VMFLAG(type, name, ...) \
type name 

#else

#define DECLARE_VMFLAG(type, name, ...) \
extern "C" type name 

#endif



#endif