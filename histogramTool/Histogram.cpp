#include <QMutex>
#include "Histogram.h"
#include "BinNotFoundException.h"
#include "InvalidHistogramException.h"

using namespace std;

/*
 * Construct a histogram with no initial data, with nbins bins. The bins are of equal size from min to max.
 */
template<typename T> Histogram<T>::Histogram(size_t nbins, T min, T max)
{
    if (min > max)
    {
        throw exception("Minimum value is larger than the maximum value");
    }

    const int interval = max - min + 1;

    /*
     * It's an error if the size of the bins are not of equal size. Thus, nbins must be
     * perfectly divided by the interval.
     */

    if (interval % nbins)
    {
        throw InvalidHistogramException("The bins must be of equal size");
    }

    const int delta = (interval / nbins);

    for (T t = min; t <= max; t += delta)
    {
        _data[t] = 0;
    }
}

/*
 * Add frequency n for the given bin.
 */
template<typename T> void Histogram<T>::count(T bin, int n)
{
    static QMutex mutex;

    mutex.lock();

    _data[bin] += n;

    mutex.unlock();
}

template<typename T> void Histogram<T>::getBins(vector<T> &bins) const
{
    bins.clear();

    for (map<T, Frequency>::const_iterator iter = _data.begin(); iter != _data.end(); iter++)
    {
        bins.push_back(iter->first);
    }
}

template<typename T> Frequency Histogram<T>::getFreq(T bin) const
{
    const map<T, Frequency>::const_iterator iter = _data.find(bin);

    if (iter != _data.end())
    {
        return iter->second;
    }

    throw BinNotFoundException<T>(bin);
}

/*
 * Remove all frequency data values from the histogram. Each bin count is set to 0.
 */
template<typename T> void Histogram<T>::reset()
{
    for (map<T, Frequency>::iterator iter = _data.begin(); iter != _data.end(); iter++)
    {
        iter->second = 0;
    }
}

template class Histogram<int>;
