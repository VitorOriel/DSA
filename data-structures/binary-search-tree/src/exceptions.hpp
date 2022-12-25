#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

class EmptyTreeException : public std::exception {
    public:
        EmptyTreeException(std::string msg) : message(msg) { };
        std::string what() { return this->message; }
    private:
        std::string message;
};

class NotFoundException : public std::exception {
    public:
        NotFoundException(std::string msg) : message(msg) { };
        std::string what() { return this->message; }
    private:
        std::string message;
};

#endif