/**
 * @file Tree.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract tree interface.
 * @date 2026.05.10
 */

#ifndef TREE_HPP
#define TREE_HPP

#include "../detail.hpp"

namespace hellods
{

/// Abstract tree interface.
template <detail::OrderedElement T>
class Tree : public detail::Container
{
public:
    /// Traverse option.
    enum TraverseOption
    {
        PreOrder,
        InOrder,
        PostOrder,
        LevelOrder
    };

    /// Iterator type — const access only (tree order must not be modified).
    using Iterator = detail::BasicIterator<T, true, std::bidirectional_iterator_tag>;
    using ConstIterator = Iterator;

    /*
     * Lifecycle
     */

    /// Virtual destructor.
    virtual ~Tree() = default;

    /*
     * Iterator
     */

    /// Return a const iterator to the first element of the tree.
    virtual Iterator begin() const = 0;

    /// Return a const iterator to the element following the last element of the tree.
    virtual Iterator end() const = 0;

    /*
     * Examination
     */

    /// Return the minimum element in the tree.
    virtual T min() const = 0;

    /// Return the maximum element in the tree.
    virtual T max() const = 0;

    /// Return the depth of the tree.
    virtual int depth() const = 0;

    /// Return an iterator to the first occurrence of the specified element, or end() if the tree does not contain the element.
    virtual Iterator find(const T& element) const = 0;

    /// Check if the tree contains the specified element.
    bool contains(const T& element) const
        requires detail::LinearElement<T>
    {
        return find(element) != end();
    }

    /*
     * Manipulation
     */

    /// Insert the specified element into the tree. Return true if the tree changed as a result.
    virtual bool insert(const T& element) = 0;

    /// Remove the specified element from the tree. Return true if the tree changed as a result.
    virtual bool remove(const T& element) = 0;

    /// Remove all of the elements from the tree.
    virtual void clear() = 0;
};

} // namespace hellods

#endif // TREE_HPP
