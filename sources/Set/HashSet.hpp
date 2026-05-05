/**
 * @file HashSet.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Hash set.
 * @date 2024.09.15
 */

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include "../Map/HashMap.hpp"

namespace hellods
{

/// Hash set.
template <typename T, typename Hash = std::hash<T>, typename Eq = std::equal_to<T>>
    requires detail::HashKey<T, Hash, Eq>
class HashSet : public detail::Container
{
protected:
    // Dummy value type for internal map.
    struct Dummy
    {
    };

    // Internal map that stores actual data.
    HashMap<T, Dummy, Hash, Eq> map_;

public:
    /// Set iterator class.
    ///
    /// Walk the set in random order.
    ///
    /// Because the internal items of the set have a fixed position,
    /// thus the iterator of the set does not support modification for item.
    template <bool Const>
    class BasicIterator
    {
        friend class HashSet;

    protected:
        using MapIterator = std::conditional_t<Const,
                                               typename HashMap<T, Dummy, Hash, Eq>::ConstIterator,
                                               typename HashMap<T, Dummy, Hash, Eq>::Iterator>;

        MapIterator map_it_;

        // Constructor.
        BasicIterator(MapIterator it)
            : map_it_(it)
        {
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = int;
        using pointer = const value_type*;
        using reference = const value_type&;

        bool operator==(const BasicIterator& that) const
        {
            return map_it_ == that.map_it_;
        }

        const T& operator*() const
        {
            return map_it_->key();
        }

        const T* operator->() const
        {
            return &(map_it_->key());
        }

        BasicIterator& operator++()
        {
            ++map_it_;
            return *this;
        }

        BasicIterator operator++(int)
        {
            auto it = *this;
            ++*this;
            return it;
        }

        BasicIterator& operator--()
        {
            --map_it_;
            return *this;
        }

        BasicIterator operator--(int)
        {
            auto it = *this;
            --*this;
            return it;
        }
    };

    using Iterator = BasicIterator<false>;
    using ConstIterator = BasicIterator<true>;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty set.
    HashSet()
        : map_()
    {
    }

    /// Create a set based on the given initializer list.
    HashSet(const std::initializer_list<T>& il)
        : HashSet()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(*it);
        }
    }

    HashSet(const HashSet&) = default;
    HashSet(HashSet&&) = default;

    HashSet& operator=(const HashSet&) = delete;
    HashSet& operator=(HashSet&&) = delete;

    /*
     * Comparison
     */

    /// Check whether two sets are equal.
    bool operator==(const HashSet& that) const
    {
        if (map_.size() != that.map_.size())
        {
            return false;
        }

        for (const auto& item : that)
        {
            if (!contains(item))
            {
                return false;
            }
        }

        return true;
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the set.
    auto begin()
    {
        return Iterator(map_.begin());
    }

    auto begin() const
    {
        return ConstIterator(map_.begin());
    }

    /// Return an iterator to the element following the last element of the set.
    auto end()
    {
        return Iterator(map_.end());
    }

    auto end() const
    {
        return ConstIterator(map_.end());
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return map_.size();
    }

    /// Return an iterator to the first occurrence of the specified item, or end() if the set does not contains the item.
    Iterator find(const T& item)
    {
        return Iterator(map_.find(item));
    }

    ConstIterator find(const T& item) const
    {
        return ConstIterator(map_.find(item));
    }

    /// Determine whether a item is in the set.
    bool contains(const T& item) const
    {
        return map_.contains(item);
    }

    /*
     * Manipulation
     */

    /// Insert a new item into the set. Return whether the item was newly inserted.
    bool insert(const T& item)
    {
        return map_.insert(item, Dummy());
    }

    /// Remove the item corresponding to the item in the set. Return whether such a item was present.
    bool remove(const T& item)
    {
        return map_.remove(item);
    }

    /// Remove all of the elements from the set.
    void clear()
    {
        map_.clear();
    }

    /*
     * Print
     */

    /// Print the set.
    friend std::ostream& operator<<(std::ostream& os, const HashSet& set)
    {
        return detail::print(os, set.begin(), set.end(), "Set");
    }
};

} // namespace hellods

#endif // HASHSET_HPP
