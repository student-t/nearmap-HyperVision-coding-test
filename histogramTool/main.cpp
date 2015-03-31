#include <fstream>
#include <iostream>
#include <QStringList>
#include <QCoreApplication>
#include "ImageReader.h"
#include "HistogramWriter.h"

#include "HistogramTest.h"
#include "ThreadCoordTest.h"
#include "HistogramWriterTest.h"

#define RGB_COLOR_COMPONENT_SIZE 256

using namespace std;

/*
 * Remarks:
 *
 *   This solution divides an array of pixels into blocks. Each thread only read the pixels inside the block.
 *   The approach is similar to the programming model used in CUDA GPU programming.
 *
 *   Due to time constraint, the solution is not the most optimized. Here, I discuss a few possible optimizations.
 *
 *   TODO:
 *
 *      - We should create a list of independent histograms, one for each thread. Each thread adds frequency to its
 *        own histogram. The main thread is responsible for aggregating the results.
 *
 *        In the solution, we use only a single shared histogram. Thus, we must add a mutex lock. Locking and unlocking
 *        is expensive.
 *
 *      - We should not use a raw array pointer. What if an exception is thrown before we can release the pointer?
 *        We should have used boost::shared_array. To simplify the build, boost is not used in this solution.
 *
 *      - I have simplified the unit test cases, in a more realistic application, more test cases are needed.
 */

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    const QStringList args = app.arguments();

    /*
     * Arguments
     *
     * 1st: Input file
     * 2rd: Output file
     * 3rd: Number of threads
     */

    if (args.count() != 4)
    {
        std::cerr << "Invalid arguments, format: [Input File] [Output File] [Number of threads]" << std::endl;

        // It's an error if we don't have valid arguments
        return 1;
    }

    /*
     * Reference: http://qt-project.org/doc/qt-4.8/qstring.html#toInt
     */

    bool ok;

    // Number of threads used in calculations
    const int threads = args[3].toInt(&ok);

    if (!ok)
    {
        std::cerr << "Invalid argument, the number of threads must be an integer" << std::endl;

        // It's an error if the number of threads isn't an integer
        return 1;
    }

    // Input image file
    const QString &input = args[1];

    // Output ASCII file
    const QString &output = args[2];

    /*
     * Run the unit tests. In a realistic application, this should be done by the testing framework.
     */

    HistogramTest histTest;
    ThreadCoordTest threadTest;
    HistogramWriterTest writerTest;

    histTest.run();
    threadTest.run();
    writerTest.run();

    /*
     * Each color component has 8 bits (0 to 255), thus we want a integer reader.
     *
     * Instead, if the color component is measured in floats (eg: 0 to 1.0):
     *
     *    ImageReader<float> reader(input.toStdString())
     */

    ImageReader<int> reader(input.toStdString());

    // Set the number of threads used
    reader.setThreads(threads);

    /*
     * One histogram for each color component, this can be easily extended to other color models.
     *
     * Again, each color component has 8 bits (0 to 255), thus we instantiate with int.
     */

    Histogram<int> redHist, blueHist, greenHist;

    /*
     * Initalise the bins for each color component.
     */

    for (unsigned int i = 0; i < RGB_COLOR_COMPONENT_SIZE; i++)
    {
        redHist.add(i);
        greenHist.add(i);
        blueHist.add(i);
    }

    RGBHistogram<int> hist(redHist, blueHist, greenHist);

    /*
     * Read the image and construct the histograms
     */

    reader.calculate(hist);

    /*
     * Write the histogram to file
     */

    std::ofstream stream;

    stream.open(output.toStdString());

    if (stream.is_open())
    {
        HistogramWriter<int, std::ofstream>::write(hist, stream);
        stream.flush();
        stream.close();
    }
    else
    {
        std::cerr << "Failed to write to " << output.toStdString() << std::endl;
        return 1;
    }

    return 0;
}
