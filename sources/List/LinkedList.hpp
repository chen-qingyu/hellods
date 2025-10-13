/**
 * @file LinkedList.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief List implemented by doubly linked list.
 * @date 2023.01.02
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "List.hpp"

namespace hellods
{

/// List implemented by doubly linked list.
template <typename T>
class LinkedList : public List<T>
{
protected:
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

    // Insert the given element at the given position.
    void insert_node(Node* pos, const T& element)
    {
        Node* node = new Node(element, pos->pred_, pos);
        pos->pred_->succ_ = node;
        pos->pred_ = node;

        ++size_;
    }

    // Remove and return the element at the given position.
    T remove_node(Node* pos)
    {
        T element = std::move(pos->data_);

        pos->pred_->succ_ = pos->succ_;
        pos->succ_->pred_ = pos->pred_;
        delete pos;

        --size_;

        return element;
    }

public:
    /// List iterator class.
    class Iterator
    {
        friend class LinkedList;

    protected:
        // Current node pointer.
        Node* current_;

        // Create an iterator that point to the current node of list.
        Iterator(Node* current)
            : current_(current)
        {
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = int;
        using pointer = value_type*;
        using reference = value_type&;

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

        /// Increment the iterator: ++it.
        Iterator& operator++()
        {
            current_ = current_->succ_;
            return *this;
        }

        /// Increment the iterator: it++.
        Iterator operator++(int)
        {
            auto it = *this;
            current_ = current_->succ_;
            return it;
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
            auto it = *this;
            current_ = current_->pred_;
            return it;
        }
    };

protected:
    using detail::Container::INIT_CAPACITY;
    using detail::Container::MAX_CAPACITY;
    using detail::Container::size_;

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
        : List<T>(0)
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
            insert_node(trailer_, *it);
        }
    }

    /// Copy constructor.
    LinkedList(const LinkedList& that)
        : LinkedList()
    {
        for (auto it = that.begin(); it != that.end(); ++it)
        {
            insert_node(trailer_, *it);
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

    /*
     * Access
     */

    /// Return the reference to the element at the specified position in the list. list[index] for index in 0..size() will be O(1) on each access.
    T& operator[](int index) override
    {
        detail::check_bounds(index, 0, size_);

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

    using List<T>::operator[];

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

    /// Append the specified element to the list.
    void append(const T& element) override
    {
        // check
        detail::check_full(size_, MAX_CAPACITY);

        // insert and resize
        insert_node(trailer_, element);
    }

    /// Insert the specified element at the specified position in the list.
    void insert(int index, const T& element) override
    {
        // check
        detail::check_full(size_, MAX_CAPACITY);
        detail::check_bounds(index, 0, size_ + 1);

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
        insert_node(current, element);
    }

    /// Remove and return the element at the specified position in the list.
    T remove(int index) override
    {
        // check
        detail::check_empty(size_);
        detail::check_bounds(index, 0, size_);

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

        // remove and return data
        return remove_node(current);
    }

    /// Remove all of the elements from the list.
    void clear() override
    {
        if (size_ != 0)
        {
            clear_data();
        }
    }

    /*
     * Print
     */

    /// Print the list.
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list)
    {
        return detail::print(os, list.begin(), list.end(), "List");
    }
};

} // namespace hellods

#endif // LINKEDLIST_HPP
