#ifndef RUNTIME_THREADCRITICAL_
#define RUNTIME_THREADCRITICAL_

#include "memory/allocation.hpp"

struct ThreadCritical : StackObj {
    ThreadCritical();
    ~ThreadCritical();
};

#endif