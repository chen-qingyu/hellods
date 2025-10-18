/**
 * @file BinaryHeap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Binary heap implemented by array. Default is max-heap.
 * @date 2022.01.29
 */

#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include "../List/ArrayList.hpp"

#include "../Map/HashMap.hpp" // for operator==()

namespace hellods
{

template <typename T, typename Cmp = std::greater<T>>
class BinaryHeap : public detail::Container
{
    using detail::Container::MAX_CAPACITY;

    ArrayList<T> list_;

    // Adjust an element: process down.
    void proc_down(int index)
    {
        while (index * 2 + 1 < list_.size_ && Cmp()(list_.data_[index * 2 + 1], list_.data_[index]) || index * 2 + 2 < list_.size_ && Cmp()(list_.data_[index * 2 + 2], list_.data_[index]))
        {
            // if size is even then only have left node, short to avoid subscript out of bounds
            bool is_left_max = (list_.size_ % 2 == 0) || Cmp()(list_.data_[index * 2 + 1], list_.data_[index * 2 + 2]);
            std::swap(list_.data_[index], is_left_max ? list_.data_[index * 2 + 1] : list_.data_[index * 2 + 2]);
            index = index * 2 + (is_left_max ? 1 : 2);
        }
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty heap.
    BinaryHeap()
        : list_()
    {
    }

    /// Create a heap based on the given initializer list.
    BinaryHeap(const std::initializer_list<T>& il)
        : list_(il)
    {
        // build heap
        for (int i = (list_.size_ - 1) / 2; i >= 0; i--)
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
        if (list_.size_ != that.list_.size_ || (!is_empty() && peek() != that.peek()))
        {
            return false;
        }

        // count elements in each heap
        HashMap<T, int> this_map, that_map;
        for (int i = 0; i < list_.size_; i++)
        {
            this_map.contains(list_.data_[i]) ? ++this_map[list_.data_[i]] : this_map.insert(list_.data_[i], 1);
            that_map.contains(that.list_.data_[i]) ? ++that_map[that.list_.data_[i]] : that_map.insert(that.list_.data_[i], 1);
        }

        return this_map == that_map;
    }

    /*
     * Access
     */

    /// Peek the top element in the heap.
    const T& peek() const
    {
        detail::check_empty(list_.size_);
        return list_.data_[0];
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return list_.size_;
    }

    /*
     * Manipulation
     */

    /// Push an element onto the heap.
    void push(const T& element)
    {
        detail::check_full(list_.size_, MAX_CAPACITY);

        // expand capacity if need
        if (list_.size_ == list_.capacity_)
        {
            list_.expand_capacity();
        }

        int pos;
        for (pos = list_.size_++; pos != 0 && Cmp()(element, list_.data_[pos / 2]); pos /= 2)
        {
            list_.data_[pos] = list_.data_[pos / 2];
        }
        list_.data_[pos] = element;
    }

    /// Remove the top element from the heap and return it.
    T pop()
    {
        detail::check_empty(list_.size_);

        T element = std::move(list_.data_[0]);
        list_.data_[0] = list_.data_[list_.size_ - 1];
        list_.size_--;
        proc_down(0);

        return element;
    }

    /// Remove all of the elements from the heap.
    void clear()
    {
        list_.clear();
    }

    /*
     * Print
     */

    /// Print the heap.
    friend std::ostream& operator<<(std::ostream& os, const BinaryHeap& heap)
    {
        std::ostringstream oss;
        oss << heap.list_;
        return os << "Heap" << oss.str().erase(0, 4);
    }
};

} // namespace hellods

#endif // BINARYHEAP_HPP
