#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <map>
#include <vector>
#include <iostream>
#include <sstream>

typedef unsigned int Frequency;

/*
 * Reference: http://stackoverflow.com/questions/3516196/testing-whether-an-iterator-points-to-the-last-item
 */

template <typename Iter, typename Cont>
bool is_last(Iter iter, const Cont& cont)
{
    return (iter != cont.end()) && (next(iter) == cont.end());
}

/*
 * The class Histogram constructs and maintains a histogram of input data. The bins can be of any data type, but most likely int or double.
 */
template<typename T> class Histogram
{
    template<typename T> friend std::ostream& operator<<(std::ostream &stream, const Histogram<T> &hist)
    {
        std::stringstream ss;

        for (std::map<T, Frequency>::const_iterator iter = hist._data.begin(); iter != hist._data.end(); iter++)
        {
            ss << iter->second;

            if (!is_last(iter, hist._data))
            {
                ss << ",";
            }
        }

        stream << ss.str();

        return stream;
    }

    public:
        /*
         * Construct an empty histogram
         */
        Histogram() {}

        /*
         * Construct a histogram with no initial data, with nbins bins. The bins are of equal size from min to max.
         */
        Histogram(std::size_t nbins, T min, T max);

        /*
         * Add a new bin. This function does nothing if already added.
         */
        inline void add(T bin) { if (!_data.count(bin)) { _data[bin] = 0; } }

        /*
         * Increase the frequency by one for the given bin.
         */
        inline void count(T bin) { count(bin, 1); }

        /*
         * Get the frequency count for the given bin.
         */
        Frequency getFreq(T bin) const;

        /*
         * Increase the frequency by n for the given bin.
         */
        void count(T bin, int n);

        /*
         * Remove all frequency data values from the histogram. Each bin count is set to 0.
         */
        void reset();

        /*
         * Return the number of bins
         */
        inline std::size_t size() const { return _data.size(); }

        /*
         * Return all bins associated with this historgram to the given vector.
         */

        void getBins(std::vector<T> &bins) const;

    private:
        std::map<T, Frequency> _data;
};


#endif
