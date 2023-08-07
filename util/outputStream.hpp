#ifndef OUTPUTSTREAM_
#define OUTPUTSTREAM_

#include "debug.h"
#include <cstdio>
#include <cstdarg>

class OutputStream {
public:
    OutputStream(const char* path) {
        fp = fopen(path, "w");
        assert(!ferror(fp), "faild to open the file '%s'.", path);
    }

    ~OutputStream() {
        fclose(fp);
    }

    void flush() { fflush(fp); }

    void appand(const char* str, ...) {
        va_list ap;
        va_start(ap, str);

        vfprintf(fp, str, ap);
    }

private:
    FILE* fp;
};

#endif