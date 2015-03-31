#ifndef HISTOGRAMWRITER_H
#define HISTOGRAMWRITER_H

#include "RGBHistogram.h"

/*
 * This class is responsible for writing histogram to an output. The output could be
 * a file or a class.
 */

template<typename T, typename Output> class HistogramWriter
{
public:
    static void write(const RGBHistogram<T> &hist, Output &output)
    {
       output << hist.redHist << std::endl;
       output << hist.greenHist << std::endl;
       output << hist.blueHist << std::endl;
    }
};

#endif
