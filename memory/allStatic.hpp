#ifndef UTIL_ALLSTATIC_
#define UTIL_ALLSTATIC_

// HotSpot-style namespace. 
// Derived classes of 'AllStatic' can't be constructed.
struct AllStatic {
    AllStatic() = delete;
    ~AllStatic() = delete;
};

#endif