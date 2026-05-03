/**
 * @file BinaryHeap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Binary heap implemented by array. Default is max-heap.
 * @date 2022.01.29
 */

#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include "../List/ArrayList.hpp"

namespace hellods
{

template <detail::StoredElement T, typename Cmp = std::greater<T>>
    requires detail::ComparatorFor<T, Cmp>
class BinaryHeap : public detail::Container
{
    using detail::Container::MAX_CAPACITY;

    ArrayList<T> list_;

    // Adjust an element: process down.
    void proc_down(int index)
    {
        while (index * 2 + 1 < list_.size_)
        {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int target = left;

            // choose the larger/smaller child according to comparator
            if (right < list_.size_ && Cmp()(list_.data_[right], list_.data_[left]))
            {
                target = right;
            }

            // if parent satisfies heap property, done
            if (!Cmp()(list_.data_[target], list_.data_[index]))
            {
                break;
            }

            std::swap(list_.data_[index], list_.data_[target]);
            index = target;
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

    BinaryHeap(const BinaryHeap&) = default;
    BinaryHeap(BinaryHeap&&) = default;

    BinaryHeap& operator=(const BinaryHeap&) = delete;
    BinaryHeap& operator=(BinaryHeap&&) = delete;

    /*
     * Comparison
     */

    /// Check whether two heaps are equal.
    bool operator==(const BinaryHeap& that) const
    {
        if (list_.size_ != that.list_.size_)
        {
            return false;
        }

        // copy raw data to temporary arrays, sort, then compare element by element
        auto this_data = std::make_unique<T[]>(list_.size_);
        std::copy(list_.data_, list_.data_ + list_.size_, this_data.get());
        std::sort(this_data.get(), this_data.get() + list_.size_, Cmp{});

        auto that_data = std::make_unique<T[]>(that.list_.size_);
        std::copy(that.list_.data_, that.list_.data_ + that.list_.size_, that_data.get());
        std::sort(that_data.get(), that_data.get() + that.list_.size_, Cmp{});

        return std::equal(this_data.get(), this_data.get() + list_.size_, that_data.get());
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
        for (pos = list_.size_++; pos != 0 && Cmp()(element, list_.data_[(pos - 1) / 2]); pos = (pos - 1) / 2)
        {
            list_.data_[pos] = list_.data_[(pos - 1) / 2];
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
