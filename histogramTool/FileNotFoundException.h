#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <string>

class FileNotFoundException : public std::runtime_error
{
public:
    FileNotFoundException(const std::string &message) : std::runtime_error(message) {}
};

#endif
