#include "UnitTest.h"
#include "Histogram.h"
#include "HistogramTest.h"
#include "BinNotFoundException.h"

using namespace std;

static void TestNumberOfBins()
{
    const int min = 0;
    const int max = 9;
    const size_t nbins = 10;

    Histogram<int> hist(nbins, min, max);

    IsTrue(nbins, hist.size());
}

static void TestCheckUnknownBin()
{
    const int min = 0;
    const int max = 9;
    const int invalidBin = 101;
    const size_t nbins = 10;

    Histogram<int> hist(nbins, min, max);

    IsThrown(hist.getFreq(invalidBin), BinNotFoundException<int>);
}

static void TestForEmptyHistogram()
{
    const int min = 0;
    const int max = 3;
    const size_t nbins = 4;

    Histogram<int> hist(nbins, min, max);

    vector<int> bins;
    hist.getBins(bins);

    IsTrue(0, bins[0]);
    IsTrue(1, bins[1]);
    IsTrue(2, bins[2]);
    IsTrue(3, bins[3]);
}

static void TestForAddDuplicateBin()
{
    const int bin = 10;

    Histogram<int> hist;

    hist.add(bin);
    hist.add(bin);

    const Frequency freq = hist.getFreq(bin);

    IsTrue(0, freq);
}

static void TestForFreqIncrement()
{
    const int bin = 10;

    Histogram<int> hist;

    hist.add(bin);
    hist.count(bin);
    hist.count(bin);

    const Frequency freq = hist.getFreq(bin);

    IsTrue(2, freq);
}

static void TestForFreqReset()
{
    const int bin = 10;

    Histogram<int> hist;

    hist.add(bin);
    hist.count(bin);
    hist.reset();

    const Frequency freq = hist.getFreq(bin);

    IsTrue(0, freq);
}

void HistogramTest::run()
{
    TestNumberOfBins();
    TestCheckUnknownBin();
    TestForEmptyHistogram();
    TestForAddDuplicateBin();
    TestForFreqIncrement();
    TestForFreqReset();
}
