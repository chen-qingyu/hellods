/**
 * @file Set.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract set interface.
 * @date 2026.05.10
 */

#ifndef SET_HPP
#define SET_HPP

#include "../core.hpp"

namespace hellods
{

/// Abstract set interface.
template <typename T>
class Set : public detail::ConstIterable<T>
{
public:
    using typename detail::ConstIterable<T>::Iterator;

    /// @name Lifecycle
    /// @{

    /// Virtual destructor.
    ~Set() override = default;

    /// Return the type name for printing.
    const char* name() const override
    {
        return "Set";
    }
    /// @}

    /// @name Search
    /// @{

    /// Return an iterator to the first occurrence of the specified element, or end() if the set does not contain the element.
    virtual Iterator find(const T& element) const = 0;

    /// Check if the set contains the specified element.
    virtual bool contains(const T& element) const
    {
        return find(element) != this->end();
    }
    /// @}

    /// @name Manipulation
    /// @{

    /// Insert the specified element into the set. Return true if the set changed as a result.
    virtual bool insert(const T& element) = 0;

    /// Remove the specified element from the set. Return true if the set changed as a result.
    virtual bool remove(const T& element) = 0;

    /// @}
};

} // namespace hellods

#endif // SET_HPP
