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
class Heap : public detail::ConstIterable<detail::BasicIterator<T, true, std::bidirectional_iterator_tag>>
{
public:
    using Base = detail::ConstIterable<detail::BasicIterator<T, true, std::bidirectional_iterator_tag>>;
    using typename Base::Iterator;

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
     * Manipulation
     */

    /// Push an element onto the heap.
    virtual void push(const T& element) = 0;

    /// Remove the top element from the heap and return it.
    virtual T pop() = 0;
};

} // namespace hellods

#endif // HEAP_HPP
