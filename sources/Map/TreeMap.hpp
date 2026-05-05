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

/// Map implemented by tree.
template <typename K, detail::StoredElement V, typename Tree = RedBlackTree<detail::MapEntry<K, V>>>
    requires detail::OrderedElement<K>
class TreeMap : public detail::Container
{
    Tree tree_;

public:
    using Iterator = typename Tree::Iterator;
    using ConstIterator = Iterator;

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

        auto it = tree_.begin();
        auto that_it = that.tree_.begin();
        while (it != tree_.end())
        {
            if (it->key() != that_it->key() || it->value() != that_it->value())
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
        auto it = tree_.find(detail::MapEntry<K, V>{key, V()});
        if (it == tree_.end())
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }
        return const_cast<V&>(it->value());
    }

    /// Return the const reference of value for key if key is in the map, else throw exception.
    const V& operator[](const K& key) const
    {
        auto it = tree_.find(detail::MapEntry<K, V>{key, V()});
        if (it == tree_.end())
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }
        return it->value();
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the map.
    auto begin() const
    {
        return tree_.begin();
    }

    /// Return an iterator to the element following the last element of the map.
    auto end() const
    {
        return tree_.end();
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
        return tree_.find(detail::MapEntry<K, V>{key, V()});
    }

    Iterator find(const K& key) const
    {
        return tree_.find(detail::MapEntry<K, V>{key, V()});
    }

    /// Determine whether a key is in the map.
    bool contains(const K& key) const
    {
        return tree_.contains(detail::MapEntry<K, V>{key, V()});
    }

    /*
     * Manipulation
     */

    /// Insert a new key-value pair into the map. Return whether the pair was newly inserted.
    bool insert(const K& key, const V& value)
    {
        return tree_.insert(detail::MapEntry<K, V>{key, value});
    }

    /// Remove the key-value pair corresponding to the key in the map. Return whether such a key was present.
    bool remove(const K& key)
    {
        return tree_.remove(detail::MapEntry<K, V>{key, V()});
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
        return detail::print(os, map.tree_.begin(), map.tree_.end(), "Map");
    }
};

} // namespace hellods

#endif // TREEMAP_HPP
