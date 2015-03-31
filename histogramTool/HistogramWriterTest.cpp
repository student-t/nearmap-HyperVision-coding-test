#include <iostream>
#include <iostream>
#include "UnitTest.h"
#include "HistogramWriter.h"
#include "HistogramWriterTest.h"

using namespace std;

static void TestWriteEmptyHist()
{
    Histogram<int> redHist, greenHist, blueHist;
    RGBHistogram<int> hist(redHist, greenHist, blueHist);

    std::stringstream ss;
    HistogramWriter<int, std::stringstream>::write(hist, ss);

    IsTrue("\n\n\n", ss.str())
}

static void TestWriteRed()
{
    Histogram<int> redHist, greenHist, blueHist;
    RGBHistogram<int> hist(redHist, greenHist, blueHist);

    /*
     * Add bin 0 and 1
     */

    redHist.add(0);
    redHist.add(1);

    /*
     * Increment the frequency in each bin by 2
     */

    redHist.count(0);
    redHist.count(0);
    redHist.count(1);
    redHist.count(1);

    std::stringstream ss;
    HistogramWriter<int, std::stringstream>::write(hist, ss);

    IsTrue("2,2\n\n\n", ss.str());
}

static void TestWriteRGB()
{
    Histogram<int> redHist, greenHist, blueHist;
    RGBHistogram<int> hist(redHist, greenHist, blueHist);

    /*
     * Add bin 0 and 1 to redHist, bin 0 to greenHist and blueHist
     */

    redHist.add(0);
    redHist.add(1);
    greenHist.add(0);
    blueHist.add(0);

    /*
     * Increment the freqency in redHist by 2, increment the frequency in greenHist and blueHist by 1
     */

    redHist.count(0);
    redHist.count(0);
    redHist.count(1);
    redHist.count(1);
    greenHist.count(0);
    blueHist.count(0);

    std::stringstream ss;
    HistogramWriter<int, std::stringstream>::write(hist, ss);

    IsTrue("2,2\n1\n1\n", ss.str());
}

void HistogramWriterTest::run()
{
    TestWriteEmptyHist();
    TestWriteRed();
    TestWriteRGB();
}
