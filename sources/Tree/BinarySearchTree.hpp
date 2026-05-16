/**
 * @file BinarySearchTree.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Binary search tree.
 * @date 2022.01.29
 */

#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "Tree.hpp"

#include "../Queue/ArrayQueue.hpp" // for traverse()

namespace hellods
{

/// Binary search tree.
template <typename T>
class BinarySearchTree : public Tree<T>
{
protected:
    // Tree node.
    struct Node
    {
        // Data stored in the node.
        std::optional<T> data_;

        // Pointer to the parent.
        Node* parent_;

        // Pointer to the left child.
        Node* left_;

        // Pointer to the right child.
        Node* right_;

        // Color of node, for red-black tree.
        bool red_;

        // Height of node, for AVL tree (leaf height = 1).
        int height_;

        // Create a sentinel node without stored data.
        Node()
            : data_(std::nullopt)
            , parent_(nullptr)
            , left_(nullptr)
            , right_(nullptr)
            , red_(false)
            , height_(0)
        {
        }

        // Create a node with given element.
        Node(const T& data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, bool red = true, int height = 1)
            : data_(data)
            , parent_(parent)
            , left_(left)
            , right_(right)
            , red_(red)
            , height_(height)
        {
        }

        T& data()
        {
            return *data_;
        }

