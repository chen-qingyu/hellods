/**
 * @file utility.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Utility functions of HelloDS.
 * @date 2023.01.05
 */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <algorithm>  // std::copy
#include <climits>    // INT_MAX
#include <cmath>      // std::abs
#include <functional> // std::std::greater std::hash std::equal_to
#include <iostream>   // std::ostream
#include <sstream>    // std::ostringstream
#include <stdexcept>  // std::runtime_error
#include <utility>    // std::initializer_list std::move

namespace hellods::common
{

// Check whether the index is valid (begin <= pos < end).
static inline void check_bounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        throw std::runtime_error("Error: Index out of range.");
    }
}

// Check whether is not empty.
static inline void check_empty(int size)
{
    if (size == 0)
    {
        throw std::runtime_error("Error: The container is empty.");
    }
}

// Check whether there is any remaining capacity.
static inline void check_full(int size, int capacity)
{
    if (size >= capacity)
    {
        throw std::runtime_error("Error: The container has reached the maximum size.");
    }
}

// Print function template for iterable container.
template <typename Iterable>
static inline std::ostream& print(std::ostream& os, const Iterable& iterable, const std::string& name)
{
    // This form looks complex, but there is only one judgment in the loop.
    // At the Assembly level (see https://godbolt.org/z/qT9n7GKf8), this is more efficient
    // than the usual short form of the generated machine code under O3-level optimization.
    // The inspiration comes from Java source code.

    if (iterable.is_empty())
    {
        return os << name << "()";
    }

    os << name << "(";
    auto it = iterable.begin();
    while (true)
    {
        os << *it++;
        if (it == iterable.end())
        {
            return os << ")";
        }
        os << ", ";
    }
}

// Print function template for std::pair.
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<const K, V>& pair)
{
    return os << pair.first << ": " << pair.second;
}

} // namespace hellods::common

#endif // UTILITY_HPP
