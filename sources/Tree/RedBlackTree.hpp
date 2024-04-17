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
    // Red-black tree node.
    struct RBNode : public Node
    {
        int black_height_;

        bool is_red_;

        RBNode* parent_;

        // Create a node with given element.
        RBNode(const T& data, RBNode* parent = nullptr, RBNode* left = nullptr, RBNode* right = nullptr)
            : Node(data, left, right)
            , black_height_(0)
            , is_red_(false)
            , parent_(parent)
        {
        }

        bool is_root() const
        {
            return parent_ == nullptr;
        }

        bool is_left_child() const
        {
            return parent_ != nullptr && this == parent_->left_;
        }

        bool is_right_child() const
        {
            return parent_ != nullptr && this == parent_->right_;
        }

        bool is_leaf() const
        {
            return left_ == nullptr && right_ == nullptr;
        }

        bool has_parent() const
        {
            return parent_ != nullptr;
        }

        bool has_left_child() const
        {
            return left_ != nullptr;
        }

        bool has_right_child() const
        {
            return right_ != nullptr;
        }

        bool has_child() const
        {
            return has_left_child() || has_right_child();
        }

        bool has_both_child() const
        {
            return has_left_child() && has_right_child();
        }

        RBNode* sibling() const
        {
            return is_left_child() ? parent_->right_ : parent_->left_;
        }

        RBNode* uncle() const
        {
            return parent_->is_left_child() ? parent_->parent_->right_ : parent_->parent_->left;
        }

        RBNode* add_left_child(const T& e)
        {
            assert(left_ == nullptr);
            return static_cast<RBNode*>(left_ = new RBNode(e, this));
        }

        RBNode* add_right_child(const T& e)
        {
            assert(right_ == nullptr);
            return static_cast<RBNode*>(right_ = new RBNode(e, this));
        }
    };

    static bool is_black_node(RBNode* node)
    {
        return node == nullptr || !node->is_red_;
    }

    static bool is_red_node(RBNode* node)
    {
        return !is_black_node(node);
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
        // root_ = insert_node(root_, element);
        // return old_size != size_;
        RBNode node(element);
        node.add_left_child(T());
        return BinarySearchTree::insert(element);
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element)
    {
        // int old_size = size_;
        // root_ = remove_node(root_, element);
        // return old_size != size_;
        return BinarySearchTree::remove(element);
    }

    /*
     * Print
     */

    /// Print the tree.
    friend std::ostream& operator<<(std::ostream& os, const RedBlackTree& tree)
    {
        std::ostringstream oss;
        oss << static_cast<const BinarySearchTree&>(tree);
        return os << oss.str();
    }
};

} // namespace hellods

#endif // REDBLACKTREE_HPP
