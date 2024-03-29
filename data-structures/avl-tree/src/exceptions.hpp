/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

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