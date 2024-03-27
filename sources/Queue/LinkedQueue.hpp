/**
 * @file LinkedQueue.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Queue implemented by single linked list.
 * @date 2022.01.28
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

#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include "../common/Container.hpp"
#include "../common/Node.hpp"
#include "../common/utility.hpp"

namespace hellods
{

/// Queue implemented by single linked list.
template <typename T>
class LinkedQueue : public common::Container
{
private:
    // Maximum capacity.
    static const int MAX_CAPACITY = INT_MAX - 1;

    // Pointer to the front element.
    common::Node<T>* front_;

    // Pointer to the rear element.
    common::Node<T>* rear_;

    // Clear the stored data.
    void clear_data()
    {
        while (front_->succ_ != nullptr)
        {
            auto node = front_->succ_->succ_;
            delete front_->succ_;
            front_->succ_ = node;
        }

        rear_ = front_;
        front_->succ_ = nullptr;
        size_ = 0;
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    LinkedQueue()
        : common::Container(0)
        , front_(new common::Node<T>(T(), nullptr))
        , rear_(front_)
    {
    }

    /// Create a queue based on the given initializer list.
    LinkedQueue(const std::initializer_list<T>& il)
        : LinkedQueue()
    {
        for (auto it = il.begin(); it != il.end(); it++)
        {
            enqueue(*it);
        }
    }

    /// Destroy the queue object.
    ~LinkedQueue()
    {
        clear_data();
        delete front_;
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const LinkedQueue& that) const
    {
        if (size_ != that.size_)
        {
            return false;
        }

        for (auto it1 = front_->succ_, it2 = that.front_->succ_; it1 != nullptr; it1 = it1->succ_, it2 = it2->succ_)
        {
            if (it1->data_ != it2->data_)
            {
                return false;
            }
        }

        return true;
    }

    /// Check whether two queues are not equal.
    bool operator!=(const LinkedQueue& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front()
    {
        common::check_empty(size_);
        return front_->succ_->data_;
    }

    /// Return the const reference to the element at the front in the queue.
    const T& front() const
    {
        common::check_empty(size_);
        return front_->succ_->data_;
    }

    /*
     * Examination
     */

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the end of the queue.
    void enqueue(const T& element)
    {
        common::check_full(size_, MAX_CAPACITY);

        auto node = new common::Node<T>(element, nullptr);

        rear_->succ_ = node;
        rear_ = node;

        ++size_;
    }

    /// Dequeue, pop the head element of the queue.
    T dequeue()
    {
        common::check_empty(size_);

        if (rear_ == front_->succ_)
        {
            rear_ = front_;
        }

        auto node = front_->succ_;
        T data = std::move(node->data_);

        front_->succ_ = node->succ_;
        delete node;

        --size_;

        return data;
    }

    /// Remove all of the elements from the queue.
    LinkedQueue& clear()
    {
        if (size_ != 0)
        {
            clear_data();
        }

        return *this;
    }
};

} // namespace hellods

#endif // LINKEDQUEUE_HPP
