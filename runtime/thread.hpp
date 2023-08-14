#ifndef RUNTIME_THREAD_
#define RUNTIME_THREAD_

#include "memory/allStatic.hpp"
#include "memory/allocation.hpp"

struct Runnable {
    virtual void run() = 0;
};

class Thread : protected CHeapObj {
public:
    template<class T = Thread>
    static T* current();

    static void yield();
    static void sleep(long);

public:
    Thread(Runnable*);
    virtual ~Thread();

    void join();
    void detach();

private:
    void* nativeHandle;
};

#endif