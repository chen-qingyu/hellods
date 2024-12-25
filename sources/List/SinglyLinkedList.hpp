/**
 * @file SinglyLinkedList.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief List implemented by singly linked list.
 * @date 2022.01.28
 */

#ifndef SINGLYLINKEDLIST_HPP
#define SINGLYLINKEDLIST_HPP

#include "../detail.hpp"

namespace hellods
{

/// List implemented by singly linked list.
template <typename T>
class SinglyLinkedList : public detail::Container
{
private:
    // Node of singly linked list.
    struct Node
    {
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

public:
    /// List iterator class.
    class Iterator
    {
        friend class SinglyLinkedList;

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
            auto it = *this;
            current_ = current_->succ_;
            return it;
        }
    };

private:
    // Pointer to the header (rank = -1).
    Node* header_;

    // Clear the stored data.
    void clear_data()
    {
        while (header_->succ_ != nullptr)
        {
            auto node = header_->succ_->succ_;
            delete header_->succ_;
            header_->succ_ = node;
        }

        size_ = 0;
        header_->succ_ = nullptr;
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty list.
    SinglyLinkedList()
        : detail::Container(0)
        , header_(new Node(T()))
    {
    }

    /// Create a list based on the given initializer list.
    SinglyLinkedList(const std::initializer_list<T>& il)
        : detail::Container(int(il.size()))
        , header_(new Node(T()))
    {
        Node* current = header_;
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            auto node = new Node(*it);
            current->succ_ = node;
            current = node;
        }
    }

    /// Copy constructor.
    SinglyLinkedList(const SinglyLinkedList& that)
        : detail::Container(that.size_)
        , header_(new Node(T()))
    {
        Node* current = header_;
        for (auto it = that.begin(); it != that.end(); ++it)
        {
            auto node = new Node(*it);
            current->succ_ = node;
            current = node;
        }
    }

    /// Destroy the list object.
    ~SinglyLinkedList()
    {
        clear_data();
        delete header_;
    }

    /*
     * Comparison
     */

    /// Check whether two lists are equal.
    bool operator==(const SinglyLinkedList& that) const
    {
        return size_ == that.size_ && std::equal(begin(), end(), that.begin());
    }

    /// Check whether two lists are not equal.
    bool operator!=(const SinglyLinkedList& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the specified position in the list.
    T& operator[](int index)
    {
        detail::check_bounds(index, 0, size_);

        auto current = header_->succ_;
        for (int i = 0; i < index; ++i)
        {
            current = current->succ_;
        }

        return current->data_;
    }

    /// Return the const reference to element at the specified position in the list.
    const T& operator[](int index) const
    {
        return const_cast<SinglyLinkedList&>(*this)[index];
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
        return Iterator(nullptr);
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
        detail::check_full(size_, MAX_CAPACITY);
        detail::check_bounds(index, 0, size_ + 1);

        // index
        auto current = header_;
        for (int i = 0; i < index; i++)
        {
            current = current->succ_;
        }

        // insert
        auto node = new Node(element, current->succ_);
        current->succ_ = node;

        // resize
        ++size_;
    }

    /// Remove and return the element at the specified position in the list.
    T remove(int index)
    {
        // check
        detail::check_empty(size_);
        detail::check_bounds(index, 0, size_);

        // index
        auto current = header_;
        for (int i = 0; i < index; i++)
        {
            current = current->succ_;
        }

        // move data
        T data = std::move(current->succ_->data_);

        // remove
        auto node = current->succ_;
        current->succ_ = node->succ_;
        delete node;

        // resize
        --size_;

        // return data
        return data;
    }

    /// Perform the given action for each element of the list.
    template <typename F>
    SinglyLinkedList& map(const F& action)
    {
        std::for_each(begin(), end(), action);

        return *this;
    }

    /// Reverse the list in place.
    SinglyLinkedList& reverse()
    {
        auto p = header_->succ_;
        decltype(p) h = nullptr;
        while (p)
        {
            auto tmp = p->succ_;
            p->succ_ = h;
            h = p;
            p = tmp;
        }
        header_->succ_ = h;

        return *this;
    }

    /// Remove all of the elements from the list.
    void clear()
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
    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList& list)
    {
        return detail::print(os, list.begin(), list.end(), "List");
    }
};

} // namespace hellods

#endif // SINGLYLINKEDLIST_HPP
