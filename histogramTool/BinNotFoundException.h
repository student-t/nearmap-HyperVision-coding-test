#ifndef BINNOTFOUNDEXCEPTION_H
#define BINNOTFOUNDEXCEPTION_H

#include <sstream>

/*
 * BinNotFoundException represents an error that a bin is not found in a histogram.
 * The type of the bin can be of any data type.
 */
template<typename Bin> class BinNotFoundException : public std::runtime_error
{
public:
    BinNotFoundException(const Bin &bin) : std::runtime_error(""), _bin(bin) {}

    virtual const char* what() const throw()
    {
        std::stringstream ss;
        ss << "Bin " << _bin << " not found";

        return ss.str().c_str();
    }

private:
    const Bin& _bin;
};

#endif
