#ifndef RGBHISTOGRAM_H
#define RGBHISTOGRAM_H

#include "Histogram.h"

template<typename T> struct RGBHistogram
{
    RGBHistogram<T>(Histogram<T> &redHist, Histogram<T> &greenHist, Histogram<T> &blueHist)
        : redHist(redHist), greenHist(greenHist), blueHist(blueHist) {}

    Histogram<T> &redHist, &greenHist, &blueHist;
};

#endif
