/**
 * @file SkewHeap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Skew heap (self-adjusting heap) implemented by binary tree.
 * @date 2026.06.03
 */

#ifndef SKEWHEAP_HPP
#define SKEWHEAP_HPP

#include "Heap.hpp"

namespace hellods
{

/// Skew heap (self-adjusting heap) implemented by binary tree. Default is max-heap.
///
/// A skew heap is a self-adjusting variant of a leftist heap that stores no
/// rank information. After every meld, the left and right children are
/// unconditionally swapped, keeping the tree roughly balanced amortized.
/// All operations run in O(log N) amortized time.
template <typename T, typename Cmp = std::greater<T>>
class SkewHeap : public Heap<T>
{
protected:
    // Node of binary tree.
    struct Node
    {
        // Data stored in the node.
        T data_;

        // Left child.
        Node* left_;

        // Right child.
        Node* right_;

        // Create a node with given element.
        Node(const T& data, Node* left = nullptr, Node* right = nullptr)
            : data_(data)
            , left_(left)
            , right_(right)
        {
        }
    };

    using Heap<T>::MAX_CAPACITY;

    // Root node.
    Node* root_;

    // Number of elements.
    int size_;

    // Meld two heaps into one.
    static Node* meld(Node* a, Node* b)
    {
        if (a == nullptr)
        {
            return b;
        }
        if (b == nullptr)
        {
            return a;
        }

        // Ensure a has higher priority (is the root).
        if (!Cmp()(a->data_, b->data_))
        {
            std::swap(a, b);
        }

        // Unconditionally swap left and right children (self-adjusting).
        std::swap(a->left_, a->right_);

        // Meld the former right (now left) child with b.
        a->left_ = meld(a->left_, b);

        return a;
    }

    // Deep copy a subtree.
    static Node* copy(Node* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        return new Node(node->data_, copy(node->left_), copy(node->right_));
    }

    // Destroy a subtree.
    static void destroy(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        destroy(node->left_);
        destroy(node->right_);
        delete node;
    }

    // Swap with another heap.
    void swap(SkewHeap& that)
    {
        std::swap(root_, that.root_);
        std::swap(size_, that.size_);
    }

public:
    /*
     * Lifecycle
     */

    /// Create an empty heap.
    SkewHeap()
        : root_(nullptr)
        , size_(0)
    {
    }

    /// Create a heap based on the given initializer list.
    SkewHeap(const std::initializer_list<T>& il)
        : SkewHeap()
    {
        for (const auto& elem : il)
        {
            push(elem);
        }
    }

    /// Copy constructor.
    SkewHeap(const SkewHeap& that)
        : root_(copy(that.root_))
        , size_(that.size_)
    {
    }

    /// Move constructor.
    SkewHeap(SkewHeap&& that)
        : SkewHeap()
    {
        swap(that);
    }

    SkewHeap& operator=(SkewHeap that)
    {
        swap(that);
        return *this;
    }

    /// Destroy the heap object.
    ~SkewHeap()
    {
        destroy(root_);
    }

    /*
     * Comparison
     */

    /// Check whether two heaps are equal.
    bool operator==(const SkewHeap& that) const
    {
        return size_ == that.size_ && std::equal(begin(), end(), that.begin());
    }

    /*
     * Access
     */

    /// Peek the top element in the heap.
    const T& peek() const override
    {
        detail::check_empty(size_);
        return root_->data_;
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return size_;
    }

    /*
     * Manipulation
     */

    /// Push an element onto the heap.
    void push(const T& element) override
    {
        detail::check_full(size_, MAX_CAPACITY);

        root_ = meld(root_, new Node(element));
        ++size_;
    }

    /// Remove the top element from the heap and return it.
    T pop() override
    {
        detail::check_empty(size_);

        T element = std::move(root_->data_);

        Node* old_root = root_;
        root_ = meld(root_->left_, root_->right_);
        delete old_root;
        --size_;

        return element;
    }

    /// Merge another heap into this one. O(log N) amortized.
    void meld(Heap<T>& that) override
    {
        if (size_ == 0 && that.size() == 0)
        {
            return;
        }

        // Fast path: same-type SkewHeap -> direct pointer meld.
        if (auto* p = dynamic_cast<SkewHeap*>(&that))
        {
            if (this == p)
            {
                return;
            }

            detail::check_full(size_ + p->size_, MAX_CAPACITY);

            root_ = meld(root_, p->root_);
            size_ += p->size_;

            p->root_ = nullptr;
            p->size_ = 0;
            return;
        }

        // Generic fallback.
        Heap<T>::meld(that);
    }

    /// Remove all of the elements from the heap.
    void clear() override
    {
        destroy(root_);
        root_ = nullptr;
        size_ = 0;
    }

    /*
     * Iterator
     */

    struct CacheIter
    {
        std::shared_ptr<ArrayList<T>> data_;
        int index_;

        CacheIter(const Node* root)
            : data_(std::make_shared<ArrayList<T>>())
            , index_(0)
        {
            if (root == nullptr)
            {
                return;
            }

            ArrayList<const Node*> stack;
            stack.append(root);

            while (stack.size() > 0)
            {
                const Node* current = stack.pop();
                data_->append(current->data_);

                // Push right first so left is processed first.
                if (current->right_)
                {
                    stack.append(current->right_);
                }
                if (current->left_)
                {
                    stack.append(current->left_);
                }
            }

            std::sort(data_->begin(), data_->end(), Cmp{});
        }

        CacheIter(int size)
            : data_(nullptr)
            , index_(size)
        {
        }

        const T& operator*() const
        {
            return (*data_)[index_];
        }

        bool operator==(const CacheIter& that) const
        {
            return index_ == that.index_;
        }

        CacheIter& operator++()
        {
            ++index_;
            return *this;
        }

        CacheIter& operator--()
        {
            --index_;
            return *this;
        }
    };

    /// Return an iterator to the first element of the heap.
    typename Heap<T>::Iterator begin() const override
    {
        return typename Heap<T>::Iterator(CacheIter(root_));
    }

    /// Return an iterator to the element following the last element of the heap.
    typename Heap<T>::Iterator end() const override
    {
        return typename Heap<T>::Iterator(CacheIter(size_));
    }
};

} // namespace hellods

#endif // SKEWHEAP_HPP
