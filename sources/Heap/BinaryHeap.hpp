/**
 * @file BinaryHeap.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Binary heap implemented by array. This is max-heap.
 * @date 2022.01.29
 *
 * @copyright Copyright (C) 2022
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include "../common/utility.hpp"

#include "../List/ArrayList.hpp"

namespace hellods
{

template <typename T>
class BinaryHeap
{
private:
    // An array list.
    ArrayList<T> alist_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty heap.
    BinaryHeap()
        : alist_()
    {
    }

    /// Create a heap based on the given initializer list.
    BinaryHeap(const std::initializer_list<T>& il)
        : alist_(il)
    {
        // TODO: build heap
    }

    /*
     * Comparison
     */

    /// Check whether two heaps are equal.
    bool operator==(const BinaryHeap& that) const
    {
        return alist_ == that.alist_;
    }

    /// Check whether two heaps are not equal.
    bool operator!=(const BinaryHeap& that) const
    {
        return alist_ != that.alist_;
    }

    /*
     * Access
     */

    /// Returns const reference of the greatest item in the heap.
    const T& peek() const
    {
        common::check_empty(alist_.size());
        return alist_[0];
    }

    /*
     * Examination
     */

    /// Get the number of elements of the deque.
    int size() const
    {
        return alist_.size();
    }

    /// Check if the deque is empty.
    bool is_empty() const
    {
        return alist_.is_empty();
    }

    /*
     * Manipulation
     */

    /// Pushes an element onto the heap.
    void push(const T& element)
    {
        // TODO: get rid of the dependence on data[0] (MAX_ITEM = INT_MAX)
        // ref: https://doc.rust-lang.org/src/alloc/collections/binary_heap/mod.rs.html#610

        /*
        check_full(self->size, MAX_CAPACITY);

        if (self->size == self->capacity) // need to expand capacity
        {
            expand_capacity(self);
        }

        int pos;
        for (pos = ++self->size; self->data[pos / 2] < data; pos /= 2)
        {
            self->data[pos] = self->data[pos / 2];
        }
        self->data[pos] = data;
        */
    }

    /// Removes the greatest element from the heap and returns it.
    T pop()
    {
        common::check_empty(alist_.size());

        // TODO: get rid of the dependence on data[0] (MAX_ITEM = INT_MAX)
        // ref: https://doc.rust-lang.org/src/alloc/collections/binary_heap/mod.rs.html#566

        /*
        check_empty(self->size);

        MaxHeapItem max_item = self->data[1];
        MaxHeapItem tmp = self->data[self->size--];

        int parent, child;
        for (parent = 1; parent * 2 <= self->size; parent = child)
        {
            child = parent * 2;
            if ((child != self->size) && (self->data[child] < self->data[child + 1]))
            {
                child++;
            }

            if (tmp >= self->data[child])
            {
                break;
            }
            else
            {
                self->data[parent] = self->data[child];
            }
        }
        self->data[parent] = tmp;

        return max_item;
        */

        return T();
    }

    /// Remove all of the elements from the heap.
    BinaryHeap& clear()
    {
        alist_.clear();

        return *this;
    }
};

} // namespace hellods

#endif // BINARYHEAP_HPP
