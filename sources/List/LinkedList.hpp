/**
 * @file LinkedList.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief List implemented by double linked list.
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

#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "../common/Container.hpp"
#include "../common/utility.hpp"

namespace hellods
{

template <typename T>
class LinkedDeque;

template <typename T>
class LinkedQueue;

template <typename T>
class LinkedStack;

/// List implemented by double linked list.
template <typename T>
class LinkedList : public common::Container
{
    friend class LinkedDeque<T>;
    friend class LinkedQueue<T>;
    friend class LinkedStack<T>;

private:
    // Node of doubly linked list.
    class Node
    {
        friend class LinkedList;
        friend class LinkedDeque<T>;
        friend class LinkedQueue<T>;
        friend class LinkedStack<T>;

    private:
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

    // Access helper. list[index] for index in 0..size() will be O(1) on each access.
    T& access(int index)
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
        if (size_ != that.size_)
        {
            return false;
        }

        for (Node *it1 = header_->succ_, *it2 = that.header_->succ_; it1 != trailer_; it1 = it1->succ_, it2 = it2->succ_)
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

    /// Return the index of the first occurrence of the specified element, or -1 if the list does not contains the element.
    int find(const T& element) const
    {
        int index = 0;
        Node* current = header_->succ_;

        while (current != trailer_ && current->data_ != element)
        {
            current = current->succ_;
            index++;
        }

        return current != trailer_ ? index : -1;
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
        for (Node* cur = header_->succ_; cur != trailer_; cur = cur->succ_)
        {
            action(cur->data_);
        }

        return *this;
    }

    /// Reverse the list in place.
    LinkedList& reverse()
    {
        for (Node* cur = header_; cur != nullptr; cur = cur->pred_)
        {
            common::swap(cur->pred_, cur->succ_);
        }
        common::swap(header_, trailer_);

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

#endif // DOUBLYLINKEDLIST_HPP
