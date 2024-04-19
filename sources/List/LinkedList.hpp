/**
 * @file LinkedList.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief List implemented by doubly linked list.
 * @date 2023.01.02
 *
 * @copyright Copyright (C) 2023
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

#include "../common/Container.hpp"
#include "../common/utility.hpp"

namespace hellods
{

/// List implemented by doubly linked list.
template <typename T>
class LinkedList : public common::Container
{
    template <typename _>
    friend class LinkedDeque;

    template <typename _>
    friend class LinkedQueue;

    template <typename _>
    friend class LinkedStack;

private:
    // Node of doubly linked list.
    struct Node
    {
        // Data stored in the node.
        T data_;

        // Predecessor.
        Node* pred_;

        // Successor.
        Node* succ_;

        // Create a node with given element.
        Node(const T& data, Node* pred = nullptr, Node* succ = nullptr)
            : data_(data)
            , pred_(pred)
            , succ_(succ)
        {
        }
    };

public:
    /// List iterator class.
    class Iterator
    {
        friend class LinkedList;

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = int;
        using pointer = value_type*;
        using reference = value_type&;

    private:
        // Current node pointer.
        Node* current_;

        // Create an iterator that point to the current node of list.
        Iterator(Node* current)
            : current_(current)
        {
        }

    public:
        /// Dereference.
        T& operator*() const
        {
            return current_->data_;
        }

        /// Get current pointer.
        T* operator->() const
        {
            return &current_->data_;
        }

        /// Check if two iterators are same.
        bool operator==(const Iterator& that) const
        {
            return current_ == that.current_;
        }

        /// Check if two iterators are different.
        bool operator!=(const Iterator& that) const
        {
            return !(current_ == that.current_);
        }

        /// Increment the iterator: ++it.
        Iterator& operator++()
        {
            current_ = current_->succ_;
            return *this;
        }

        /// Increment the iterator: it++.
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            current_ = current_->succ_;
            return tmp;
        }

        /// Decrement the iterator: --it.
        Iterator& operator--()
        {
            current_ = current_->pred_;
            return *this;
        }

        /// Decrement the iterator: it--.
        Iterator operator--(int)
        {
            Iterator tmp = *this;
            current_ = current_->pred_;
            return tmp;
        }
    };

private:
    // Pointer to the header (rank = -1).
    Node* header_;

    // Pointer to the trailer (rank = size).
    Node* trailer_;

    // Index of the latest accessed element. For operator[]().
    int latest_;

    // Pointer to the latest accessed element. For operator[]().
    Node* p_latest_;

    // Clear the stored data.
    void clear_data()
    {
        while (header_->succ_ != trailer_)
        {
            Node* node = header_->succ_->succ_;
            delete header_->succ_;
            header_->succ_ = node;
        }

        size_ = 0;
        header_->succ_ = trailer_;
        trailer_->pred_ = header_;
        latest_ = -1;
        p_latest_ = header_;
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty list.
    LinkedList()
        : common::Container(0)
        , header_(new Node(T()))
        , trailer_(new Node(T()))
        , latest_(-1)
        , p_latest_(header_)
    {
        header_->succ_ = trailer_;
        trailer_->pred_ = header_;
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
        delete trailer_;
    }

    /*
     * Comparison
     */

    /// Check whether two lists are equal.
    bool operator==(const LinkedList& that) const
    {
        return size_ == that.size_ && std::equal(begin(), end(), that.begin());
    }

    /// Check whether two lists are not equal.
    bool operator!=(const LinkedList& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the specified position in the list. list[index] for index in 0..size() will be O(1) on each access.
    T& operator[](int index)
    {
        common::check_bounds(index, 0, size_);

        // too far from the last accessed element
        if (std::abs(index - latest_) > size_ / 2)
        {
            // closer to the header or trailer
            p_latest_ = (index < latest_) ? header_->succ_ : trailer_->pred_;
            latest_ = (index < latest_) ? 0 : size_ - 1;
        }

        if (index < latest_)
        {
            while (index < latest_)
            {
                latest_--;
                p_latest_ = p_latest_->pred_;
            }
        }
        else if (index > latest_)
        {
            while (index > latest_)
            {
                latest_++;
                p_latest_ = p_latest_->succ_;
            }
        }
        // else the element accessed this time is the same as the last time

        return p_latest_->data_;
    }

    /// Return the const reference to element at the specified position in the list. list[index] for index in 0..size() will be O(1) on each access.
    const T& operator[](int index) const
    {
        return const_cast<LinkedList&>(*this)[index];
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the list.
    /// If the list is empty, the returned iterator will be equal to end().
    Iterator begin() const
    {
        return Iterator(header_->succ_);
    }

    /// Return an iterator to the element following the last element of the list.
    /// This element acts as a placeholder, attempting to access it results in undefined behavior.
    Iterator end() const
    {
        return Iterator(trailer_);
    }

    /*
     * Examination
     */

    /// Return an iterator to the first occurrence of the specified element, or end() if the list does not contains the element.
    Iterator find(const T& element) const
    {
        return std::find(begin(), end(), element);
    }

    /*
     * Manipulation
     */

    /// Insert the specified element at the specified position in the list.
    void insert(int index, const T& element)
    {
        // check
        common::check_full(size_, MAX_CAPACITY);
        common::check_bounds(index, 0, size_ + 1);

        // index
        Node* current = nullptr;
        if (index < size_ / 2)
        {
            current = header_->succ_;
            for (int i = 0; i < index; i++)
            {
                current = current->succ_;
            }
        }
        else
        {
            current = trailer_; // be careful, index may be same as size
            for (int i = size_; i > index; i--)
            {
                current = current->pred_;
            }
        }

        // insert
        Node* node = new Node(element, current->pred_, current);
        current->pred_->succ_ = node;
        current->pred_ = node;

        // resize
        ++size_;
    }

    /// Remove and return the element at the specified position in the list.
    T remove(int index)
    {
        // check
        common::check_empty(size_);
        common::check_bounds(index, 0, size_);

        // index
        Node* current = nullptr;
        if (index < size_ / 2)
        {
            current = header_->succ_;
            for (int i = 0; i < index; i++)
            {
                current = current->succ_;
            }
        }
        else
        {
            current = trailer_->pred_;
            for (int i = size_ - 1; i > index; i--)
            {
                current = current->pred_;
            }
        }

        // reset state of the latest accessed element if it was removed
        if (current == p_latest_)
        {
            latest_ = -1;
            p_latest_ = header_;
        }

        // move data
        T data = std::move(current->data_);

        // remove
        current->pred_->succ_ = current->succ_;
        current->succ_->pred_ = current->pred_;
        delete current;

        // resize
        --size_;

        // return data
        return data;
    }

    /// Perform the given action for each element of the list.
    template <typename F>
    LinkedList& map(const F& action)
    {
        std::for_each(begin(), end(), action);

        return *this;
    }

    /// Reverse the list in place.
    LinkedList& reverse()
    {
        for (Node* cur = header_; cur != nullptr; cur = cur->pred_)
        {
            std::swap(cur->pred_, cur->succ_);
        }
        std::swap(header_, trailer_);

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

    /*
     * Print
     */

    /// Print the list.
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list)
    {
        os << "List(";
        for (auto it = list.header_->succ_; it != list.trailer_; it = it->succ_)
        {
            os << (it == list.header_->succ_ ? "" : ", ") << it->data_;
        }
        return os << ")";
    }
};

} // namespace hellods

#endif // LINKEDLIST_HPP
