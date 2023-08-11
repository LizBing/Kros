#ifndef RUNTIME_OS_
#define RUNTIME_OS_

#include "memory/allStatic.hpp"
#include "utils/int.h"

struct os : AllStatic {
    static long getpid();

    static size_t pageSize();

    struct io {
        enum {
            READ = 1,
            WRITE = 2,
            APPEND = 4,
            TRUNC = 8
        };
/* the same as <stdio.h>
        enum {
            SEEK_SET,
            SEEK_CUR,
            SEEK_END,
        };
*/
        enum {
            SET,
            CUR,
            END,
        };
    };

    static int open(const char*, int mode);
    static int truncate(int, size_t);
    static size_t read(void*, size_t, int);
    static size_t write(int, void*, size_t);
    static off_t seek(int, off_t, int whence);
    static void close(int);

    static int open_shm(const char*, int mode);
    static void close_shm(const char*);

    static void* mmap(void*, size_t, bool executable, int fd, off_t);
    static void munmap(void*, size_t);

    static void* malloc(size_t);
    static void free(void*);
    static void* realloc(void*, size_t);

    static void* memcpy(void*, void*, size_t);
};



#endif