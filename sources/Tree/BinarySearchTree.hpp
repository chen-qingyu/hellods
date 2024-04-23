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

#include "../Queue/ArrayQueue.hpp" // for traverse()

namespace hellods
{

/// Binary search tree.
template <typename T>
class BinarySearchTree : public common::Container
{
protected:
    // Tree node.
    struct Node
    {
        // Data stored in the node.
        T data_;

        // Pointer to the parent.
        Node* parent_;

        // Pointer to the left child.
        Node* left_;

        // Pointer to the right child.
        Node* right_;

        // Color of node, for red-black tree.
        bool red_;

        // Create a node with given element.
        Node(const T& data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, bool red = true)
            : data_(data)
            , parent_(parent)
            , left_(left)
            , right_(right)
            , red_(red)
        {
        }

        // Link left child.
        void link_left(Node* child)
        {
            left_ = child;
            if (child != nullptr)
            {
                child->parent_ = this;
            }
        }

        // Link right child.
        void link_right(Node* child)
        {
            right_ = child;
            if (child != nullptr)
            {
                child->parent_ = this;
            }
        }

        // Get the sibling node.
        Node* sibling() const
        {
            assert(parent_ != nullptr);
            return parent_->left_ == this ? parent_->right_ : parent_->left_;
        }
    };

public:
    /// Tree iterator class.
    ///
    /// Walk the tree in ascending order. This means that begin() is the smallest element.
    ///
    /// Because the internal elements of the tree have a fixed order,
    /// thus the iterator of the tree only supports access and does not support modification.
    class Iterator
    {
        friend class BinarySearchTree;

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = int;
        using pointer = value_type*;
        using reference = value_type&;

    private:
        // Current node pointer.
        Node* current_;

        // Constructor.
        Iterator(Node* current)
            : current_(current)
        {
        }

        // Iterator to next ascending node.
        void next()
        {
            if (current_->right_) // have right sub tree
            {
                current_ = current_->right_;
                while (current_->left_) // find min in right sub tree
                {
                    current_ = current_->left_;
                }
            }
            else // back to the next ascending node
            {
                // due to the presence of virtual maximum node, ensured current_->parent_ is not nullptr
                while (current_->parent_->right_ == current_)
                {
                    current_ = current_->parent_;
                }
                current_ = current_->parent_;
            }
        }

        // Iterator to previous ascending node.
        void previous()
        {
            if (current_->left_) // have left sub tree
            {
                current_ = current_->left_;
                while (current_->right_) // find max in left sub tree
                {
                    current_ = current_->right_;
                }
            }
            else // back to the previous ascending node
            {
                // due to the presence of virtual maximum node, ensured current_->parent_ is not nullptr
                while (current_->parent_->left_ == current_)
                {
                    current_ = current_->parent_;
                }
                current_ = current_->parent_;
            }
        }

    public:
        /**
         * @brief Dereference.
         *
         * @return reference of the data
         */
        const T& operator*() const
        {
            return current_->data_;
        }

        /**
         * @brief Get current pointer.
         *
         * @return current pointer
         */
        const T* operator->() const
        {
            return &current_->data_;
        }

        /**
         * @brief Check if two iterators are same.
         *
         * @param that another iterator
         * @return ture if two iterators are same, false otherwise.
         */
        bool operator==(const Iterator& that) const
        {
            return current_ == that.current_;
        }

        /**
         * @brief Check if two iterators are different.
         *
         * @param that another iterator
         * @return ture if two iterators are different, false otherwise.
         */
        bool operator!=(const Iterator& that) const
        {
            return !(*this == that);
        }

        /**
         * @brief Increment the iterator: ++it.
         *
         * @return reference of this iterator that point to next data
         */
        Iterator& operator++()
        {
            next();
            return *this;
        }

        /**
         * @brief Increment the iterator: it++.
         *
         * @return const reference of this iterator that point to current data
         */
        Iterator operator++(int)
        {
            auto tmp = *this;
            next();
            return tmp;
        }

        /**
         * @brief Decrement the iterator: --it.
         *
         * @return reference of this iterator that point to previous data
         */
        Iterator& operator--()
        {
            previous();
            return *this;
        }

        /**
         * @brief Decrement the iterator: it--.
         *
         * @return const reference of this iterator that point to current data
         */
        Iterator operator--(int)
        {
            auto tmp = *this;
            previous();
            return tmp;
        }
    };

protected:
    // Virtual maximum node.
    // In order for the iterator to move back from end, there must be a virtual maximum node.
    // And due to the presence of this node, can simplify the judgment of iterator movement, thereby improving the performance of iterator.
    Node* end_;

