#ifndef THREADCOORD_H
#define THREADCOORD_H

#include <assert.h>
#include <QThread>
#include <algorithm>

typedef unsigned int DataSize;
typedef unsigned int BlockSize;
typedef unsigned int ThreadNum;

/*
 * This coordinator is responsible for managing thread operations. Threads are organized in blocks.
 *
 * For example, if we have an image of 10 * 10 dimension, and we have 4 threads.
 *
 *   Thread 1 => Block => 0 to 24
 *   Thread 2 => Block => 25 to 49
 *   Thread 3 => Block => 50 to 74
 *   Thread 4 => Block => 75 to 99
 */
class ThreadCoord
{
public:
    /*
     * Calculate the block size for an array, each block is equally divided among threads.
     */
    inline static BlockSize getBlock(DataSize size, ThreadNum threads)
    {
        return size / threads;
    }

    /*
     * We define a functor for flexibility, for instance, WorkerThread can be reused for image writing.
     */
    template<class Functor> class WorkerThread : public QThread
    {
    public:
        WorkerThread(std::size_t from, std::size_t to, Functor &fun) : _from(from), _to(to), _fun(fun) {}

    protected:
        void run()
        {
            for (std::size_t i = _from; i < _to; i++)
            {
                _fun(i);
            }
        }

    private:
        Functor _fun;

        /*
         * The starting and ending index that this thread is responsible for
         */

        std::size_t _from, _to;
    };

    /*
     * Start a generic multi-threaded execution. The execution is given by the functor.
     * size is the size of the input data, the workload is equally shared among worker threads.
     */
    template<typename Functor> static void start(DataSize size, ThreadNum threadNum, Functor f)
    {
        // The size of the block must be perfectly divisable
        assert(size / threadNum);

        /*
         * Important: It would be better to use boost::scoped_array or boost::shared_array for
         *            the array. We want to prevent memory leak if an exception is thrown before
         *            we reach "delete[] threads". To simplify the build process, boost is not
         *            used here.
         */

        std::auto_ptr<QThread> *threads = new std::auto_ptr<QThread>[threadNum];

        int allocated = 0;

        /*
         * A block is a region of the image array that a thread is responsibile for. If we use
         * only a single thread, the block is equivalent to the entire image.
         */

        const BlockSize blockSize = ThreadCoord::getBlock(size, threadNum);

        for (ThreadNum i = 0; i < threadNum; i++)
        {
            /*
             * A thread is responsible for the range [allocated, allocated + block). For example, if we have
             * 256 pixels and we have 2 threads.
             *
             *   Thread 1: 0 to 127
             *   Thread 2: 128 to 256
             */

            threads[i] = std::auto_ptr<QThread>(new WorkerThread<Functor>(allocated, allocated + blockSize, f));
            threads[i]->start();

            allocated += blockSize;
        }

        /*
         * Wait until all worker threads complete. In a more realistic application, we should wait for the
         * the finish signal (so that the application can do something useful while waiting).
         */

        for (unsigned int i = 0; i < threadNum; i++)
        {
            threads[i]->wait();
        }

        delete[] threads;
    }
};

#endif
