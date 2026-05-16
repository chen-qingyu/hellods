/**
 * @file SplayTree.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Splay tree (self-adjusting binary search tree).
 * @date 2026.05.05
 */

#ifndef SPLAYTREE_HPP
#define SPLAYTREE_HPP

#include "BinarySearchTree.hpp"

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
class SplayTree : public BinarySearchTree<T>
{
protected:
    using Node = typename BinarySearchTree<T>::Node;
    using BinarySearchTree<T>::size_;
    using BinarySearchTree<T>::end_;
    using BinarySearchTree<T>::root_;
    using BinarySearchTree<T>::set_root;
    using BinarySearchTree<T>::rotate_at;
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
                this->rotate_at(p, node_on_right);
            }
            else
            {
                bool p_on_right = p == g->right_;

                if (node_on_right == p_on_right)
                {
                    // Zig-Zig: node and parent are both left (or both right) children.
                    this->rotate_at(g, p_on_right);
                    this->rotate_at(p, node_on_right);
                }
                else
                {
                    // Zig-Zag: node and parent are in opposite directions.
                    this->rotate_at(p, node_on_right);
                    this->rotate_at(g, p_on_right);
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
            if (element < node->data())
            {
                node = node->left_;
            }
            else if (node->data() < element)
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
     * Lifecycle
     */

    /// Create an empty tree.
    SplayTree() = default;

    /// Create a tree based on the given initializer list.
    SplayTree(const std::initializer_list<T>& il)
        : BinarySearchTree<T>()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(*it);
        }
    }

    /// Copy constructor.
    SplayTree(const SplayTree& that)
        : BinarySearchTree<T>()
    {
        for (const auto& element : that)
        {
            insert(element);
        }
    }

    /// Move constructor.
    SplayTree(SplayTree&& that) = default;

    SplayTree& operator=(SplayTree that)
    {
        this->BinarySearchTree<T>::swap(that);
        return *this;
    }

    /*
     * Examination
     */

    /// Return an iterator to the specified element, or end() if the tree does
    /// not contain the element. The accessed element (or the last accessed node)
    /// is splayed to the root.
    Iterator find(const T& element)
    {
        if (root_ == nullptr)
        {
            return this->end();
        }

        Node* node = root_;
        Node* last = nullptr;

        while (node != nullptr)
        {
            last = node;
            if (element < node->data())
            {
                node = node->left_;
            }
            else if (node->data() < element)
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

        return this->end();
    }

    /// Determine whether an element is in the tree.
    /// The accessed element (or the last accessed node) is splayed to the root.
    bool contains(const T& element)
    {
        return find(element) != this->end();
    }

    /*
     * Manipulation
     */

    /// Insert the specified element in the tree. Return whether the element was newly inserted.
    bool insert(const T& element) override
    {
        if (root_ == nullptr)
        {
            set_root(new Node(element));
            size_++;
            return true;
        }

        // Splay the tree so that the root is either the element or
        // the last visited node on the search path.
        splay_find(element);

        // Duplicate check.
        if (root_->data() == element)
        {
            return false;
        }

        Node* new_node = new Node(element);
        size_++;

        if (element < root_->data())
        {
            // Split: new_node becomes the root, with root_ as its right child.
            new_node->link_left(root_->left_);
            root_->link_left(nullptr);
            new_node->link_right(root_);
            set_root(new_node);
        }
        else // element > root_->data()
        {
            // Split: new_node becomes the root, with root_ as its left child.
            new_node->link_right(root_->right_);
            root_->link_right(nullptr);
            new_node->link_left(root_);
            set_root(new_node);
        }

        return true;
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element) override
    {
        if (root_ == nullptr)
        {
            return false;
        }

        splay_find(element);

        // Element not found.
        if (!(root_->data() == element))
        {
            return false;
        }

        Node* to_delete = root_;

        if (root_->left_ == nullptr)
        {
            // Replace root with its right child.
            set_root(root_->right_);
            delete to_delete;
            size_--;
        }
        else if (root_->right_ == nullptr)
        {
            // Replace root with its left child.
            set_root(root_->left_);
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
            set_root(L);

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
