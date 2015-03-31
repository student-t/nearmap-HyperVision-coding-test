#ifndef IMAGE_READER_H
#define IMAGE_READER_H

#include "ThreadCoord.h"
#include "RGBHistogram.h"

template<typename T> class ImageReader
{
public:
    ImageReader(const std::string &file) : _file(file), _threads(1) {}

    /*
     * This function calculates a RGB histogram for an image. Any existing data in the histograms will be erased.
     */
    void calculate(RGBHistogram<T> &hist);

    inline ThreadNum getThreads() const { return _threads; }
    inline void setThreads(ThreadNum threads) { _threads = threads; }

private:
    // The number of threads used for processing the image
    ThreadNum _threads;

    // The path of the image
    const std::string _file;
};

#endif
