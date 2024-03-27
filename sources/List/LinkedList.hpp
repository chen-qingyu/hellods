/**
 * @file LinkedList.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief List implemented by single linked list.
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

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "../utility.hpp"

namespace hellods
{

/// List implemented by single linked list.
template <typename T>
class LinkedList
{
private:
    // Node of linked list.
    class Node
    {
        friend class LinkedList;

    private:
        // Data stored in the node.
        T data_;

        // Successor.
        Node* succ_;

        // Create a node with given element.
        Node(const T& data, Node* succ = nullptr)
            : data_(data)
            , succ_(succ)
        {
        }
    };

    /// Number of elements.
    int size_;

    /// Pointer to the header (rank = -1).
    Node* header_;

    // Maximum capacity.
    static const int MAX_CAPACITY = INT_MAX - 1;

    // Clear the stored data.
    void clear_data()
    {
        while (header_->succ_ != nullptr)
        {
            Node* node = header_->succ_->succ_;
            delete header_->succ_;
            header_->succ_ = node;
        }

        size_ = 0;
        header_->succ_ = nullptr;
    }

    // Access helper.
    T& access(int index)
    {
        internal::check_bounds(index, 0, size_);

        Node* current = header_->succ_;
        for (int i = 0; i < index; ++i)
        {
            current = current->succ_;
        }

        return current->data_;
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty list.
    LinkedList()
        : size_(0)
        , header_(new Node(T()))

    {
        header_->succ_ = nullptr;
    }

    /// Create a list based on the given initializer list.
    LinkedList(const std::initializer_list<T>& il)
        : LinkedList()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(size_, *it);
        }
    }

    /// Destroy the list object.
    ~LinkedList()
    {
        clear_data();
        delete header_;
    }

    /*
     * Comparison
     */

    /// Check whether two lists are equal.
    bool operator==(const LinkedList& that) const
    {
        if (size_ != that.size_)
        {
            return false;
        }

        for (Node *it1 = header_->succ_, *it2 = that.header_->succ_; it1 != nullptr; it1 = it1->succ_, it2 = it2->succ_)
        {
            if (it1->data_ != it2->data_)
            {
                return false;
            }
        }

        return true;
    }

    /// Check whether two lists are not equal.
    bool operator!=(const LinkedList& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the specified position in the list.
    T& operator[](int index)
    {
        return access(index);
    }

    /// Return the const reference to element at the specified position in the list.
    const T& operator[](int index) const
    {
        return access(index);
    }

    /*
     * Examination
     */

    /// Get the number of elements of the list.
    int size() const
    {
        return size_;
    }

    /// Check if the list is empty.
    bool is_empty() const
    {
        return size_ == 0;
    }

    /// Return the index of the first occurrence of the specified element, or -1 if the list does not contains the element.
    int find(const T& element) const
    {
        int index = 0;
        Node* current = header_->succ_;

        while (current != nullptr && current->data_ != element)
        {
            current = current->succ_;
            index++;
        }

        return current != nullptr ? index : -1;
    }

    /*
     * Manipulation
     */

    /// Insert the specified element at the specified position in the list.
    void insert(int index, const T& element)
    {
        // check
        internal::check_full(size_, MAX_CAPACITY);
        internal::check_bounds(index, 0, size_ + 1);

        // index
        Node* current = header_;
        for (int i = 0; i < index; i++)
        {
            current = current->succ_;
        }

        // insert
        Node* node = new Node(element, current->succ_);
        current->succ_ = node;

        // resize
        ++size_;
    }

    /// Remove and return the element at the specified position in the list.
    T remove(int index)
    {
        // check
        internal::check_empty(size_);
        internal::check_bounds(index, 0, size_);

        // index
        Node* current = header_;
        for (int i = 0; i < index; i++)
        {
            current = current->succ_;
        }

        // move data
        T data = std::move(current->succ_->data_);

        // remove
        Node* node = current->succ_;
        current->succ_ = node->succ_;
        delete node;

        // resize
        --size_;

        // return data
        return data;
    }

    /// Perform the given action for each element of the list.
    template <typename F>
    LinkedList& map(const F& action)
    {
        for (Node* cur = header_->succ_; cur != nullptr; cur = cur->succ_)
        {
            action(cur->data_);
        }

        return *this;
    }

    /// Reverse the list in place.
    LinkedList& reverse()
    {
        Node* pre = header_->succ_;
        header_->succ_ = nullptr;
        while (pre)
        {
            Node* tmp = pre;
            pre = pre->succ_;
            tmp->succ_ = header_->succ_;
            header_->succ_ = tmp;
        }

        return *this;
    }

    /// Remove all of the elements from the list.
    LinkedList& clear()
    {
        if (size_ != 0)
        {
            clear_data();
        }

        return *this;
    }
};

} // namespace hellods

#endif // LINKEDLIST_HPP
