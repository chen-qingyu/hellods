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
template <typename T>
class Tree : public detail::ConstIterable<T>
{
public:
    using typename detail::ConstIterable<T>::Iterator;

    /// Traverse option.
    enum TraverseOption
    {
        PreOrder,
        InOrder,
        PostOrder,
        LevelOrder
    };

    /*
     * Lifecycle
     */

    /// Virtual destructor.
    ~Tree() override = default;

    /*
     * Examination
     */

    /// Return the minimum element in the tree.
    virtual T min() const = 0;

    /// Return the maximum element in the tree.
    virtual T max() const = 0;

    /// Return the depth of the tree.
    virtual int depth() const = 0;

    /// Traverse the tree in the specified order.
    virtual void traverse(TraverseOption order, const std::function<void(const T&)>& action) const = 0;

    /// Return an iterator to the first occurrence of the specified element, or end() if the tree does not contain the element.
    virtual Iterator find(const T& element) const = 0;

    /// Check if the tree contains the specified element.
    virtual bool contains(const T& element) const
    {
        return find(element) != this->end();
    }

    /*
     * Manipulation
     */

    /// Insert the specified element into the tree. Return true if the tree changed as a result.
    virtual bool insert(const T& element) = 0;

    /// Remove the specified element from the tree. Return true if the tree changed as a result.
    virtual bool remove(const T& element) = 0;
};

} // namespace hellods

#endif // TREE_HPP
