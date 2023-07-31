#ifndef OOPS_MARKWORD_
#define OOPS_MARKWORD_

#include "util/bits.h"

typedef unsigned long MarkWord;

Bits_1stField(MarkWord_lock, 0, 2);
Bits_field(MarkWord_biasedLock, MarkWord_lock, 0, 1);
Bits_field(MarkWord_age, MarkWord_biasedLock, 0, 4);

#ifdef _LP64

Bits_field(MarkWord_lockptr, MarkWord_lock, 0, 62);

Bits_field(MarkWord_epoch, MarkWord_age, 1, 2);
Bits_field(MarkWord_hashCode, MarkWord_age, 1, 31);
Bits_field(MarkWord_thrdID, MarkWord_epoch, 0, 54);

#else

Bits_field(MarkWord_lockptr, MarkWord_lock, 0, 30);

Bits_field(MarkWord_epoch, MarkWord_age, 0, 2);
Bits_field(MarkWord_hashCode, MarkWord_age, 0, 25);
Bits_field(MarkWord_thrdID, CompressedMarkWord_epoch, 0, 23);

#endif

#endif
