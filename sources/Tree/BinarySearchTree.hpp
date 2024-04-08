/**
 * @file BinarySearchTree.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Binary search tree.
 * @date 2022.01.29
 *
 * @copyright Copyright (C) 2022
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

#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "../common/Container.hpp"
#include "../common/utility.hpp"

#include <set> // for operator==()

#include "../Queue/ArrayQueue.hpp" // for traverse()

namespace hellods
{

/// Binary search tree.
template <typename T>
class BinarySearchTree : public common::Container
{
private:
    // Binary search tree node.
    struct Node
    {
        // Data stored in the node.
        T data_;

        // Pointer to the left child.
        Node* left_;

        // Pointer to the right child.
        Node* right_;

        // Create a node with given element.
        Node(const T& data, Node* left = nullptr, Node* right = nullptr)
            : data_(data)
            , left_(left)
            , right_(right)
        {
        }
    };

    // Pointer to the root.
    Node* root_;

    // Destroy the subtree rooted at that node recursively.
    void destroy(Node* node)
    {
        if (node)
        {
            destroy(node->left_);
            destroy(node->right_);
            delete node;
        }
    }

    enum TraverseOption;

    // Traverse the tree in specified order.
    template <typename F>
    void traverse_node(Node* node, TraverseOption order, const F& p_trav) const
    {
        if (node)
        {
            switch (order)
            {
                case PreOrder:
                {
                    p_trav(node->data_);
                    traverse_node(node->left_, PreOrder, p_trav);
                    traverse_node(node->right_, PreOrder, p_trav);
                    break;
                }

                case InOrder:
                {
                    traverse_node(node->left_, InOrder, p_trav);
                    p_trav(node->data_);
                    traverse_node(node->right_, InOrder, p_trav);
                    break;
                }

                case PostOrder:
                {
                    traverse_node(node->left_, PostOrder, p_trav);
                    traverse_node(node->right_, PostOrder, p_trav);
                    p_trav(node->data_);
                    break;
                }

                case LevelOrder:
                {
                    ArrayQueue<Node*> queue;
                    queue.enqueue(node);
                    while (!queue.is_empty())
                    {
                        node = queue.dequeue();
                        p_trav(node->data_);
                        if (node->left_)
                        {
                            queue.enqueue(node->left_);
                        }
                        if (node->right_)
                        {
                            queue.enqueue(node->right_);
                        }
                    }
                    break;
                }

                default:
                {
                    throw std::runtime_error("Error: Invalid order for traverse.");
                }
            }
        }
    }

    // Insert node recursively.
    Node* insert_node(Node* node, const T& element)
    {
        if (node == nullptr)
        {
            node = new Node(element);
            size_++;
        }
        else
        {
            if (element < node->data_)
            {
                node->left_ = insert_node(node->left_, element);
            }
            else if (element > node->data_)
            {
                node->right_ = insert_node(node->right_, element);
            }
        }

        return node;
    }

    // Find subtree minimum node.
    Node* find_min(Node* node) const
    {
        while (node->left_) // node is not null
        {
            node = node->left_;
        }
        return node;
    }

    // Remove node recursively.
    Node* remove_node(Node* node, const T& element)
    {
        if (node)
        {
            if (element < node->data_)
            {
                node->left_ = remove_node(node->left_, element);
            }
            else if (element > node->data_)
            {
                node->right_ = remove_node(node->right_, element);
            }
            else // element == node->data_
            {
                if (node->left_ && node->right_)
                {
                    Node* min = find_min(node->right_);
                    node->data_ = min->data_;
                    node->right_ = remove_node(node->right_, min->data_);
                }
                else
                {
                    Node* tmp = node;
                    node = node->left_ ? node->left_ : node->right_;
                    delete tmp;
                    size_--;
                }
            }
        }

        return node;
    }

    // Returns the maximum depth of the subtree rooted at the node.
    int depth_node(Node* node) const
    {
        return node == nullptr ? 0 : 1 + std::max(depth_node(node->left_), depth_node(node->right_));
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty tree.
    BinarySearchTree()
        : common::Container(0)
        , root_(nullptr)
    {
    }

    /// Create a tree based on the given initializer list.
    BinarySearchTree(const std::initializer_list<T>& il)
        : BinarySearchTree()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(*it);
        }
    }

    /// Destroy the tree object.
    ~BinarySearchTree()
    {
        destroy(root_);
    }

    /*
     * Comparison
     */

    /// Check whether two trees are equal.
    bool operator==(const BinarySearchTree& that) const
    {
        if (size_ != that.size_)
        {
            return false;
        }

        // count elements in each tree
        std::set<T> this_set, that_set;
        traverse_node(root_, InOrder, [&](const T& e)
                      { this_set.insert(e); });
        traverse_node(that.root_, InOrder, [&](const T& e)
                      { that_set.insert(e); });

        return this_set == that_set;
    }

    /// Check whether two trees are not equal.
    bool operator!=(const BinarySearchTree& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the smallest element of the tree
    T min() const
    {
        common::check_empty(size());
        return find_min(root_)->data_;
    }

    /// Return the largest element of the tree
    T max() const
    {
        common::check_empty(size());
        Node* current = root_;
        while (current->right_)
        {
            current = current->right_;
        }
        return current->data_;
    }

    /*
     * Examination
     */

    /// Traverse Option.
    enum TraverseOption
    {
        PreOrder,
        InOrder,
        PostOrder,
        LevelOrder
    };

    /// Traverse the tree.
    template <typename F>
    void traverse(TraverseOption order, const F& p_trav) const
    {
        traverse_node(root_, order, p_trav);
    }

    /// Determine whether an element is in the tree.
    bool contains(const T& element) const
    {
        Node* current = root_;
        while (current)
        {
            if (element > current->data_)
            {
                current = current->right_;
            }
            else if (element < current->data_)
            {
                current = current->left_;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    /// Find the maximum depth of the tree. Empty tree depth is 0.
    int depth() const
    {
        return depth_node(root_);
    }

    /*
     * Manipulation
     */

    /// Insert the specified element in the tree. Return whether the element was newly inserted.
    bool insert(const T& element)
    {
        int old_size = size_;
        root_ = insert_node(root_, element);
        return old_size != size_;
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element)
    {
        int old_size = size_;
        root_ = remove_node(root_, element);
        return old_size != size_;
    }

    /// Remove all of the elements from the tree.
    BinarySearchTree& clear()
    {
        if (size_ != 0)
        {
            size_ = 0;
            destroy(root_);
            root_ = nullptr;
        }

        return *this;
    }

    /*
     * Print
     */

    /// Print the tree.
    friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree)
    {
        os << "Tree(";
        tree.traverse_node(tree.root_, LevelOrder, [&](const T& e)
                           { os << (tree.root_->data_ == e ? "" : ", ") << e; });
        return os << ")";
    }
};

} // namespace hellods

#endif // BINARYSEARCHTREE_HPP
