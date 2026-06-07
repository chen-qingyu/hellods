/**
 * @file List.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract list interface.
 * @date 2025.10.12
 */

#ifndef LIST_HPP
#define LIST_HPP

#include "../core.hpp"

namespace hellods
{

/// Abstract list interface.
template <typename T, typename Cat = std::bidirectional_iterator_tag>
class List : public detail::Iterable<T, Cat>
{
public:
    using typename detail::Iterable<T, Cat>::ConstIterator;
    using typename detail::Iterable<T, Cat>::Iterator;

    /// @name Lifecycle
    /// @{

    /// Virtual destructor.
    ~List() override = default;

    /// Return the type name for printing.
    const char* name() const override
    {
        return "List";
    }
    /// @}

    /// @name Access
    /// @{

    /// Return the reference to the element at the specified position in the list.
    virtual T& operator[](int index) = 0;

    /// Return the const reference to element at the specified position in the list.
    virtual const T& operator[](int index) const
    {
        return const_cast<List&>(*this)[index];
    }
    /// @}

    /// @name Examination
    /// @{

    /// Return an iterator to the first occurrence of the specified element, or end() if the list does not contain the element.
    virtual Iterator find(const T& element)
    {
        if constexpr (std::equality_comparable<T>)
        {
            return std::find(this->begin(), this->end(), element);
        }
        throw std::runtime_error("Error: List::find requires equality comparable elements.");
    }

    virtual ConstIterator find(const T& element) const
    {
        return const_cast<List&>(*this).find(element);
    }
    /// @}

    /// @name Manipulation
    /// @{

    /// Append the specified element to the list.
    virtual void append(const T& element) = 0;

    /// Insert the specified element at the specified position in the list.
    virtual void insert(int index, const T& element) = 0;

    /// Remove and return the element at the specified position in the list.
    virtual T remove(int index) = 0;

    /// Remove and return the last element in the list.
    virtual T pop()
    {
        return remove(this->size() - 1);
    }

    /// @}
};

} // namespace hellods

#endif // LIST_HPP
