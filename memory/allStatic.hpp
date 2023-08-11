#ifndef UTILS_ALLSTATIC_
#define UTILS_ALLSTATIC_

// HotSpot-style namespace. 
// Derived classes of 'AllStatic' can't be constructed.
struct AllStatic {
    AllStatic() = delete;
    ~AllStatic() = delete;
};

#endif