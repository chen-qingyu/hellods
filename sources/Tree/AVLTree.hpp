/**
 * @file AVLTree.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief AVL tree (self-balancing binary search tree).
 * @date 2026.05.05
 */

#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "BinarySearchTree.hpp"

namespace hellods
{

/// AVL tree (self-balancing binary search tree).
///
/// In AVL trees, the heights of the two child subtrees of any node
/// differ by at most one; if at any time they differ by more than one,
/// rebalancing is performed to restore this property.
template <detail::OrderedElement T>
class AVLTree : public BinarySearchTree<T>
{
protected:
    using Node = typename BinarySearchTree<T>::Node;
    using BinarySearchTree<T>::size_;
    using BinarySearchTree<T>::end_;
    using BinarySearchTree<T>::root_;
    using BinarySearchTree<T>::find_min;

    // Return the height of the node (nullptr has height 0).
    int height(const Node* node) const
    {
        return node == nullptr ? 0 : node->height_;
    }

    // Return the balance factor of the node.
    int balance_factor(const Node* node) const
    {
        return height(node->left_) - height(node->right_);
    }

    // Update the height of the node based on its children.
    void update_height(Node* node)
    {
        node->height_ = 1 + std::max(height(node->left_), height(node->right_));
    }

    // Rotate right.
    /*
            y          x
           / \        / \
          x   C  =>  A   y
         / \            / \
        A   B          B   C
    */
    Node* rotate_right(Node* y)
    {
        Node* x = y->left_;
        Node* B = x->right_;

        y->link_left(B);
        x->link_right(y);

        update_height(y);
        update_height(x);

        return x;
    }

    // Rotate left.
    /*
        x                y
       / \              / \
      A   y     =>     x   C
         / \          / \
        B   C        A   B
    */
    Node* rotate_left(Node* x)
    {
        Node* y = x->right_;
        Node* B = y->left_;

        x->link_right(B);
        y->link_left(x);

        update_height(x);
        update_height(y);

        return y;
    }

    // Rebalance the subtree rooted at the node.
    // Return the new root of the subtree after rebalancing.
    Node* rebalance(Node* node)
    {
        update_height(node);

        int bf = balance_factor(node);

        // Left heavy
        if (bf > 1)
        {
            if (balance_factor(node->left_) < 0) // LR case
            {
                node->link_left(rotate_left(node->left_));
            }
            // LL case (including after LR adjustment)
            return rotate_right(node);
        }

        // Right heavy
        if (bf < -1)
        {
            if (balance_factor(node->right_) > 0) // RL case
            {
                node->link_right(rotate_right(node->right_));
            }
            // RR case (including after RL adjustment)
            return rotate_left(node);
        }

        // Already balanced
        return node;
    }

    // Insert node recursively, maintaining AVL balance.
    Node* insert_avlnode(Node* node, const T& element)
    {
        if (node == nullptr)
        {
            node = new Node(element);
            size_++;
        }
        else if (element < node->data_)
        {
            node->link_left(insert_avlnode(node->left_, element));
        }
        else if (node->data_ < element)
        {
            node->link_right(insert_avlnode(node->right_, element));
        }
        // else duplicate, do nothing

        return rebalance(node);
    }

    // Remove the minimum node from the subtree rooted at node.
    // Return the new root of the subtree.
    Node* remove_min(Node* node)
    {
        if (node->left_ == nullptr)
        {
            Node* right = node->right_;
            delete node;
            size_--;
            return right;
        }

        node->link_left(remove_min(node->left_));
        return rebalance(node);
    }

    // Remove node recursively, maintaining AVL balance.
    Node* remove_avlnode(Node* node, const T& element)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (element < node->data_)
        {
            node->link_left(remove_avlnode(node->left_, element));
        }
        else if (node->data_ < element)
        {
            node->link_right(remove_avlnode(node->right_, element));
        }
        else // element == node->data_, found the node to remove
        {
            if (node->left_ == nullptr)
            {
                Node* right = node->right_;
                delete node;
                size_--;
                return right;
            }

            if (node->right_ == nullptr)
            {
                Node* left = node->left_;
                delete node;
                size_--;
                return left;
            }

            // Two children: replace with successor (minimum of right subtree)
            Node* min = find_min(node->right_);
            node->data_ = min->data_;
            node->link_right(remove_avlnode(node->right_, min->data_));
        }

        return rebalance(node);
    }

public:
    /*
     * Lifecycle
     */

    /// Create an empty tree.
    AVLTree()
        : BinarySearchTree<T>()
    {
    }

    /// Create a tree based on the given initializer list.
    AVLTree(const std::initializer_list<T>& il)
        : BinarySearchTree<T>()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(*it);
        }
    }

    /// Copy constructor.
    AVLTree(const AVLTree& that)
        : BinarySearchTree<T>()
    {
        for (const auto& element : that)
        {
            insert(element);
        }
    }

    /// Move constructor.
    AVLTree(AVLTree&& that) = default;

    AVLTree& operator=(AVLTree that)
    {
        this->BinarySearchTree<T>::swap(that);
        return *this;
    }

    /*
     * Manipulation
     */

    /// Insert the specified element in the tree. Return whether the element was newly inserted.
    bool insert(const T& element)
    {
        int old_size = size_;
        end_->link_left(insert_avlnode(root_, element));
        return old_size != size_;
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element)
    {
        int old_size = size_;
        end_->link_left(remove_avlnode(root_, element));
        return old_size != size_;
    }
};

} // namespace hellods

#endif // AVLTREE_HPP
