/**
 * @file TreeMap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Map implemented by tree.
 * @date 2026.05.05
 */

#ifndef TREEMAP_HPP
#define TREEMAP_HPP

#include "../Tree/RedBlackTree.hpp"
#include "Map.hpp"

namespace hellods
{

/// Map implemented by tree.
template <typename K, typename V, typename Tree = RedBlackTree<detail::MapEntry<K, V>>>
class TreeMap : public Map<K, V>
{
    Tree tree_;

    // Wraps the tree's const iterator to provide mutable access.
    class Iter : public Tree::Iterator
    {
        using Base = typename Tree::Iterator;

    public:
        explicit Iter(Base it)
            : Base(std::move(it))
        {
        }

        typename Map<K, V>::Entry& operator*() const
        {
            return const_cast<typename Map<K, V>::Entry&>(Base::operator*());
        }
    };

public:
    /*
     * Lifecycle
     */

    /// Create an empty map.
    TreeMap() = default;

    /// Create a map based on the given initializer list.
    TreeMap(const std::initializer_list<std::pair<const K, V>>& il)
        : tree_()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(it->first, it->second);
        }
    }

    TreeMap(const TreeMap&) = default;
    TreeMap(TreeMap&&) = default;

    TreeMap& operator=(const TreeMap&) = default;
    TreeMap& operator=(TreeMap&&) = default;

    /*
     * Comparison
     */

    /// Check whether two maps are equal.
    bool operator==(const TreeMap& that) const
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
    V& operator[](const K& key) override
    {
        auto tree_it = tree_.find(detail::MapEntry<K, V>{key});
        if (tree_it == tree_.end())
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }
        return const_cast<V&>(tree_it->value());
    }

    /// Return the const reference of value for key if key is in the map, else throw exception.
    const V& operator[](const K& key) const override
    {
        auto tree_it = tree_.find(detail::MapEntry<K, V>{key});
        if (tree_it == tree_.end())
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }
        return tree_it->value();
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the map.
    Map<K, V>::Iterator begin() override
    {
        return typename Map<K, V>::Iterator(Iter(tree_.begin()));
    }

    Map<K, V>::ConstIterator begin() const override
    {
        return tree_.begin();
    }

    /// Return an iterator to the element following the last element of the map.
    Map<K, V>::Iterator end() override
    {
        return typename Map<K, V>::Iterator(Iter(tree_.end()));
    }

    Map<K, V>::ConstIterator end() const override
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
    Map<K, V>::Iterator find(const K& key) override
    {
        return typename Map<K, V>::Iterator(Iter(tree_.find(detail::MapEntry<K, V>{key})));
    }

    /// Return a const iterator to the first occurrence of the specified key, or end() if the map does not contains the key.
    Map<K, V>::ConstIterator find(const K& key) const override
    {
        return tree_.find(detail::MapEntry<K, V>{key});
    }

    /// Determine whether a key is in the map.
    bool contains(const K& key) const override
    {
        return tree_.find(detail::MapEntry<K, V>{key}) != tree_.end();
    }

    /*
     * Manipulation
     */

    /// Insert a new key-value pair into the map. Return whether the pair was newly inserted.
    bool insert(const K& key, const V& value) override
    {
        return tree_.insert(detail::MapEntry<K, V>{key, value});
    }

    /// Remove the key-value pair corresponding to the key in the map. Return whether such a key was present.
    bool remove(const K& key) override
    {
        auto tree_it = tree_.find(detail::MapEntry<K, V>{key});
        if (tree_it == tree_.end())
        {
            return false;
        }
        return tree_.remove(*tree_it);
    }

    /// Remove all of the elements from the map.
    void clear() override
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
