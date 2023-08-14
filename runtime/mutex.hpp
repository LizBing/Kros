#ifndef RUNTIME_MUTEX_
#define RUNTIME_MUTEX_

class Mutex {
public:
    Mutex();

    bool lock(long time = 0, bool checkSafePoint = false);
    void unlock();
    bool tryLock(bool checkSafePoint = false);

private:
    void* nativeHandle;
};


#endif 