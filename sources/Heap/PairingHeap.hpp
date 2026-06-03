/**
 * @file PairingHeap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Pairing heap implemented by multi-way tree.
 * @date 2026.06.01
 */

#ifndef PAIRINGHEAP_HPP
#define PAIRINGHEAP_HPP

#include "../List/ArrayList.hpp"
#include "Heap.hpp"

namespace hellods
{

/// Pairing heap implemented by multi-way tree. Default is max-heap.
template <typename T, typename Cmp = std::greater<T>>
class PairingHeap : public Heap<T>
{
protected:
    // Node of multi-way tree.
    struct Node
    {
        // Data stored in the node.
        T data_;

        // First child.
        Node* child_;

        // Next sibling.
        Node* sibling_;

        // Previous sibling or parent.
        Node* prev_;

        // Create a node with given element.
        Node(const T& data, Node* prev = nullptr)
            : data_(data)
            , child_(nullptr)
            , sibling_(nullptr)
            , prev_(prev)
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

        // Make b the first child of a.
        b->sibling_ = a->child_;
        b->prev_ = a;
        if (a->child_)
        {
            a->child_->prev_ = b;
        }
        a->child_ = b;

        return a;
    }

    // Two-pass pairing: meld siblings left-to-right then right-to-left.
    static Node* meld_siblings(Node* node)
    {
        if (node == nullptr || node->sibling_ == nullptr)
        {
            return node;
        }

        // Collect all siblings.
        ArrayList<Node*> nodes;
        while (node)
        {
            nodes.append(node);
            node = node->sibling_;
        }

        // First pass: pair left to right.
        ArrayList<Node*> paired;
        for (int i = 0; i < nodes.size(); i += 2)
        {
            if (i + 1 < nodes.size())
            {
                paired.append(meld(nodes[i], nodes[i + 1]));
            }
            else
            {
                paired.append(nodes[i]);
            }
        }

        // Second pass: meld right to left.
        Node* result = paired[paired.size() - 1];
        for (int i = paired.size() - 2; i >= 0; --i)
        {
            result = meld(paired[i], result);
        }

        return result;
    }

    // Deep copy a subtree.
    static Node* copy(Node* node, Node* prev = nullptr)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        Node* new_node = new Node(node->data_, prev);
        new_node->child_ = copy(node->child_, new_node);
        new_node->sibling_ = copy(node->sibling_, prev);
        return new_node;
    }

    // Destroy a subtree.
    static void destroy(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        destroy(node->child_);
        destroy(node->sibling_);
        delete node;
    }

    // Swap with another heap.
    void swap(PairingHeap& that)
    {
        std::swap(root_, that.root_);
        std::swap(size_, that.size_);
    }

public:
    /*
     * Lifecycle
     */

    /// Create an empty heap.
    PairingHeap()
        : root_(nullptr)
        , size_(0)
    {
    }

    /// Create a heap based on the given initializer list.
    PairingHeap(const std::initializer_list<T>& il)
        : PairingHeap()
    {
        for (const auto& elem : il)
        {
            push(elem);
        }
    }

    /// Copy constructor.
    PairingHeap(const PairingHeap& that)
        : root_(copy(that.root_))
        , size_(that.size_)
    {
    }

    /// Move constructor.
    PairingHeap(PairingHeap&& that)
        : PairingHeap()
    {
        swap(that);
    }

    PairingHeap& operator=(PairingHeap that)
    {
        swap(that);
        return *this;
    }

    /// Destroy the heap object.
    ~PairingHeap()
    {
        destroy(root_);
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
        root_ = meld_siblings(root_->child_);
        delete old_root;
        --size_;

        return element;
    }

    /// Merge another heap into this one. O(1) when both are PairingHeap of the same type.
    void meld(Heap<T>& that) override
    {
        if (size_ == 0 && that.size() == 0)
        {
            return;
        }

        // Fast path: same-type PairingHeap -> O(1) pointer meld.
        if (auto* p = dynamic_cast<PairingHeap*>(&that))
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

            // Iterative pre-order DFS.
            ArrayList<const Node*> stack;
            stack.append(root);

            while (stack.size() > 0)
            {
                const Node* current = stack.pop();
                data_->append(current->data_);

                // Push children from rightmost to leftmost so that leftmost is processed first.
                ArrayList<const Node*> children;
                for (const Node* child = current->child_; child; child = child->sibling_)
                {
                    children.append(child);
                }
                for (int i = children.size() - 1; i >= 0; --i)
                {
                    stack.append(children[i]);
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

#endif // PAIRINGHEAP_HPP
