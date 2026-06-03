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

template <typename T, typename Cmp = std::greater<T>>
class BinaryHeap : public Heap<T>
{
    using Heap<T>::MAX_CAPACITY;

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

    struct CacheIter
    {
        std::shared_ptr<ArrayList<T>> data_;
        int index_;

        CacheIter(const ArrayList<T>& list)
            : data_(std::make_shared<ArrayList<T>>(list))
            , index_(0)
        {
            std::sort(data_->begin(), data_->end(), Cmp{});
        }

        CacheIter(int size)
            : data_(nullptr)
            , index_(size)
        {
        }

        const T& operator*() const
        {
            return (*data_)[index_];
        }

        bool operator==(const CacheIter& that) const
        {
            return index_ == that.index_;
        }

        CacheIter& operator++()
        {
            ++index_;
            return *this;
        }

        CacheIter& operator--()
        {
            --index_;
            return *this;
        }
    };

    /// Return an iterator to the first element of the heap.
    typename Heap<T>::Iterator begin() const override
    {
        return typename Heap<T>::Iterator(CacheIter(list_));
    }

    /// Return an iterator to the element following the last element of the heap.
    typename Heap<T>::Iterator end() const override
    {
        return typename Heap<T>::Iterator(CacheIter(list_.size()));
    }
};

} // namespace hellods

#endif // BINARYHEAP_HPP
