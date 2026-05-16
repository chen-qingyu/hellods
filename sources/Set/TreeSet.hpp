/**
 * @file TreeSet.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Set implemented by tree.
 * @date 2026.05.05
 */

#ifndef TREESET_HPP
#define TREESET_HPP

#include "../Tree/RedBlackTree.hpp"
#include "Set.hpp"

namespace hellods
{

/// Set implemented by tree.
template <typename T, typename Tree = RedBlackTree<T>>
class TreeSet : public Set<T>
{
    Tree tree_;

public:
    /*
     * Lifecycle
     */

    /// Create an empty set.
    TreeSet() = default;

    /// Create a set based on the given initializer list.
    TreeSet(const std::initializer_list<T>& il)
        : tree_()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(*it);
        }
    }

    TreeSet(const TreeSet&) = default;
    TreeSet(TreeSet&&) = default;

    TreeSet& operator=(const TreeSet&) = default;
    TreeSet& operator=(TreeSet&&) = default;

    /*
     * Comparison
     */

    /// Check whether two sets are equal.
    bool operator==(const TreeSet& that) const
    {
        return tree_ == that.tree_;
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the set.
    typename Set<T>::Iterator begin() const override
    {
        return tree_.begin();
    }

    /// Return an iterator to the element following the last element of the set.
    typename Set<T>::Iterator end() const override
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

    /// Return an iterator to the first occurrence of the specified item, or end() if the set does not contains the item.
    Set<T>::Iterator find(const T& item) const override
    {
        return tree_.find(item);
    }

    /// Determine whether a item is in the set.
    bool contains(const T& item) const override
    {
        return tree_.contains(item);
    }

    /*
     * Manipulation
     */

    /// Insert a new item into the set. Return whether the item was newly inserted.
    bool insert(const T& item) override
    {
        return tree_.insert(item);
    }

    /// Remove the item corresponding to the item in the set. Return whether such a item was present.
    bool remove(const T& item) override
    {
        return tree_.remove(item);
    }

    /// Remove all of the elements from the set.
    void clear() override
    {
        tree_.clear();
    }

    /*
     * Print
     */

    /// Print the set.
    friend std::ostream& operator<<(std::ostream& os, const TreeSet& set)
    {
        return detail::print(os, set.begin(), set.end(), "Set");
    }
};

} // namespace hellods

#endif // TREESET_HPP