        const T& data() const
        {
            return *data_;
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
    class Iter
    {
        friend class BinarySearchTree;

    protected:
        // Current node pointer.
        Node* current_;

        // Constructor.
        Iter(Node* current)
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
        /// Dereference.
        const T& operator*() const
        {
            return current_->data();
        }

        /// Check if two iterators are same.
        bool operator==(const Iter& that) const
        {
            return current_ == that.current_;
        }

        /// Increment the iterator.
        Iter& operator++()
        {
            next();
            return *this;
        }

        /// Decrement the iterator.
        Iter& operator--()
        {
            previous();
            return *this;
        }
    };

protected:
    // Number of elements.
    int size_;

    // Virtual maximum node.
    // In order for the iterator to move back from end, there must be a virtual maximum node.
    // And due to the presence of this node, can simplify the judgment of iterator movement, thereby improving the performance of iterator.
    Node* end_;

    // Pointer to the root.
    Node* root_;

    // Replace the root node.
    void set_root(Node* node)
    {
        root_ = node;
        end_->left_ = node;
        if (node != nullptr)
        {
            node->parent_ = end_;
        }
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
        set_root(root_);
    }

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

    // Traverse the tree in specified order.
    void traverse_node(Node* node, typename Tree<T>::TraverseOption order, const std::function<void(const T&)>& action) const
    {
        if (node)
        {
            switch (order)
            {
                case Tree<T>::PreOrder:
                {
                    action(node->data());
                    traverse_node(node->left_, Tree<T>::PreOrder, action);
                    traverse_node(node->right_, Tree<T>::PreOrder, action);
                    break;
                }

                case Tree<T>::InOrder:
                {
                    traverse_node(node->left_, Tree<T>::InOrder, action);
                    action(node->data());
                    traverse_node(node->right_, Tree<T>::InOrder, action);
                    break;
                }

                case Tree<T>::PostOrder:
                {
                    traverse_node(node->left_, Tree<T>::PostOrder, action);
                    traverse_node(node->right_, Tree<T>::PostOrder, action);
                    action(node->data());
                    break;
                }

                case Tree<T>::LevelOrder:
                {
                    ArrayQueue<Node*> queue;
                    queue.enqueue(node);
                    while (!queue.is_empty())
                    {
                        node = queue.dequeue();
                        action(node->data());
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
            if (element < node->data())
            {
                node->link_left(insert_node(node->left_, element));
            }
            else if (node->data() < element)
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
            if (element < node->data())
            {
                node->link_left(remove_node(node->left_, element));
            }
            else if (node->data() < element)
            {
                node->link_right(remove_node(node->right_, element));
            }
            else // element == node->data()
            {
                if (node->left_ && node->right_)
                {
                    Node* min = find_min(node->right_);
                    node->data() = min->data();
                    node->link_right(remove_node(node->right_, min->data()));
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

    // Construct an iterator pointing to the given node.
    typename Tree<T>::Iterator make_iterator(Node* node) const
    {
        return typename Tree<T>::Iterator(Iter(node));
    }

    // Swap with another tree.
    void swap(BinarySearchTree& that)
    {
        std::swap(size_, that.size_);
        std::swap(root_, that.root_);
        set_root(root_);
        that.set_root(that.root_);
    }

public:
    /*
     * Lifecycle
     */

    /// Create an empty tree.
    BinarySearchTree()
        : size_(0)
        , end_(new Node())
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

    /// Copy constructor.
    BinarySearchTree(const BinarySearchTree& that)
        : BinarySearchTree()
    {
        for (const auto& element : that)
        {
            insert(element);
        }
    }

    /// Move constructor.
    BinarySearchTree(BinarySearchTree&& that)
        : BinarySearchTree()
    {
        size_ = that.size_;
        set_root(that.root_);

        that.size_ = 0;
        that.set_root(nullptr);
    }

    BinarySearchTree& operator=(BinarySearchTree that)
    {
        swap(that);
        return *this;
    }

    /// Destroy the tree object.
    ~BinarySearchTree()
    {
        destroy(root_);
        delete end_;
    }

    /*
     * Comparison
     */

    /// Check whether two trees are equal.
    bool operator==(const BinarySearchTree& that) const
    {
        return size_ == that.size_ && std::equal(begin(), end(), that.begin());
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the tree.
    ///
    /// If the tree is empty, the returned iterator will be equal to end().
    typename Tree<T>::Iterator begin() const override
    {
        return typename Tree<T>::Iterator(Iter(find_min(root_)));
    }

    /// Return an iterator to the element following the last element of the tree.
    ///
    /// This element acts as a placeholder, attempting to access it results in undefined behavior.
    typename Tree<T>::Iterator end() const override
    {
        return typename Tree<T>::Iterator(Iter(end_));
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return size_;
    }

    /// Return the smallest element of the tree.
    T min() const override
    {
        detail::check_empty(size_);
        return find_min(root_)->data();
    }

    /// Return the largest element of the tree.
    T max() const override
    {
        detail::check_empty(size_);
        Node* current = root_;
        while (current->right_)
        {
            current = current->right_;
        }
        return current->data();
    }

    /// Traverse the tree.
    void traverse(typename Tree<T>::TraverseOption order, const std::function<void(const T&)>& action) const override
    {
        traverse_node(root_, order, action);
    }

    /// Return an iterator to the specified element, or end() if the tree does not contain the element.
    typename Tree<T>::Iterator find(const T& element) const override
    {
        Node* current = root_;
        while (current)
        {
            if (current->data() < element)
            {
                current = current->right_;
            }
            else if (element < current->data())
            {
                current = current->left_;
            }
            else
            {
                return make_iterator(current);
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
    int depth() const override
    {
        return depth_node(root_);
    }

    /*
     * Manipulation
     */

    /// Insert the specified element in the tree. Return whether the element was newly inserted.
    bool insert(const T& element) override
    {
        int old_size = size_;
        set_root(insert_node(root_, element));
        return old_size != size_;
    }

    /// Remove the specified element from the tree. Return whether such an element was present.
    bool remove(const T& element) override
    {
        int old_size = size_;
        set_root(remove_node(root_, element));
        return old_size != size_;
    }

    /// Remove all of the elements from the tree.
    void clear() override
    {
        if (size_ != 0)
        {
            size_ = 0;
            destroy(root_);
            set_root(nullptr);
        }
    }

    /*
     * Print
     */

    /// Print the tree.
    friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree)
    {
        return detail::print(os, tree.begin(), tree.end(), "Tree");
    }
};

} // namespace hellods

#endif // BINARYSEARCHTREE_HPP
