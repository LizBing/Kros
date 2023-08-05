#ifndef UTIL_PAIR_
#define UTIL_PAIR_

template<class T, class U>
struct Pair {
    T first;
    U second;
};

template<class T, class U>
inline Pair<T, U> make_pair(T t, U u) { return (Pair<T, U>){ t, u }; }


#endif
