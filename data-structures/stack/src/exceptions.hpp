/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

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