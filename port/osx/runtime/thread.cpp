#include "runtime/thread.hpp"
#include <pthread.h>

template<class T>
T* Thread::current() {
    auto thrd = pthread_self();
    auto stack = (char*)pthread_get_stackaddr_np(thrd);
    auto tls = (Thread**)(stack - sizeof(Thread*));

    return static_cast<T*>(*tls);
}

void Thread::yield() { pthread_yield_np(); }