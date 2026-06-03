/**
 * @file core.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief The core class hierarchy of HelloDS.
 * @date 2026.06.03
 */

#ifndef CORE_HPP
#define CORE_HPP

#include "detail.hpp"

namespace hellods::detail
{

// Base container class for HelloDS.
class Container
{
protected:
    // Initial capacity.
    static constexpr int INIT_CAPACITY = 8;

    // Maximum capacity.
    static constexpr int MAX_CAPACITY = INT_MAX - 1;

public:
    virtual ~Container() = default;

    // Get the number of elements of the container.
    virtual int size() const = 0;

    // Check if the container is empty.
    virtual bool is_empty() const
    {
        return size() == 0;
    }

    // Remove all of the elements from the container.
    virtual void clear() = 0;
};

// Type-erased bidirectional iterator.
// Wraps any concrete iterator via type erasure; forward-only iterators
// (e.g. SinglyLinkedList) throw on operator-- at runtime.
template <typename T, bool Const, typename Category = std::bidirectional_iterator_tag>
class BasicIterator
{
public:
    using RefType = std::conditional_t<Const, const T&, T&>;
    using PtrType = std::conditional_t<Const, const T*, T*>;

protected:
    struct Concept
    {
        virtual void advance() = 0;
        virtual void retreat() = 0;
        virtual RefType deref() const = 0;
        virtual PtrType arrow() const = 0;
        virtual bool equals(const Concept&) const = 0;
        virtual std::unique_ptr<Concept> clone() const = 0;
        virtual ~Concept() = default;
    };

    template <typename Impl>
    struct Model final : Concept
    {
        Impl impl_;

        Model(Impl impl)
            : impl_(std::move(impl))
        {
        }

        void advance() override
        {
            ++impl_;
        }

        void retreat() override
        {
            if constexpr (requires { --impl_; })
            {
                --impl_;
            }
            else
            {
                throw std::runtime_error("Error: Cannot decrement a forward-only iterator.");
            }
        }

        RefType deref() const override
        {
            return *impl_;
        }

        PtrType arrow() const override
        {
            return &*impl_;
        }

        bool equals(const Concept& other) const override
        {
            auto* p = dynamic_cast<const Model*>(&other);
            return p != nullptr && impl_ == p->impl_;
        }

        std::unique_ptr<Concept> clone() const override
        {
            return std::make_unique<Model>(impl_);
        }
    };

    std::unique_ptr<Concept> ptr_;

public:
    using iterator_category = Category;
    using iterator_concept = Category;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = PtrType;
    using reference = RefType;

    // Construct from a concrete iterator.
    template <typename Impl>
    BasicIterator(Impl impl)
        : ptr_(std::make_unique<Model<Impl>>(std::move(impl)))
    {
    }

    // Default constructor (end-like sentinel).
    BasicIterator() = default;

    // Copy.
    BasicIterator(const BasicIterator& that)
        : ptr_(that.ptr_ ? that.ptr_->clone() : nullptr)
    {
    }

    BasicIterator& operator=(const BasicIterator& that)
    {
        if (this != &that)
        {
            ptr_ = that.ptr_ ? that.ptr_->clone() : nullptr;
        }
        return *this;
    }

    // Move.
    BasicIterator(BasicIterator&&) = default;
    BasicIterator& operator=(BasicIterator&&) = default;

    /// Dereference.
    RefType operator*() const
    {
        return ptr_->deref();
    }

    /// Get pointer.
    PtrType operator->() const
    {
        return ptr_->arrow();
    }

    /// Check equality.
    bool operator==(const BasicIterator& that) const
    {
        if (ptr_ == nullptr && that.ptr_ == nullptr)
        {
            return true;
        }
        if (ptr_ == nullptr || that.ptr_ == nullptr)
        {
            return false;
        }
        return ptr_->equals(*that.ptr_);
    }

    /// Pre-increment.
    BasicIterator& operator++()
    {
        ptr_->advance();
        return *this;
    }

    /// Post-increment.
    BasicIterator operator++(int)
    {
        auto tmp = *this;
        ptr_->advance();
        return tmp;
    }

    /// Pre-decrement. Throws for forward-only iterators.
    BasicIterator& operator--()
    {
        ptr_->retreat();
        return *this;
    }

    /// Post-decrement. Throws for forward-only iterators.
    BasicIterator operator--(int)
    {
        auto tmp = *this;
        ptr_->retreat();
        return tmp;
    }
};

// Iterable base: provides const begin/end. T is the element type for BasicIterator.
template <typename T>
class ConstIterable : public Container
{
public:
    using Iterator = BasicIterator<T, true>;
    using ConstIterator = Iterator;

    virtual Iterator begin() const = 0;
    virtual Iterator end() const = 0;

    /// Return the type name for printing (e.g. "List", "Map").
    virtual const char* name() const = 0;

    /// Print the container.
    friend std::ostream& operator<<(std::ostream& os, const ConstIterable& container)
    {
        return print(os, container.begin(), container.end(), container.name());
    }
};

// Iterable base: adds mutable begin/end on top of ConstIterable.
template <typename T>
class Iterable : public ConstIterable<T>
{
public:
    using ConstIterable<T>::begin;
    using ConstIterable<T>::end;
    using Iterator = BasicIterator<T, false>;
    using ConstIterator = BasicIterator<T, true>;

    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;
};

} // namespace hellods::detail

#endif // CORE_HPP
