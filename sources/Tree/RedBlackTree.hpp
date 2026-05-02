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

protected:
    using BinarySearchTree<T>::find_min;

    // Check whether the node is red.
    bool is_red(Node* node) const
    {
        return node != nullptr && node->red_;
    }

    // Check whether the node is black.
    bool is_black(Node* node) const
    {
        return !is_red(node);
    }

    // Replace the subtree rooted at old_node with new_node.
    void replace_node(Node* old_node, Node* new_node)
    {
        if (old_node->parent_ == end_)
        {
            end_->link_left(new_node);
        }
        else if (old_node->parent_->left_ == old_node)
        {
            old_node->parent_->link_left(new_node);
        }
        else
        {
            old_node->parent_->link_right(new_node);
        }
    }

    // Rotate the subtree rooted at current to the left.
    void rotate_left_at(Node* current)
    {
        if (current->parent_ == end_)
        {
            rotate_left(root_);
        }
        else if (current->parent_->left_ == current)
        {
            rotate_left(current->parent_->left_);
        }
        else
        {
            rotate_left(current->parent_->right_);
        }
    }

    // Rotate the subtree rooted at current to the right.
    void rotate_right_at(Node* current)
    {
        if (current->parent_ == end_)
        {
            rotate_right(root_);
        }
        else if (current->parent_->left_ == current)
        {
            rotate_right(current->parent_->left_);
        }
        else
        {
            rotate_right(current->parent_->right_);
        }
    }

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
                    rotate_left(grandpa->left_);
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
                    rotate_right(grandpa->right_);
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

    // Solve double black node caused by deletion.
    void solve_double_black(Node* current, Node* parent)
    {
        while (current != root_ && is_black(current))
        {
            if (parent == end_)
            {
                break;
            }

            if (current == parent->left_)
            {
                Node* sibling = parent->right_;

                if (is_red(sibling))
                {
                    sibling->red_ = false;
                    parent->red_ = true;
                    rotate_left_at(parent);
                    sibling = parent->right_;
                }

                if (is_black(sibling == nullptr ? nullptr : sibling->left_) &&
                    is_black(sibling == nullptr ? nullptr : sibling->right_))
                {
                    if (sibling != nullptr)
                    {
                        sibling->red_ = true;
                    }
                    current = parent;
                    parent = current->parent_;
                }
                else
                {
                    if (is_black(sibling == nullptr ? nullptr : sibling->right_))
                    {
                        if (sibling != nullptr)
                        {
                            if (sibling->left_ != nullptr)
                            {
                                sibling->left_->red_ = false;
                            }
                            sibling->red_ = true;
                            rotate_right_at(sibling);
                        }
                        sibling = parent->right_;
                    }

                    sibling->red_ = parent->red_;
                    parent->red_ = false;
                    if (sibling->right_ != nullptr)
                    {
                        sibling->right_->red_ = false;
                    }
                    rotate_left_at(parent);
                    current = root_;
                }
            }
            else
            {
                Node* sibling = parent->left_;

                if (is_red(sibling))
                {
                    sibling->red_ = false;
                    parent->red_ = true;
                    rotate_right_at(parent);
                    sibling = parent->left_;
                }

                if (is_black(sibling == nullptr ? nullptr : sibling->left_) &&
                    is_black(sibling == nullptr ? nullptr : sibling->right_))
                {
                    if (sibling != nullptr)
                    {
                        sibling->red_ = true;
                    }
                    current = parent;
                    parent = current->parent_;
                }
                else
                {
                    if (is_black(sibling == nullptr ? nullptr : sibling->left_))
                    {
                        if (sibling != nullptr)
                        {
                            if (sibling->right_ != nullptr)
                            {
                                sibling->right_->red_ = false;
                            }
                            sibling->red_ = true;
                            rotate_left_at(sibling);
                        }
                        sibling = parent->left_;
                    }

                    sibling->red_ = parent->red_;
                    parent->red_ = false;
                    if (sibling->left_ != nullptr)
                    {
                        sibling->left_->red_ = false;
                    }
                    rotate_right_at(parent);
                    current = root_;
                }
            }
        }

        if (current != nullptr)
        {
            current->red_ = false;
        }
    }

    // Remove node for red-black tree.
    bool remove_rbnode(const T& element)
    {
        Node* node = root_;
        while (node != nullptr)
        {
            if (element < node->data_)
            {
                node = node->left_;
            }
            else if (node->data_ < element)
            {
                node = node->right_;
            }
            else
            {
                break;
            }
        }

        if (node == nullptr)
        {
            return false;
        }

        Node* removed = node;
        bool removed_red = removed->red_;
        Node* current = nullptr;
        Node* parent = end_;

        if (node->left_ == nullptr)
        {
            current = node->right_;
            parent = node->parent_;
            replace_node(node, node->right_);
        }
        else if (node->right_ == nullptr)
        {
            current = node->left_;
            parent = node->parent_;
            replace_node(node, node->left_);
        }
        else
        {
            removed = find_min(node->right_);
            removed_red = removed->red_;
            current = removed->right_;

            if (removed->parent_ == node)
            {
                parent = removed;
            }
            else
            {
                parent = removed->parent_;
                replace_node(removed, removed->right_);
                removed->link_right(node->right_);
            }

            replace_node(node, removed);
            removed->link_left(node->left_);
            removed->red_ = node->red_;
        }

        delete node;
        size_--;

        if (size_ == 0)
        {
            root_ = nullptr;
            return true;
        }

        if (removed_red == false)
        {
            solve_double_black(current, parent);
        }

        root_->red_ = false;
        return true;
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
        return remove_rbnode(element);
    }
};

} // namespace hellods

#endif // REDBLACKTREE_HPP
