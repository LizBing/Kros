#ifndef UTIL_AVERAGE_
#define UTIL_AVERAGE_

#include "globals.h"

class Average {
public:
    Average()
    : _last(0) {}

    float last() { return _last; }

    float sample(float f) { return _last = compute(f); }

protected:
    virtual float compute(float f) { return (f + last()) / 2; }
 
    float _last;
};

class WeightedMovingAverage : public Average {
public:
    WeightedMovingAverage()
    : epoch(0) {}

protected:
    long epoch;

    float compute(float f) override {
        epoch += 1;
        return (f * epoch + last() * (epoch - 1)) / epoch;
    }
};

class ExpMovingAverage : public WeightedMovingAverage {
public:
    ExpMovingAverage(long w, long _threshold = 100)
    : threshold(_threshold), weight(w) {}

private:
    long threshold, weight;

    float compute(float f) override {
        epoch += 1;

        long w = epoch >= threshold ? weight : max2(weight, threshold / epoch);
        return last() * (100 - w) / 100 + f * w / 100;
    }
};

#endif