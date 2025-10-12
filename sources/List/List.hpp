/**
 * @file List.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract list interface.
 * @date 2025.10.12
 */

#ifndef LIST_HPP
#define LIST_HPP

#include "../detail.hpp"

namespace hellods
{

/// Abstract list interface.
template <typename T>
class List : public detail::Container
{
public:
    /*
     * Constructor / Destructor
     */

    /// Constructor.
    List(int size)
        : detail::Container(size)
    {
    }

    /// Virtual destructor.
    virtual ~List() = default;

    /*
     * Access
     */

    /// Return the reference to the element at the specified position in the list.
    virtual T& operator[](int index) = 0;

    /// Return the const reference to element at the specified position in the list.
    virtual const T& operator[](int index) const = 0;

    /*
     * Manipulation
     */

    /// Add the specified element to the end of the list.
    virtual void add(const T& element) = 0;

    /// Insert the specified element at the specified position in the list.
    virtual void insert(int index, const T& element) = 0;

    /// Remove and return the element at the specified position in the list.
    virtual T remove(int index) = 0;

    /// Remove all of the elements from the list.
    virtual void clear() = 0;
};

} // namespace hellods

#endif // LIST_HPP