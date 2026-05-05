/**
 * @file TreeMap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Map implemented by tree.
 * @date 2026.05.05
 */

#ifndef TREEMAP_HPP
#define TREEMAP_HPP

#include "../Tree/RedBlackTree.hpp"

namespace hellods
{

namespace detail
{

/// Internal key-value entry for tree map.
/// Only compares by key, so the tree orders entries by key alone.
template <typename K, typename V>
struct TreeMapEntry
{
    K first;
    V second;

    bool operator<(const TreeMapEntry& rhs) const
    {
        return first < rhs.first;
    }

    bool operator==(const TreeMapEntry& rhs) const
    {
        return first == rhs.first;
    }
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const TreeMapEntry<K, V>& entry)
{
    return os << entry.first << ": " << entry.second;
}

} // namespace detail

/// Map implemented by tree.
template <typename K, detail::StoredElement V, typename Tree = RedBlackTree<detail::TreeMapEntry<K, V>>>
    requires detail::OrderedElement<K>
class TreeMap : public detail::Container
{
    Tree tree_;

public:
    /// Map iterator class.
    ///
    /// Walk the map in ascending key order.
    ///
    /// Because the internal keys of the map have a fixed order,
    /// thus the iterator of the map does not support modification for key.
    class Iterator
    {
        friend class TreeMap;

    protected:
        using TreeIter = typename Tree::Iterator;

        TreeIter it_;

        // Proxy for operator* that provides pair-like access by reference.
        struct PairRef
        {
            const K& first;
            const V& second;

            bool operator==(const std::pair<const K, V>& rhs) const
            {
                return first == rhs.first && second == rhs.second;
            }
        };

        friend std::ostream& operator<<(std::ostream& os, const PairRef& pair)
        {
            return os << pair.first << ": " << pair.second;
        }

        // Proxy for operator-> that enables `it->first` returning const K&.
        struct ArrowProxy
        {
            std::pair<const K, V> data_;

            const std::pair<const K, V>* operator->() const
            {
                return &data_;
            }
        };

        Iterator(TreeIter it)
            : it_(it)
        {
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::pair<const K, V>;
        using difference_type = int;

        /// Dereference.
        PairRef operator*() const
        {
            return {it_->first, it_->second};
        }

        /// Get pointer for arrow access.
        ArrowProxy operator->() const
        {
            return {{it_->first, it_->second}};
        }

        /// Check if two iterators are same.
        bool operator==(const Iterator& that) const
        {
            return it_ == that.it_;
        }

        /// Increment the iterator: ++it.
        Iterator& operator++()
        {
            ++it_;
            return *this;
        }

        /// Increment the iterator: it++.
        Iterator operator++(int)
        {
            auto it = *this;
            ++it_;
            return it;
        }

        /// Decrement the iterator: --it.
        Iterator& operator--()
        {
            --it_;
            return *this;
        }

        /// Decrement the iterator: it--.
        Iterator operator--(int)
        {
            auto it = *this;
            --it_;
            return it;
        }
    };

    using ConstIterator = Iterator;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty map.
    TreeMap()
        : tree_()
    {
    }

    /// Create a map based on the given initializer list.
    TreeMap(const std::initializer_list<std::pair<const K, V>>& il)
        : tree_()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(it->first, it->second);
        }
    }

    /// Copy constructor.
    TreeMap(const TreeMap& that)
        : tree_(that.tree_)
    {
    }

    /// Move constructor.
    TreeMap(TreeMap&& that) = default;

    TreeMap& operator=(const TreeMap&) = delete;
    TreeMap& operator=(TreeMap&&) = delete;

    /*
     * Comparison
     */

    /// Check whether two maps are equal.
    bool operator==(const TreeMap& that) const
        requires detail::LinearElement<V>
    {
        if (tree_.size() != that.tree_.size())
        {
            return false;
        }

        // Both trees store entries in key order; compare in parallel.
        auto it = tree_.begin();
        auto that_it = that.tree_.begin();
        while (it != tree_.end())
        {
            if (it->first != that_it->first || it->second != that_it->second)
            {
                return false;
            }
            ++it;
            ++that_it;
        }

        return true;
    }

    /*
     * Access
     */

    /// Return the reference of value for key if key is in the map, else throw exception.
    V& operator[](const K& key)
    {
        auto it = tree_.find(detail::TreeMapEntry<K, V>{key, V()});
        if (it == tree_.end())
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }
        // The tree stores mutable data; only the iterator provides const access.
        return const_cast<V&>(it->second);
    }

    /// Return the const reference of value for key if key is in the map, else throw exception.
    const V& operator[](const K& key) const
    {
        auto it = tree_.find(detail::TreeMapEntry<K, V>{key, V()});
        if (it == tree_.end())
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }
        return it->second;
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the map.
    auto begin()
    {
        return Iterator(tree_.begin());
    }

    auto begin() const
    {
        return Iterator(tree_.begin());
    }

    /// Return an iterator to the element following the last element of the map.
    auto end()
    {
        return Iterator(tree_.end());
    }

    auto end() const
    {
        return Iterator(tree_.end());
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return tree_.size();
    }

    /// Return an iterator to the first occurrence of the specified key, or end() if the map does not contains the key.
    Iterator find(const K& key)
    {
        return Iterator(tree_.find(detail::TreeMapEntry<K, V>{key, V()}));
    }

    Iterator find(const K& key) const
    {
        return Iterator(tree_.find(detail::TreeMapEntry<K, V>{key, V()}));
    }

    /// Determine whether a key is in the map.
    bool contains(const K& key) const
    {
        return tree_.contains(detail::TreeMapEntry<K, V>{key, V()});
    }

    /*
     * Manipulation
     */

    /// Insert a new key-value pair into the map. Return whether the pair was newly inserted.
    bool insert(const K& key, const V& value)
    {
        return tree_.insert(detail::TreeMapEntry<K, V>{key, value});
    }

    /// Remove the key-value pair corresponding to the key in the map. Return whether such a key was present.
    bool remove(const K& key)
    {
        return tree_.remove(detail::TreeMapEntry<K, V>{key, V()});
    }

    /// Remove all of the elements from the map.
    void clear()
    {
        tree_.clear();
    }

    /*
     * Print
     */

    /// Print the map.
    friend std::ostream& operator<<(std::ostream& os, const TreeMap& map)
    {
        // Use the tree's iterator directly for printing, since PairRef
        // is not a full input_iterator (it proxies std::pair<const K, V>&).
        return detail::print(os, map.tree_.begin(), map.tree_.end(), "Map");
    }
};

} // namespace hellods

#endif // TREEMAP_HPP
