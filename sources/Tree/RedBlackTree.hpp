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
template <detail::OrderedElement T>
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

    // Return the reference slot that points to the subtree root.
    Node*& slot(Node* node)
    {
        if (node->parent_ == end_)
        {
            return root_;
        }
        return node->parent_->left_ == node ? node->parent_->left_ : node->parent_->right_;
    }

    // Return the left or right child of the node.
    Node* child(Node* node, bool on_left) const
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        return on_left ? node->left_ : node->right_;
    }

    // Set the node color to black if the node exists.
    void set_black(Node* node)
    {
        if (node != nullptr)
        {
            node->red_ = false;
        }
    }

    // Rotate the subtree rooted at current in the given direction.
    void rotate_at(Node* current, bool to_left)
    {
        Node*& current_slot = slot(current);
        if (to_left)
        {
            rotate_left(current_slot);
        }
        else
        {
            rotate_right(current_slot);
        }
    }

    // Replace the subtree rooted at old_node with new_node.
    void replace_node(Node* old_node, Node* new_node)
    {
        slot(old_node) = new_node;
        if (new_node != nullptr)
        {
            new_node->parent_ = old_node->parent_;
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
        while (true)
        {
            Node* grandpa = current->parent_->parent_;

            // if grandpa is end_, break
            if (grandpa == end_)
            {
                break;
            }

            Node* uncle = parent->sibling();

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
            bool parent_on_left = parent == grandpa->left_;
            Node*& grandpa_slot = slot(grandpa);

            if (current != child(parent, parent_on_left))
            {
                rotate_at(child(grandpa, parent_on_left), parent_on_left);
            }

            if (parent_on_left)
            {
                rotate_right(grandpa);
                grandpa->right_->red_ = true;
            }
            else
            {
                rotate_left(grandpa);
                grandpa->left_->red_ = true;
            }

            grandpa->red_ = false;
            grandpa_slot = grandpa;
            break;
        } // end while(true)
    }

    // Find the node containing the specified element.
    Node* find_node(const T& element) const
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
                return node;
            }
        }
        return nullptr;
    }

    // Insert node for red-black tree.
    bool insert_rbnode(Node*& node, const T& element)
    {
        Node* current = node; // from root_
        Node* parent = end_;  // root_'s parent is end_

        // find the position for insert
        while (current != nullptr)
        {
            // if already has the element, do nothing
            if (element == current->data_)
            {
                return false;
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
            return true;
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
            return true;
        }

        // now, the level >= 3 (root is level 1), and parent is red, double red
        solve_double_red(current, parent);

        // root is black
        root_->red_ = false;
        return true;
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

            bool current_on_left = current == parent->left_;
            Node* sibling = child(parent, !current_on_left);
            Node* near_nephew = child(sibling, current_on_left);
            Node* far_nephew = child(sibling, !current_on_left);

            if (is_red(sibling))
            {
                sibling->red_ = false;
                parent->red_ = true;
                rotate_at(parent, current_on_left);
                sibling = child(parent, !current_on_left);
                near_nephew = child(sibling, current_on_left);
                far_nephew = child(sibling, !current_on_left);
            }

            if (is_black(near_nephew) && is_black(far_nephew))
            {
                if (sibling != nullptr)
                {
                    sibling->red_ = true;
                }
                current = parent;
                parent = current->parent_;
                continue;
            }

            if (is_black(far_nephew))
            {
                if (sibling != nullptr)
                {
                    set_black(near_nephew);
                    sibling->red_ = true;
                    rotate_at(sibling, !current_on_left);
                }
                sibling = child(parent, !current_on_left);
                far_nephew = child(sibling, !current_on_left);
            }

            sibling->red_ = parent->red_;
            parent->red_ = false;
            set_black(far_nephew);
            rotate_at(parent, current_on_left);
            current = root_;
        }

        set_black(current);
    }

    // Remove node for red-black tree.
    bool remove_rbnode(const T& element)
    {
        Node* node = find_node(element);

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

    /// Copy constructor.
    RedBlackTree(const RedBlackTree& that)
        : RedBlackTree()
    {
        for (const auto& element : that)
        {
            insert(element);
        }
    }

    RedBlackTree(RedBlackTree&&) = default;

    RedBlackTree& operator=(const RedBlackTree&) = delete;
    RedBlackTree& operator=(RedBlackTree&&) = delete;

    /*
     * Manipulation
     */

    /// Insert the specified element in the tree. Return whether the element was newly inserted.
    bool insert(const T& element)
    {
        return insert_rbnode(root_, element);
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element)
    {
        return remove_rbnode(element);
    }
};

} // namespace hellods

#endif // REDBLACKTREE_HPP
