/**
 * @file utility.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Utility functions for HelloDS.
 * @date 2023.01.05
 */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <algorithm> // std::copy
#include <climits>   // INT_MAX
#include <cmath>     // std::abs
#include <stdexcept> // std::runtime_error
#include <utility>   // std::initializer_list std::move

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

// Swap the content of the two elements.
template <typename T>
static inline void swap(T& e1, T& e2)
{
    auto tmp = std::move(e1);
    e1 = std::move(e2);
    e2 = std::move(tmp);
}

} // namespace hellods::common

#endif // UTILITY_HPP
