/**
 * @file HashSet.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Hash set.
 * @date 2024.09.15
 */

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include "../Map/HashMap.hpp"
#include "Set.hpp"

namespace hellods
{

/// Hash set.
template <typename T, typename Hash = std::hash<T>, typename Eq = std::equal_to<T>>
    requires detail::HashKey<T, Hash, Eq>
class HashSet : public Set<T>
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
    class Iter
    {
        friend class HashSet;

    protected:
        using MapIterator = typename HashMap<T, Dummy, Hash, Eq>::ConstIterator;

        MapIterator map_it_;

        // Constructor.
        Iter(MapIterator it)
            : map_it_(it)
        {
        }

    public:
        const T& operator*() const
        {
            return map_it_->key();
        }

        bool operator==(const Iter& that) const
        {
            return map_it_ == that.map_it_;
        }

        Iter& operator++()
        {
            ++map_it_;
            return *this;
        }

        Iter& operator--()
        {
            --map_it_;
            return *this;
        }
    };

public:
    /*
     * Lifecycle
     */

    /// Create an empty set.
    HashSet() = default;

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

    HashSet& operator=(const HashSet&) = default;
    HashSet& operator=(HashSet&&) = default;

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
    Set<T>::Iterator begin() const override
    {
        return typename Set<T>::Iterator(Iter(map_.begin()));
    }

    /// Return an iterator to the element following the last element of the set.
    Set<T>::Iterator end() const override
    {
        return typename Set<T>::Iterator(Iter(map_.end()));
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
    Set<T>::Iterator find(const T& item) const override
    {
        return typename Set<T>::Iterator(Iter(map_.find(item)));
    }

    /// Determine whether a item is in the set.
    bool contains(const T& item) const override
    {
        return map_.contains(item);
    }

    /*
     * Manipulation
     */

    /// Insert a new item into the set. Return whether the item was newly inserted.
    bool insert(const T& item) override
    {
        return map_.insert(item, Dummy());
    }

    /// Remove the item corresponding to the item in the set. Return whether such a item was present.
    bool remove(const T& item) override
    {
        return map_.remove(item);
    }

    /// Remove all of the elements from the set.
    void clear() override
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
