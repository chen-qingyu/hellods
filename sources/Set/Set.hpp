/**
 * @file Set.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract set interface.
 * @date 2026.05.10
 */

#ifndef SET_HPP
#define SET_HPP

#include "../detail.hpp"

namespace hellods
{

/// Abstract set interface.
template <typename T>
class Set : public detail::Container
{
public:
    /// Iterator type — const access only (set elements must not be modified).
    using Iterator = detail::BasicIterator<T, true, std::bidirectional_iterator_tag>;
    using ConstIterator = Iterator;

    /*
     * Lifecycle
     */

    /// Virtual destructor.
    virtual ~Set() = default;

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the set.
    virtual Iterator begin() const = 0;

    /// Return an iterator to the element following the last element of the set.
    virtual Iterator end() const = 0;

    /*
     * Search
     */

    /// Return an iterator to the first occurrence of the specified element, or end() if the set does not contain the element.
    virtual Iterator find(const T& element) const = 0;

    /// Check if the set contains the specified element.
    virtual bool contains(const T& element) const
    {
        return find(element) != end();
    }

    /*
     * Manipulation
     */

    /// Insert the specified element into the set. Return true if the set changed as a result.
    virtual bool insert(const T& element) = 0;

    /// Remove the specified element from the set. Return true if the set changed as a result.
    virtual bool remove(const T& element) = 0;

    /// Remove all of the elements from the set.
    virtual void clear() = 0;
};

} // namespace hellods

#endif // SET_HPP
