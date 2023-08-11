#ifndef UTILS_MACROS_
#define UTILS_MACROS_

#ifdef _LP64
#define LP64_ONLY(x) x
#define NOT_LP64(x)
#else
#define LP64_ONLY(x)
#define NOT_LP64(x) x
#endif


#endif