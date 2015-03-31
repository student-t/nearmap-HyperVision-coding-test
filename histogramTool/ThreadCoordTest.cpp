#include "UnitTest.h"
#include "ThreadCoord.h"
#include "ThreadCoordTest.h"

static void TestBlockSize()
{
    const DataSize  dataSize = 100;
    const ThreadNum threadNum = 4;

    const BlockSize blockSize = ThreadCoord::getBlock(dataSize, threadNum);

    IsTrue(25, blockSize);
}

static void TestAddOne()
{
    #define TEST_ARRAY_SIZE 6

    struct TestFun
    {
        TestFun(int *data) : data(data) {}

        void operator()(std::size_t i)
        {
            data[i]++;
        }

        int *data;
    };

    int data[TEST_ARRAY_SIZE];

    const int oldValue = 5;
    const int newValue = 6;

    for (std::size_t i = 0; i < TEST_ARRAY_SIZE; i++)
    {
        data[i] = oldValue;
    }

    const int numThreads = 2;

    ThreadCoord::start(TEST_ARRAY_SIZE, numThreads, TestFun(data));

    IsTrue(newValue, data[0]);
    IsTrue(newValue, data[1]);
    IsTrue(newValue, data[2]);
    IsTrue(newValue, data[3]);
    IsTrue(newValue, data[4]);
    IsTrue(newValue, data[5]);
}

void ThreadCoordTest::run()
{
    TestBlockSize();
    TestAddOne();
}