    // Pointer to the root.
    Node*& root_ = end_->left_;

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
    void traverse_node(Node* node, TraverseOption order, const F& action) const
    {
        if (node)
        {
            switch (order)
            {
                case PreOrder:
                {
                    action(node->data_);
                    traverse_node(node->left_, PreOrder, action);
                    traverse_node(node->right_, PreOrder, action);
                    break;
                }

                case InOrder:
                {
                    traverse_node(node->left_, InOrder, action);
                    action(node->data_);
                    traverse_node(node->right_, InOrder, action);
                    break;
                }

                case PostOrder:
                {
                    traverse_node(node->left_, PostOrder, action);
                    traverse_node(node->right_, PostOrder, action);
                    action(node->data_);
                    break;
                }

                case LevelOrder:
                {
                    ArrayQueue<Node*> queue;
                    queue.enqueue(node);
                    while (!queue.is_empty())
                    {
                        node = queue.dequeue();
                        action(node->data_);
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
                node->link_left(insert_node(node->left_, element));
            }
            else if (node->data_ < element)
            {
                node->link_right(insert_node(node->right_, element));
            }
        }

        return node;
    }

    // Find subtree minimum node.
    Node* find_min(Node* node) const
    {
        if (node)
        {
            while (node->left_)
            {
                node = node->left_;
            }
        }

        return node == nullptr ? end_ : node;
    }

    // Remove node recursively.
    Node* remove_node(Node* node, const T& element)
    {
        if (node)
        {
            if (element < node->data_)
            {
                node->link_left(remove_node(node->left_, element));
            }
            else if (node->data_ < element)
            {
                node->link_right(remove_node(node->right_, element));
            }
            else // element == node->data_
            {
                if (node->left_ && node->right_)
                {
                    Node* min = find_min(node->right_);
                    node->data_ = min->data_;
                    node->link_right(remove_node(node->right_, min->data_));
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

    // Return the maximum depth of the subtree rooted at the node.
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
        , end_(new Node(T()))
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
        destroy(end_);
    }

    /*
     * Comparison
     */

    /// Check whether two trees are equal.
    bool operator==(const BinarySearchTree& that) const
    {
        return size_ == that.size_ && std::equal(begin(), end(), that.begin());
    }

    /// Check whether two trees are not equal.
    bool operator!=(const BinarySearchTree& that) const
    {
        return !(*this == that);
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the tree.
    ///
    /// If the tree is empty, the returned iterator will be equal to end().
    Iterator begin() const
    {
        return Iterator(find_min(root_));
    }

    /// Return an iterator to the element following the last element of the tree.
    ///
    /// This element acts as a placeholder, attempting to access it results in undefined behavior.
    Iterator end() const
    {
        return Iterator(end_);
    }

    /*
     * Examination
     */

    /// Return the smallest element of the tree.
    T min() const
    {
        common::check_empty(size());
        return find_min(root_)->data_;
    }

    /// Return the largest element of the tree.
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

    /// Traverse option.
    enum TraverseOption
    {
        PreOrder,
        InOrder,
        PostOrder,
        LevelOrder
    };

    /// Traverse the tree.
    template <typename F>
    void traverse(TraverseOption order, const F& action) const
    {
        traverse_node(root_, order, action);
    }

    /// Return an iterator to the specified element, or end() if the tree does not contains the element.
    Iterator find(const T& element) const
    {
        Node* current = root_;
        while (current)
        {
            if (current->data_ < element)
            {
                current = current->right_;
            }
            else if (element < current->data_)
            {
                current = current->left_;
            }
            else
            {
                return Iterator(current);
            }
        }
        return end();
    }

    /// Determine whether an element is in the tree.
    bool contains(const T& element) const
    {
        return find(element) != end();
    }

    /// Return the maximum depth of the tree. Empty tree depth is 0.
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
        end_->link_left(insert_node(root_, element));
        return old_size != size_;
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element)
    {
        int old_size = size_;
        end_->link_left(remove_node(root_, element));
        return old_size != size_;
    }

    /// Remove all of the elements from the tree.
    void clear()
    {
        if (size_ != 0)
        {
            size_ = 0;
            destroy(root_);
            root_ = nullptr;
        }
    }

    /*
     * Print
     */

    /// Print the tree.
    friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree)
    {
        return common::print(os, tree, "Tree");
    }
};

} // namespace hellods

#endif // BINARYSEARCHTREE_HPP
