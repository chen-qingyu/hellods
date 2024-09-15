/**
 * @file RedBlackTree.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Red-black tree.
 * @date 2024.04.17
 */

#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include "BinarySearchTree.hpp"

namespace hellods
{

/// Red-black tree.
template <typename T>
class RedBlackTree : public BinarySearchTree<T>
{
    using BinarySearchTree<T>::Node;
    using BinarySearchTree<T>::size_;
    using BinarySearchTree<T>::end_;
    using BinarySearchTree<T>::root_;

private:
    // Rotate right.
    void rotate_right(Node*& current)
    {
        /*
               6       ->        4
              / \               / \
             4   7             3   6
            / \                   / \
           3   5                 5   7
        */

        Node* tmproot = current;             // -> 6
        current = tmproot->left_;            // -> 4
        current->parent_ = tmproot->parent_; // 4'p = 6'p
        tmproot->link_left(current->right_); // 6'l = 5
        current->link_right(tmproot);        // 4'r = 6
    }

    // Rotate left.
    void rotate_left(Node*& current)
    {
        /*
             4       ->        6
            / \               / \
           3   6             4   7
              / \           / \
             5   7         3   5
        */

        Node* tmproot = current;             // -> 4
        current = tmproot->right_;           // -> 6
        current->parent_ = tmproot->parent_; // 6'p = 4'p
        tmproot->link_right(current->left_); // 4'r = 5
        current->link_left(tmproot);         // 6'l = 4
    }

    // Solve double red node.
    void solve_double_red(Node* current, Node* parent)
    {
        Node* uncle = nullptr;   // parent's sibling
        Node* grandpa = nullptr; // parent's parent

        while (true)
        {
            uncle = (parent->parent_ != end_) ? parent->sibling() : nullptr;
            grandpa = current->parent_->parent_;

            // if grandpa is end_, break
            if (grandpa == end_)
            {
                break;
            }

            // state 1: if uncle is red
            if (uncle != nullptr && uncle->red_)
            {
                // 1. change color
                parent->red_ = false;
                uncle->red_ = false;
                grandpa->red_ = true;

                // 2. if grandpa is the root, break
                if (grandpa == root_)
                {
                    break;
                }

                // 3. up up, until there is no double red
                current = grandpa;
                parent = current->parent_;
                if (parent->red_ == false)
                {
                    break;
                }

                continue;
            }

            // state 2: if uncle is black or null
            Node* fff = grandpa->parent_;
            int flag = 0; // 0 means grandpa is end_, 1 is left child, 2 is right child
            if (fff != end_)
            {
                flag = fff->left_ == grandpa ? 1 : 2;
            }
            if (parent == grandpa->left_)
            {
                if (current == parent->left_)
                {
                    rotate_right(grandpa);
                }
                else // current is right child
                {
                    rotate_left(parent);
                    rotate_right(grandpa);
                }

                // change color
                grandpa->red_ = false;
                grandpa->right_->red_ = true;
            }
            else // parent is right child
            {
                if (parent->right_ == current)
                {
                    rotate_left(grandpa);
                }
                else
                {
                    rotate_right(parent);
                    rotate_left(grandpa);
                }

                // change color
                grandpa->red_ = false;
                grandpa->left_->red_ = true;
            }

            // update root
            if (flag == 0)
            {
                end_->link_left(grandpa);
            }
            else if (flag == 1)
            {
                fff->link_left(grandpa);
            }
            else if (flag == 2)
            {
                fff->link_right(grandpa);
            }
            break;
        } // end while(true)
    }

    // Insert node for red-black tree.
    void insert_rbnode(Node*& node, const T& element)
    {
        Node* current = node; // from root_
        Node* parent = end_;  // root_'s parent is end_

        // find the position for insert
        while (current != nullptr)
        {
            // if already has the element, do nothing
            if (element == current->data_)
            {
                return;
            }

            parent = current;
            current = current->data_ < element ? current->right_ : current->left_;
        }

        // current is nullptr now, here is the position to insert
        current = new Node(element);
        size_++;

        // if current is root, ok
        if (parent == end_)
        {
            current->red_ = false;
            end_->link_left(current);
            return;
        }

        // current is not root
        if (parent->data_ < element)
        {
            parent->link_right(current);
        }
        else
        {
            parent->link_left(current);
        }

        // if parent is black, ok (current is red)
        if (parent->red_ == false)
        {
            return;
        }

        // now, the level >= 3 (root is level 1), and parent is red, double red
        solve_double_red(current, parent);

        // root is black
        root_->red_ = false;
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty tree.
    RedBlackTree()
        : BinarySearchTree<T>()
    {
    }

    /// Create a tree based on the given initializer list.
    RedBlackTree(const std::initializer_list<T>& il)
        : RedBlackTree()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(*it);
        }
    }

    /*
     * Manipulation
     */

    /// Insert the specified element in the tree. Return whether the element was newly inserted.
    bool insert(const T& element)
    {
        int old_size = size_;
        insert_rbnode(root_, element);
        return old_size != size_;
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element)
    {
        // int old_size = size_;
        // remove_rbnode(root_, element);
        // return old_size != size_;
        return BinarySearchTree<T>::remove(element);
    }
};

} // namespace hellods

#endif // REDBLACKTREE_HPP
