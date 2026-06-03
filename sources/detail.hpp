/**
 * @file detail.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief The internal details of HelloDS.
 * @date 2023.01.05
 */

#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <algorithm>  // std::copy
#include <cassert>    // assert
#include <climits>    // INT_MAX
#include <cmath>      // std::abs
#include <concepts>   // std::convertible_to std::copyable std::default_initializable std::predicate
#include <cstddef>    // std::size_t
#include <functional> // std::greater std::hash std::equal_to
#include <iterator>   // std::input_iterator
#include <memory>     // std::make_unique
#include <optional>   // std::optional std::nullopt
#include <ostream>    // std::ostream
#include <sstream>    // std::ostringstream
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string
#include <utility>    // std::initializer_list std::move

namespace hellods::detail
{

template <typename T>
concept Printable = requires(std::ostream& os, const T& value) {
    os << value;
};

// Check whether the index is valid (begin <= pos < end).
inline void check_bounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        throw std::runtime_error("Error: Index out of range.");
    }
}

// Check whether is not empty.
inline void check_empty(int size)
{
    if (size == 0)
    {
        throw std::runtime_error("Error: The container is empty.");
    }
}

// Check whether there is any remaining capacity.
inline void check_full(int size, int capacity)
{
    if (size >= capacity)
    {
        throw std::runtime_error("Error: The container has reached the maximum size.");
    }
}

// Internal key-value entry shared by HashMap, TreeMap, etc.
template <typename K, typename V>
struct MapEntry
{
    K key_;
    std::optional<V> value_;

    MapEntry() = default;

    MapEntry(const K& key, const V& value)
        : key_(key)
        , value_(value)
    {
    }

    // Key-only constructor for tree lookup without requiring V to be default-constructible.
    explicit MapEntry(const K& key)
        : key_(key)
        , value_(std::nullopt)
    {
    }

    const K& key() const
    {
        return key_;
    }

    V& value()
    {
        return *value_;
    }

    const V& value() const
    {
        return *value_;
    }

    // For tree ordering: compare by key only.
    bool operator<(const MapEntry& rhs) const
    {
        return key_ < rhs.key_;
    }

    bool operator==(const MapEntry& rhs) const
    {
        return key_ == rhs.key_;
    }

    friend std::ostream& operator<<(std::ostream& os, const MapEntry& entry)
    {
        if constexpr (Printable<K> && Printable<V>)
        {
            return os << entry.key() << ": " << entry.value();
        }
        throw std::runtime_error("Error: MapEntry output requires Printable key and value.");
    }
};

// Print helper for range [`first`, `last`).
template <std::input_iterator InputIt>
inline std::ostream& print(std::ostream& os, const InputIt& first, const InputIt& last, const std::string& name)
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

} // namespace hellods::detail

#endif // DETAIL_HPP
