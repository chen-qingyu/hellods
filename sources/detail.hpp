/**
 * @file detail.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief The internal details of HelloDS.
 * @date 2023.01.05
 */

#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <algorithm>  // std::copy
#include <climits>    // INT_MAX
#include <cmath>      // std::abs
#include <functional> // std::std::greater std::hash std::equal_to
#include <iterator>   // std::input_iterator
#include <ostream>    // std::ostream
#include <sstream>    // std::ostringstream
#include <stdexcept>  // std::runtime_error
#include <utility>    // std::initializer_list std::move

namespace hellods::detail
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

// Print function template for std::pair.
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<const K, V>& pair)
{
    return os << pair.first << ": " << pair.second;
}

// Print helper for range [`first`, `last`).
template <std::input_iterator InputIt>
static inline std::ostream& print(std::ostream& os, const InputIt& first, const InputIt& last, const std::string& name)
{
    // This form looks complex, but there is only one judgment in the loop.
    // At the Assembly level (see https://godbolt.org/z/qT9n7GKf8), this is more efficient
    // than the usual short form of the generated machine code under O3-level optimization.
    // The inspiration comes from Java source code.

    if (first == last)
    {
        return os << name << "()";
    }

    os << name << "(";
    auto it = first;
    while (true)
    {
        os << *it++;
        if (it == last)
        {
            return os << ")";
        }
        os << ", ";
    }
}

// Base container class for HelloDS.
class Container
{
protected:
    // Initial capacity.
    static const int INIT_CAPACITY = 8;

    // Maximum capacity.
    static const int MAX_CAPACITY = INT_MAX - 1;

    // Number of elements in the container.
    int size_;

public:
    // Constructor.
    Container(int size)
        : size_(size)
    {
    }

    // Get the number of elements of the container.
    int size() const
    {
        return size_;
    }

    // Check if the container is empty.
    bool is_empty() const
    {
        return size_ == 0;
    }
};

} // namespace hellods::detail

#endif // DETAIL_HPP
