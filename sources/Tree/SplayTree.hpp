/**
 * @file SplayTree.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Splay tree (self-adjusting binary search tree).
 * @date 2026.05.05
 */

#ifndef SPLAYTREE_HPP
#define SPLAYTREE_HPP

#include "RedBlackTree.hpp"

namespace hellods
{

/// Splay tree (self-adjusting binary search tree).
///
/// A splay tree is a binary search tree with the additional property that
/// recently accessed elements are quick to access again by splaying them
/// to the root of the tree. All operations (find, insert, remove) run in
/// O(log n) amortized time.
///
/// Unlike AVL or red-black trees, the splay tree stores no extra balancing
/// data and relies only on rotation during each access.
template <detail::OrderedElement T>
class SplayTree : public RedBlackTree<T>
{
protected:
    using Node = typename RedBlackTree<T>::Node;
    using RedBlackTree<T>::size_;
    using RedBlackTree<T>::end_;
    using RedBlackTree<T>::root_;
    using RedBlackTree<T>::slot;
    using RedBlackTree<T>::rotate_at;

    using typename BinarySearchTree<T>::Iterator;

    // Splay the given node to the root of the tree.
    void splay(Node* node)
    {
        while (node->parent_ != end_)
        {
            Node* p = node->parent_;
            Node* g = p->parent_;

            bool node_on_right = node == p->right_;

            if (g == end_)
            {
                // Zig: node's parent is the root.
                rotate_at(p, node_on_right);
            }
            else
            {
                bool p_on_right = p == g->right_;

                if (node_on_right == p_on_right)
                {
                    // Zig-Zig: node and parent are both left (or both right) children.
                    rotate_at(g, p_on_right);
                    rotate_at(p, node_on_right);
                }
                else
                {
                    // Zig-Zag: node and parent are in opposite directions.
                    rotate_at(p, node_on_right);
                    rotate_at(g, p_on_right);
                }
            }
        }
    }

    // Search for the element and splay the node containing it (or the last
    // accessed node if not found) to the root.
    void splay_find(const T& element)
    {
        Node* node = root_;
        Node* last = nullptr;

        while (node != nullptr)
        {
            last = node;
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
                splay(node);
                return;
            }
        }

        // Element not found; splay the last visited node if the tree is non-empty.
        if (last != nullptr)
        {
            splay(last);
        }
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty tree.
    SplayTree()
        : RedBlackTree<T>()
    {
    }

    /// Create a tree based on the given initializer list.
    SplayTree(const std::initializer_list<T>& il)
        : RedBlackTree<T>()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(*it);
        }
    }

    /// Copy constructor.
    SplayTree(const SplayTree& that)
        : RedBlackTree<T>()
    {
        for (const auto& element : that)
        {
            insert(element);
        }
    }

    /// Move constructor.
    SplayTree(SplayTree&& that) = default;

    SplayTree& operator=(const SplayTree&) = delete;
    SplayTree& operator=(SplayTree&&) = delete;

    /*
     * Examination
     */

    using BinarySearchTree<T>::end;

    /// Return an iterator to the specified element, or end() if the tree does
    /// not contain the element. The accessed element (or the last accessed node)
    /// is splayed to the root.
    Iterator find(const T& element)
    {
        if (root_ == nullptr)
        {
            return end();
        }

        Node* node = root_;
        Node* last = nullptr;

        while (node != nullptr)
        {
            last = node;
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
                splay(node);
                return this->make_iterator(root_);
            }
        }

        if (last != nullptr)
        {
            splay(last);
        }

        return end();
    }

    /// Determine whether an element is in the tree.
    /// The accessed element (or the last accessed node) is splayed to the root.
    bool contains(const T& element)
    {
        return find(element) != end();
    }

    /*
     * Manipulation
     */

    /// Insert the specified element in the tree. Return whether the element was newly inserted.
    bool insert(const T& element)
    {
        if (root_ == nullptr)
        {
            root_ = new Node(element);
            root_->parent_ = end_;
            size_++;
            return true;
        }

        // Splay the tree so that the root is either the element or
        // the last visited node on the search path.
        splay_find(element);

        // Duplicate check.
        if (root_->data_ == element)
        {
            return false;
        }

        Node* new_node = new Node(element);
        size_++;

        if (element < root_->data_)
        {
            // Split: new_node becomes the root, with root_ as its right child.
            new_node->link_left(root_->left_);
            root_->link_left(nullptr);
            new_node->link_right(root_);
            end_->link_left(new_node);
        }
        else // element > root_->data_
        {
            // Split: new_node becomes the root, with root_ as its left child.
            new_node->link_right(root_->right_);
            root_->link_right(nullptr);
            new_node->link_left(root_);
            end_->link_left(new_node);
        }

        return true;
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element)
    {
        if (root_ == nullptr)
        {
            return false;
        }

        splay_find(element);

        // Element not found.
        if (!(root_->data_ == element))
        {
            return false;
        }

        Node* to_delete = root_;

        if (root_->left_ == nullptr)
        {
            // Replace root with its right child.
            end_->link_left(root_->right_);
            delete to_delete;
            size_--;
        }
        else if (root_->right_ == nullptr)
        {
            // Replace root with its left child.
            end_->link_left(root_->left_);
            delete to_delete;
            size_--;
        }
        else
        {
            // Two children: replace root with the maximum element of the left subtree.
            Node* L = root_->left_;
            Node* R = root_->right_;

            delete to_delete;
            size_--;

            // Make L the new root.
            end_->link_left(L);

            // Find the maximum node in L and splay it to the root.
            Node* max = L;
            while (max->right_ != nullptr)
            {
                max = max->right_;
            }
            splay(max);

            // Attach R as the right child.
            max->link_right(R);
        }

        return true;
    }
};

} // namespace hellods

#endif // SPLAYTREE_HPP
