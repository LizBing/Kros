#ifndef UTILS_ALIGN_
#define UTILS_ALIGN_

#define align_down(n, a) ((n) & ~(a - 1))
#define align_up(n, a) (align_down((n) + a - 1, a))

#endif