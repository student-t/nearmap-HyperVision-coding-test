#ifndef UNITTEST_H
#define UNITTEST_H

#include <iostream>

/*
 * This should be part of the unit test framework, eg, CppUnit, NUnit, GoogleTest etc.
 * Here, we are providing a simple implementation.
 */

#define IsTrue(expected, actual) \
{\
    if (expected != actual)\
    {\
        std::cerr << expected << " is not equal to " << actual; \
    }\
}\

#define IsThrown(x, Exception) \
{\
    try \
    { \
        x; \
           \
        std::cerr << "No exception has been thrown" << std::endl; \
    } \
    catch (Exception &) \
    { \
      \
    } \
    catch (...) \
    { \
        std::cerr << "The expected excpetion hasn't been thrown" << std::endl; \
    } \
}\


#endif
