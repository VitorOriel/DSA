/*
 * Author: Vitor Oriel Borges
 * Data Structures and Algorithms
 */

#ifndef BASE_DATA_HPP
#define BASE_DATA_HPP

#include "namespace.hpp"

// Must override at least both operator< and operator== methods
class avl::BaseData {
    virtual bool operator<(const BaseData& other) const = 0;
    virtual bool operator==(const BaseData& other) const = 0;
};

#endif