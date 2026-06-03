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

// Type-erased iterator.
template <typename T, bool Const, typename Category = std::bidirectional_iterator_tag>
class BasicIterator
{
public:
    using RefType = std::conditional_t<Const, const T&, T&>;
    using PtrType = std::conditional_t<Const, const T*, T*>;

    static constexpr bool is_fwd = std::is_same_v<Category, std::forward_iterator_tag>;
    static constexpr bool is_ra = std::is_same_v<Category, std::random_access_iterator_tag> ||
                                  std::is_same_v<Category, std::contiguous_iterator_tag>;

protected:
    struct Concept
    {
        virtual void inc() = 0;
        virtual void dec() = 0;
        virtual void advance(std::ptrdiff_t n) = 0;
        virtual std::ptrdiff_t distance(const Concept&) const = 0;
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

        void inc() override
        {
            ++impl_;
        }

        void dec() override
        {
            if constexpr (!is_fwd)
            {
                --impl_;
            }
        }

        void advance(std::ptrdiff_t n) override
        {
            if constexpr (is_ra)
            {
                impl_ += n;
            }
        }

        std::ptrdiff_t distance(const Concept& other) const override
        {
            if constexpr (is_ra)
            {
                auto& p = static_cast<const Model&>(other);
                return static_cast<std::ptrdiff_t>(impl_ - p.impl_);
            }
            return 0;
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

    /// Construct from a concrete iterator.
    template <typename Impl>
    BasicIterator(Impl impl)
        : ptr_(std::make_unique<Model<Impl>>(std::move(impl)))
    {
    }

    /// Default constructor (end-like sentinel).
    BasicIterator() = default;

    /// Copy.
    BasicIterator(const BasicIterator& that)
        : ptr_(that.ptr_ ? that.ptr_->clone() : nullptr)
    {
    }

    /// Copy assignment.
    BasicIterator& operator=(const BasicIterator& that)
    {
        if (this != &that)
        {
            ptr_ = that.ptr_ ? that.ptr_->clone() : nullptr;
        }
        return *this;
    }

    /// Move and move assignment.
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
        ptr_->inc();
        return *this;
    }

    /// Post-increment.
    BasicIterator operator++(int)
    {
        auto tmp = *this;
        ptr_->inc();
        return tmp;
    }

    /// Pre-decrement.
    BasicIterator& operator--()
        requires(!is_fwd)
    {
        ptr_->dec();
        return *this;
    }

    /// Post-decrement.
    BasicIterator operator--(int)
        requires(!is_fwd)
    {
        auto tmp = *this;
        ptr_->dec();
        return tmp;
    }

    /// Advance by n steps.
    BasicIterator& operator+=(std::ptrdiff_t n)
        requires(is_ra)
    {
        ptr_->advance(n);
        return *this;
    }

    /// Advance by n steps.
    BasicIterator operator+(std::ptrdiff_t n) const
        requires(is_ra)
    {
        auto tmp = *this;
        tmp += n;
        return tmp;
    }

    /// Retreat by n steps.
    BasicIterator& operator-=(std::ptrdiff_t n)
        requires(is_ra)
    {
        *this += -n;
        return *this;
    }

    /// Retreat by n steps.
    BasicIterator operator-(std::ptrdiff_t n) const
        requires(is_ra)
    {
        auto tmp = *this;
        tmp -= n;
        return tmp;
    }

    /// Random access.
    RefType operator[](std::ptrdiff_t n) const
        requires(is_ra)
    {
        return *(*this + n);
    }

    /// Distance between iterators.
    std::ptrdiff_t operator-(const BasicIterator& that) const
        requires(is_ra)
    {
        return ptr_->distance(*that.ptr_);
    }

    bool operator<(const BasicIterator& that) const
        requires(is_ra)
    {
        return *this - that < 0;
    }

    bool operator<=(const BasicIterator& that) const
        requires(is_ra)
    {
        return *this - that <= 0;
    }

    bool operator>(const BasicIterator& that) const
        requires(is_ra)
    {
        return *this - that > 0;
    }

    bool operator>=(const BasicIterator& that) const
        requires(is_ra)
    {
        return *this - that >= 0;
    }
};

// Iterable base: provides const begin/end. T is the element type for BasicIterator.
template <typename T, typename Cat = std::bidirectional_iterator_tag>
class ConstIterable : public Container
{
public:
    using Iterator = BasicIterator<T, true, Cat>;
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
template <typename T, typename Cat = std::bidirectional_iterator_tag>
class Iterable : public ConstIterable<T, Cat>
{
public:
    using ConstIterable<T, Cat>::begin;
    using ConstIterable<T, Cat>::end;
    using Iterator = BasicIterator<T, false, Cat>;
    using ConstIterator = BasicIterator<T, true, Cat>;

    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;
};

} // namespace hellods::detail

#endif // CORE_HPP
