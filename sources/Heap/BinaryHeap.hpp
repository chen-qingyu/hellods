/**
 * @file BinaryHeap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Binary heap implemented by array. Default is max-heap.
 * @date 2022.01.29
 */

#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include "../List/ArrayList.hpp"
#include "Heap.hpp"

namespace hellods
{

template <detail::StoredElement T, typename Cmp = std::greater<T>>
    requires detail::ComparatorFor<T, Cmp>
class BinaryHeap : public Heap<T>
{
    using detail::Container::MAX_CAPACITY;

    ArrayList<T> list_;

    // Adjust an element: process down.
    void proc_down(int index)
    {
        while (index * 2 + 1 < list_.size())
        {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int target = left;

            // choose the larger/smaller child according to comparator
            if (right < list_.size() && Cmp()(list_[right], list_[left]))
            {
                target = right;
            }

            // if parent satisfies heap property, done
            if (!Cmp()(list_[target], list_[index]))
            {
                break;
            }

            std::swap(list_[index], list_[target]);
            index = target;
        }
    }

public:
    /*
     * Lifecycle
     */

    /// Create an empty heap.
    BinaryHeap() = default;

    /// Create a heap based on the given initializer list.
    BinaryHeap(const std::initializer_list<T>& il)
        : list_(il)
    {
        // build heap
        for (int i = (list_.size() - 1) / 2; i >= 0; i--)
        {
            proc_down(i);
        }
    }

    BinaryHeap(const BinaryHeap&) = default;
    BinaryHeap(BinaryHeap&&) = default;

    BinaryHeap& operator=(const BinaryHeap&) = default;
    BinaryHeap& operator=(BinaryHeap&&) = default;

    /*
     * Comparison
     */

    /// Check whether two heaps are equal.
    bool operator==(const BinaryHeap& that) const
    {
        if (list_.size() != that.list_.size())
        {
            return false;
        }

        // copy raw data to temporary arrays, sort, then compare element by element
        auto this_data = std::make_unique<T[]>(list_.size());
        std::copy(list_.begin(), list_.end(), this_data.get());
        std::sort(this_data.get(), this_data.get() + list_.size(), Cmp{});

        auto that_data = std::make_unique<T[]>(that.list_.size());
        std::copy(that.list_.begin(), that.list_.end(), that_data.get());
        std::sort(that_data.get(), that_data.get() + that.list_.size(), Cmp{});

        return std::equal(this_data.get(), this_data.get() + list_.size(), that_data.get());
    }

    /*
     * Access
     */

    /// Peek the top element in the heap.
    const T& peek() const override
    {
        detail::check_empty(list_.size());
        return list_[0];
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return list_.size();
    }

    /*
     * Manipulation
     */

    /// Push an element onto the heap.
    void push(const T& element) override
    {
        detail::check_full(list_.size(), MAX_CAPACITY);

        list_.append(element);

        for (int pos = list_.size() - 1; pos != 0 && Cmp()(list_[pos], list_[(pos - 1) / 2]); pos = (pos - 1) / 2)
        {
            std::swap(list_[pos], list_[(pos - 1) / 2]);
        }
    }

    /// Remove the top element from the heap and return it.
    T pop() override
    {
        detail::check_empty(list_.size());

        T element = std::move(list_[0]);
        list_[0] = list_[list_.size() - 1];
        list_.pop();
        proc_down(0);

        return element;
    }

    /// Remove all of the elements from the heap.
    void clear() override
    {
        list_.clear();
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the heap.
    /// The order is the underlying array order (heap order), not priority order.
    Heap<T>::Iterator begin() override
    {
        return list_.begin();
    }

    Heap<T>::ConstIterator begin() const override
    {
        return list_.begin();
    }

    /// Return an iterator to the element following the last element of the heap.
    Heap<T>::Iterator end() override
    {
        return list_.end();
    }

    Heap<T>::ConstIterator end() const override
    {
        return list_.end();
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
