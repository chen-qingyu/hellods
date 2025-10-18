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
    class Iterator
    {
        friend class HashSet;

    protected:
        // Internal map iterator.
        HashMap<T, Dummy, Hash, Eq>::Iterator map_it_;

        // Constructor.
        Iterator(HashMap<T, Dummy, Hash, Eq>::Iterator it)
            : map_it_(it)
        {
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = int;
        using pointer = value_type*;
        using reference = value_type&;

        bool operator==(const Iterator& that) const
        {
            return map_it_ == that.map_it_;
        }

        const T& operator*() const
        {
            return map_it_->first;
        }

        const T* operator->() const
        {
            return &(map_it_->first);
        }

        Iterator& operator++()
        {
            ++map_it_;
            return *this;
        }

        Iterator operator++(int)
        {
            auto it = *this;
            ++*this;
            return it;
        }

        Iterator& operator--()
        {
            --map_it_;
            return *this;
        }

        Iterator operator--(int)
        {
            auto it = *this;
            --*this;
            return it;
        }
    };

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

    /// Copy constructor.
    HashSet(const HashSet& that)
        : map_(that.map_)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two sets are equal.
    bool operator==(const HashSet& that) const
    {
        if (map_.size_ != that.map_.size_)
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
    auto begin() const
    {
        return Iterator(map_.begin());
    }

    /// Return an iterator to the element following the last element of the set.
    auto end() const
    {
        return Iterator(map_.end());
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return map_.size_;
    }

    /// Return an iterator to the first occurrence of the specified item, or end() if the set does not contains the item.
    Iterator find(const T& item) const
    {
        return Iterator(map_.find(item));
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
