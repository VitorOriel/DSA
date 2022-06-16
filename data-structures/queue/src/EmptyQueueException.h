#ifndef EMPTY_QUEUE_EXCEPTION_H
#define EMPTY_QUEUE_EXCEPTION_H

#include <string>
#include <stdexcept>

class EmptyQueueException : public std::exception {
    public:
        EmptyQueueException(std::string msg) : message(msg) { };
        std::string what() { return this->message; }
    private:
        std::string message;
};

#endif