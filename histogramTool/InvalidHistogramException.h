#ifndef INVALIDHISTOGRAMEXCEPTION_H
#define INVALIDHISTOGRAMEXCEPTION_H

#include <string>

class InvalidHistogramException : public std::runtime_error
{
public:
    InvalidHistogramException(const std::string &message) : std::runtime_error(message) {}
};

#endif
