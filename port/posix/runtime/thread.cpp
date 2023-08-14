#include "runtime/thread.hpp"
#include "runtime/debug.h"
#include "runtime/globals.h"

#include <pthread.h>
#include <unistd.h>

static void* Runnable2PlatformRunnable(void* _r) {
    auto r = (Runnable*)_r;
    r->run();
    return NULL;
}

Thread::Thread(Runnable* r) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    char* m = new char[nativeStackSize + sizeof(Thread*)];
    assert(m, "can't create a new native stack(out of memory).");

    void* stack = m + sizeof(Thread*);
    auto tls = (Thread**)m;

    pthread_attr_setstack(&attr, stack, nativeStackSize);
    *tls = this;

    nativeHandle = new pthread_t;
    auto res = pthread_create((pthread_t*)nativeHandle, &attr, Runnable2PlatformRunnable, (void*)r);
    assert(!res, "failed to create a new thread.");
}

Thread::~Thread() { operator delete(nativeHandle); }

void Thread::join() { pthread_join(*(pthread_t*)nativeHandle, NULL); }
void Thread::detach() { pthread_detach(*(pthread_t*)nativeHandle); }

void Thread::sleep(long us) { usleep(us); }