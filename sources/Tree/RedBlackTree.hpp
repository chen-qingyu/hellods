/**
 * @file RedBlackTree.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Red-black tree.
 * @date 2024.04.17
 *
 * @copyright Copyright (C) 2024
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
private:
    // Solve double red node.
    void solve_double_red(Node* current, Node* parent)
    {
        Node* uncle = nullptr;   // parent's sibling
        Node* grandpa = nullptr; // parent's parent

        while (true)
        {
            uncle = (parent->parent_ != nullptr) ? parent->sibling() : nullptr;
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

            // state 2:
        }
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
        : BinarySearchTree()
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
        // int old_size = size_;
        // insert_rbnode(root_, element);
        // return old_size != size_;
        return BinarySearchTree::insert(element);
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element)
    {
        // int old_size = size_;
        // remove_rbnode(root_, element);
        // return old_size != size_;
        return BinarySearchTree::remove(element);
    }
};

} // namespace hellods

#endif // REDBLACKTREE_HPP
