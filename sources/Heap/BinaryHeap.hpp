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

#include "../List/ArrayList.hpp"

#include <map> // for operator==()

namespace hellods
{

template <typename T>
class BinaryHeap : private ArrayList<T>
{
private:
    // Adjust an element: process down.
    void proc_down(int index)
    {
        while (index * 2 + 1 < size_ && data_[index] < data_[index * 2 + 1] || index * 2 + 2 < size_ && data_[index] < data_[index * 2 + 2])
        {
            // if size is even then only have left node, short to avoid subscript out of bounds
            bool is_left_max = (size_ % 2 == 0) || (data_[index * 2 + 1] > data_[index * 2 + 2]);
            common::swap(data_[index], is_left_max ? data_[index * 2 + 1] : data_[index * 2 + 2]);
            index = index * 2 + (is_left_max ? 1 : 2);
        }
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty heap.
    BinaryHeap()
        : ArrayList()
    {
    }

    /// Create a heap based on the given initializer list.
    BinaryHeap(const std::initializer_list<T>& il)
        : ArrayList(il)
    {
        // build heap
        for (int i = (size_ - 1) / 2; i >= 0; i--)
        {
            proc_down(i);
        }
    }

    /*
     * Comparison
     */

    /// Check whether two heaps are equal.
    bool operator==(const BinaryHeap& that) const
    {
        if (size() != that.size())
        {
            return false;
        }

        // count elements in each heap
        std::map<T, int> this_map, that_map;
        for (int i = 0; i < size(); i++)
        {
            this_map[data_[i]] = this_map.find(data_[i]) == this_map.end() ? 1 : this_map[data_[i]] + 1;
            that_map[that.data_[i]] = that_map.find(that.data_[i]) == that_map.end() ? 1 : that_map[that.data_[i]] + 1;
        }

        return this_map == that_map;
    }

    /// Check whether two heaps are not equal.
    bool operator!=(const BinaryHeap& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Returns const reference of the greatest item in the heap.
    const T& peek() const
    {
        common::check_empty(size());
        return data_[0];
    }

    /*
     * Examination
     */

    /// Get the number of elements of the heap.
    int size() const
    {
        return ArrayList::size();
    }

    /// Check if the heap is empty.
    bool is_empty() const
    {
        return ArrayList::is_empty();
    }

    /*
     * Manipulation
     */

    /// Pushes an element onto the heap.
    void push(const T& element)
    {
        common::check_full(size_, MAX_CAPACITY);

        // expand capacity if need
        if (size_ == capacity_)
        {
            expand_capacity();
        }

        int pos;
        for (pos = size_++; pos != 0 && data_[pos / 2] < element; pos /= 2)
        {
            data_[pos] = data_[pos / 2];
        }
        data_[pos] = element;
    }

    /// Removes the greatest element from the heap and returns it.
    T pop()
    {
        common::check_empty(size());

        T item = std::move(data_[0]);
        data_[0] = data_[size_ - 1];
        size_--;
        proc_down(0);

        return item;
    }

    /// Remove all of the elements from the heap.
    BinaryHeap& clear()
    {
        ArrayList::clear();

        return *this;
    }

    /*
     * Print
     */

    /// Print the heap.
    friend std::ostream& operator<<(std::ostream& os, const BinaryHeap& heap)
    {
        std::ostringstream oss;
        oss << static_cast<const ArrayList&>(heap);
        return os << "Heap" << oss.str().erase(0, 4);
    }
};

} // namespace hellods

#endif // BINARYHEAP_HPP
