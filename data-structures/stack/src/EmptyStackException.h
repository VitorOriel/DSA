#ifndef EMPTY_STACK_EXCEPTION_H
#define EMPTY_STACK_EXCEPTION_H

#include <string>
#include <stdexcept>

class EmptyStackException : public std::exception {
    public:
        EmptyStackException(std::string msg) : message(msg) { };
        std::string what() { return this->message; }
    private:
        std::string message;
};

#endif