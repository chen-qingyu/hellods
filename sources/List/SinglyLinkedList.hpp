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
template <detail::StoredElement T>
class SinglyLinkedList : public List<T>
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

public:
    template <bool Const>
    class BasicIterator
    {
        friend class SinglyLinkedList;

    protected:
        using NodePtr = std::conditional_t<Const, const Node*, Node*>;
        using Value = std::conditional_t<Const, const T, T>;

        NodePtr current_;

        // Create an iterator that point to the current node of list.
        BasicIterator(NodePtr current)
            : current_(current)
        {
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = int;
        using pointer = Value*;
        using reference = Value&;

        /// Dereference.
        reference operator*() const
        {
            return current_->data_;
        }

        /// Get current pointer.
        pointer operator->() const
        {
            return &current_->data_;
        }

        /// Check if two iterators are same.
        bool operator==(const BasicIterator& that) const
        {
            return current_ == that.current_;
        }

        /// Increment the iterator: ++it.
        BasicIterator& operator++()
        {
            current_ = current_->succ_;
            return *this;
        }

        /// Increment the iterator: it++.
        BasicIterator operator++(int)
        {
            auto it = *this;
            current_ = current_->succ_;
            return it;
        }
    };

    using Iterator = BasicIterator<false>;
    using ConstIterator = BasicIterator<true>;

protected:
    using detail::Container::INIT_CAPACITY;
    using detail::Container::MAX_CAPACITY;

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
        : size_(that.size_)
        , header_(that.header_)
        , tail_(that.tail_)
    {
        that.size_ = 0;
        that.header_ = new Node(T());
        that.tail_ = nullptr;
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
     * Comparison
     */

    /// Check whether two lists are equal.
    bool operator==(const SinglyLinkedList& that) const
        requires detail::LinearElement<T>
    {
        return size_ == that.size_ && std::equal(begin(), end(), that.begin());
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

    using List<T>::operator[]; // const

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the list.
    /// If the list is empty, the returned iterator will be equal to end().
    auto begin()
    {
        return Iterator(header_->succ_);
    }

    auto begin() const
    {
        return ConstIterator(header_->succ_);
    }

    /// Return an iterator to the element following the last element of the list.
    /// This element acts as a placeholder, attempting to access it results in undefined behavior.
    auto end()
    {
        return Iterator(nullptr);
    }

    auto end() const
    {
        return ConstIterator(nullptr);
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return size_;
    }

    /// Return an iterator to the first occurrence of the specified element, or end() if the list does not contains the element.
    Iterator find(const T& element)
        requires detail::LinearElement<T>
    {
        return std::find(begin(), end(), element);
    }

    ConstIterator find(const T& element) const
        requires detail::LinearElement<T>
    {
        return std::find(begin(), end(), element);
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
