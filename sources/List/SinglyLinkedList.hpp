/**
 * @file SinglyLinkedList.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief List implemented by singly linked list.
 * @date 2022.01.28
 */

#ifndef SINGLYLINKEDLIST_HPP
#define SINGLYLINKEDLIST_HPP

#include "List.hpp"

namespace hellods
{

/// List implemented by singly linked list.
template <typename T>
class SinglyLinkedList : public List<T, std::forward_iterator_tag>
{
protected:
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

protected:
    template <bool Const>
    class Iter
    {
        friend class SinglyLinkedList;

    protected:
        using Value = std::conditional_t<Const, const T, T>;
        using NodePtr = std::conditional_t<Const, const Node*, Node*>;

        NodePtr current_;

        // Create an iterator that point to the current node of list.
        Iter(NodePtr current)
            : current_(current)
        {
        }

    public:
        /// Dereference.
        Value& operator*() const
        {
            return current_->data_;
        }

        /// Check if two iterators are same.
        bool operator==(const Iter& that) const
        {
            return current_ == that.current_;
        }

        /// Increment the iterator.
        Iter& operator++()
        {
            current_ = current_->succ_;
            return *this;
        }
    };

protected:
    using Base = List<T, std::forward_iterator_tag>;
    using Base::INIT_CAPACITY;
    using Base::MAX_CAPACITY;

    // Number of elements.
    int size_;

    // Pointer to the header (rank = -1).
    Node* header_;

    // Pointer to the tail (last element, rank = size - 1), nullptr if empty.
    Node* tail_;

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
        tail_ = nullptr;
    }

    // Swap with another list.
    void swap(SinglyLinkedList& that)
    {
        std::swap(size_, that.size_);
        std::swap(header_, that.header_);
        std::swap(tail_, that.tail_);
    }

public:
    /*
     * Lifecycle
     */

    /// Create an empty list.
    SinglyLinkedList()
        : size_(0)
        , header_(new Node(T()))
        , tail_(nullptr)
    {
    }

    /// Create a list based on the given initializer list.
    SinglyLinkedList(const std::initializer_list<T>& il)
        : size_(int(il.size()))
        , header_(new Node(T()))
        , tail_(nullptr)
    {
        Node* current = header_;
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            auto node = new Node(*it);
            current->succ_ = node;
            current = node;
        }
        tail_ = current;
    }

    /// Copy constructor.
    SinglyLinkedList(const SinglyLinkedList& that)
        : size_(that.size_)
        , header_(new Node(T()))
        , tail_(nullptr)
    {
        Node* current = header_;
        for (auto it = that.begin(); it != that.end(); ++it)
        {
            auto node = new Node(*it);
            current->succ_ = node;
            current = node;
        }
        tail_ = current;
    }

    /// Move constructor.
    SinglyLinkedList(SinglyLinkedList&& that)
        : SinglyLinkedList()
    {
        swap(that);
    }

    SinglyLinkedList& operator=(SinglyLinkedList that)
    {
        swap(that);
        return *this;
    }

    /// Destroy the list object.
    ~SinglyLinkedList()
    {
        clear_data();
        delete header_;
    }

    /*
     * Access
     */

    /// Return the reference to the element at the specified position in the list.
    T& operator[](int index) override
    {
        detail::check_bounds(index, 0, size_);

        auto current = header_->succ_;
        for (int i = 0; i < index; ++i)
        {
            current = current->succ_;
        }

        return current->data_;
    }

    using Base::operator[]; // const

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the list.
    Base::Iterator begin() override
    {
        return Base::Iterator(Iter<false>(header_->succ_));
    }

    Base::ConstIterator begin() const override
    {
        return Base::ConstIterator(Iter<true>(header_->succ_));
    }

    /// Return an iterator to the element following the last element of the list.
    Base::Iterator end() override
    {
        return Base::Iterator(Iter<false>(nullptr));
    }

    Base::ConstIterator end() const override
    {
        return Base::ConstIterator(Iter<true>(nullptr));
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return size_;
    }

    /*
     * Manipulation
     */

    /// Append the specified element to the list.
    void append(const T& element) override
    {
        detail::check_full(size_, MAX_CAPACITY);

        auto node = new Node(element);
        if (tail_ == nullptr)
        {
            header_->succ_ = node;
        }
        else
        {
            tail_->succ_ = node;
        }
        tail_ = node;
        ++size_;
    }

    /// Insert the specified element at the specified position in the list.
    void insert(int index, const T& element) override
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

        // if inserted at the end, update tail
        if (index == size_)
        {
            tail_ = node;
        }

        // resize
        ++size_;
    }

    /// Remove and return the element at the specified position in the list.
    T remove(int index) override
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

        // if removed the last element, update tail
        if (index == size_ - 1)
        {
            tail_ = (current == header_) ? nullptr : current;
        }

        // resize
        --size_;

        // return data
        return data;
    }

    /// Remove all of the elements from the list.
    void clear() override
    {
        if (size_ != 0)
        {
            clear_data();
        }
    }
};

} // namespace hellods

#endif // SINGLYLINKEDLIST_HPP
