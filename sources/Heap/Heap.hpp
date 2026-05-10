/**
 * @file Heap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract heap interface.
 * @date 2026.05.10
 */

#ifndef HEAP_HPP
#define HEAP_HPP

#include "../detail.hpp"

namespace hellods
{

/// Abstract heap interface.
template <typename T>
class Heap : public detail::Container
{
public:
    /// Iterator type.
    using Iterator = detail::BasicIterator<T, false, std::bidirectional_iterator_tag>;
    using ConstIterator = detail::BasicIterator<T, true, std::bidirectional_iterator_tag>;

    /*
     * Lifecycle
     */

    /// Virtual destructor.
    virtual ~Heap() = default;

    /*
     * Access
     */

    /// Peek the top element in the heap.
    virtual const T& peek() const = 0;

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the heap.
    /// Iteration order is the underlying array order (heap order), not priority order.
    virtual Iterator begin() = 0;

    /// Return a const iterator to the first element of the heap.
    virtual ConstIterator begin() const = 0;

    /// Return an iterator to the element following the last element of the heap.
    virtual Iterator end() = 0;

    /// Return a const iterator to the element following the last element of the heap.
    virtual ConstIterator end() const = 0;

    /*
     * Manipulation
     */

    /// Push an element onto the heap.
    virtual void push(const T& element) = 0;

    /// Remove the top element from the heap and return it.
    virtual T pop() = 0;

    /// Remove all of the elements from the heap.
    virtual void clear() = 0;
};

} // namespace hellods

#endif // HEAP_HPP
