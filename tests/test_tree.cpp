#include "tool.hpp"

#include "../sources/Tree/AVLTree.hpp"
#include "../sources/Tree/BinarySearchTree.hpp"
#include "../sources/Tree/RedBlackTree.hpp"

using namespace hellods;

// Verify in-order traversal produces an ascending sequence.
template <typename Tree>
static bool verify_order(const Tree& tree)
{
    auto it = tree.begin();
    if (it == tree.end())
    {
        return true;
    }
    int previous = *it;
    int count = 1;
    for (++it; it != tree.end(); ++it)
    {
        if (!(previous < *it))
        {
            return false;
        }
        previous = *it;
        count++;
    }
    return count == tree.size();
}

class InspectableRedBlackTree : public RedBlackTree<int>
{
    using Node = typename BinarySearchTree<int>::Node;
    using BinarySearchTree<int>::end_;
    using BinarySearchTree<int>::root_;

    bool verify_node(Node* node, int black_count, int& black_height) const
    {
        if (node == nullptr)
        {
            black_count++;
            if (black_height == -1)
            {
                black_height = black_count;
            }
            return black_count == black_height;
        }

        // No double red: a red node cannot have a red child.
        if (node->red_ && ((node->left_ && node->left_->red_) || (node->right_ && node->right_->red_)))
        {
            return false;
        }

        return verify_node(node->left_, black_count + (node->red_ ? 0 : 1), black_height) &&
               verify_node(node->right_, black_count + (node->red_ ? 0 : 1), black_height);
    }

public:
    using RedBlackTree<int>::RedBlackTree;

    bool verify_invariants() const
    {
        if (root_ == nullptr)
        {
            return true;
        }
        if (root_->parent_ != end_ || root_->red_)
        {
            return false;
        }

        int black_height = -1;
        return verify_node(root_, 0, black_height) && verify_order(*this);
    }
};

class InspectableAVLTree : public AVLTree<int>
{
    using Node = typename BinarySearchTree<int>::Node;
    using BinarySearchTree<int>::end_;
    using BinarySearchTree<int>::root_;

    bool verify_balance(Node* node) const
    {
        if (node == nullptr)
        {
            return true;
        }

        int left_h = node->left_ ? node->left_->height_ : 0;
        int right_h = node->right_ ? node->right_->height_ : 0;

        if (node->height_ != 1 + std::max(left_h, right_h) || std::abs(left_h - right_h) > 1)
        {
            return false;
        }

        return verify_balance(node->left_) && verify_balance(node->right_);
    }

public:
    using AVLTree<int>::AVLTree;

    bool verify_invariants() const
    {
        if (root_ == nullptr)
        {
            return true;
        }
        return root_->parent_ == end_ && verify_balance(root_) && verify_order(*this);
    }
};

TEMPLATE_TEST_CASE("Tree", "[tree]", BinarySearchTree<int>, RedBlackTree<int>, AVLTree<int>)
{
    using Tree = TestType;

    // Constructor / Destructor
    Tree empty;
    Tree some = {3, 1, 5, 2, 4};

    // Comparison
    REQUIRE(empty == Tree());
    REQUIRE(some == Tree({5, 4, 3, 2, 1}));
    REQUIRE(empty != some);
    REQUIRE(some != Tree({1, 2, 3, 4, 6}));

    REQUIRE(Tree({2, 3, 3, 3}) == Tree({2, 2, 3, 3}));
    REQUIRE(Tree({2, 3, 3, 3}) != Tree({3, 3, 3, 3}));

    // Iterator
    REQUIRE(empty.begin() == empty.end());

    int i = 1;
    for (auto it = some.begin(); it != some.end(); ++it)
    {
        REQUIRE(*it == i++);
    }

    i = 1;
    for (const auto& e : some)
    {
        REQUIRE(e == i++);
    }

    auto it = some.begin();
    REQUIRE(*it == 1);
    REQUIRE(*++it == 2);
    REQUIRE(*++it == 3);
    REQUIRE(*++it == 4);
    REQUIRE(*++it == 5);
    REQUIRE(++it == some.end());
    REQUIRE(*--it == 5);
    REQUIRE(*--it == 4);
    REQUIRE(*--it == 3);
    REQUIRE(*--it == 2);
    REQUIRE(*--it == 1);
    REQUIRE(it == some.begin());

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);

    REQUIRE(empty.is_empty() == true);
    REQUIRE(some.is_empty() == false);

    REQUIRE(some.min() == 1);
    REQUIRE_THROWS_MATCHES(empty.min(), std::runtime_error, Message("Error: The container is empty."));

    REQUIRE(some.max() == 5);
    REQUIRE_THROWS_MATCHES(empty.max(), std::runtime_error, Message("Error: The container is empty."));

    std::ostringstream buf;
    auto action = [&](const auto& e)
    { buf << e << " "; };

    some.traverse(Tree::PreOrder, action);
    REQUIRE(buf.str() == "3 1 2 5 4 ");
    buf.str("");

    some.traverse(Tree::InOrder, action);
    REQUIRE(buf.str() == "1 2 3 4 5 ");
    buf.str("");

    some.traverse(Tree::PostOrder, action);
    REQUIRE(buf.str() == "2 1 4 5 3 ");
    buf.str("");

    some.traverse(Tree::LevelOrder, action);
    REQUIRE(buf.str() == "3 1 5 2 4 ");
    buf.str("");

    REQUIRE(empty.find(1) == empty.end());
    REQUIRE(*some.find(1) == 1);
    REQUIRE(some.find(6) == some.end());

    REQUIRE(some.contains(1) == true);
    REQUIRE(some.contains(0) == false);
    REQUIRE(empty.contains(1) == false);
    REQUIRE(empty.contains(0) == false);

    REQUIRE(some.depth() == 3);
    REQUIRE(empty.depth() == 0);

    // Manipulation
    REQUIRE(empty.insert(1) == true);
    REQUIRE(empty == Tree({1}));
    REQUIRE(empty.insert(0) == true);
    REQUIRE(empty == Tree({0, 1}));
    REQUIRE(empty.insert(2) == true);
    REQUIRE(empty == Tree({0, 1, 2}));
    REQUIRE(empty.insert(3) == true);
    REQUIRE(empty == Tree({0, 1, 2, 3}));
    REQUIRE(empty.insert(3) == false);
    REQUIRE(empty == Tree({0, 1, 2, 3}));

    REQUIRE(empty.remove(3) == true);
    REQUIRE(empty == Tree({0, 1, 2}));
    REQUIRE(empty.remove(2) == true);
    REQUIRE(empty == Tree({0, 1}));
    REQUIRE(empty.remove(1) == true);
    REQUIRE(empty == Tree({0}));
    REQUIRE(empty.remove(0) == true);
    REQUIRE(empty == Tree({}));
    REQUIRE(empty.remove(0) == false);
    REQUIRE(empty == Tree({}));

    some.clear();
    REQUIRE(some == empty);
    some.clear(); // double clear
    REQUIRE(some == empty);

    // Print
    std::ostringstream oss;

    oss << Tree({});
    REQUIRE(oss.str() == "Tree()");

    oss.str("");
    oss << Tree({1});
    REQUIRE(oss.str() == "Tree(1)");

    oss.str("");
    oss << Tree({1, 2, 3, 4, 5});
    REQUIRE(oss.str() == "Tree(1, 2, 3, 4, 5)");
}

TEMPLATE_TEST_CASE("Tree with user-defined type", "[tree]", BinarySearchTree<EqLtType>, RedBlackTree<EqLtType>, AVLTree<EqLtType>)
{
    using Tree = TestType;

    Tree empty;
    Tree some = {EqLtType(), EqLtType(), EqLtType(), EqLtType(), EqLtType()};
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);
}

// Shared helpers for invariant tests.
template <typename Tree, typename T>
static void run_mixed_ops(Tree& tree, const T items[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        REQUIRE(tree.insert(items[i]) == true);
        REQUIRE(tree.verify_invariants() == true);
    }
    // Insert all in reverse order, verifying invariants.
    for (int i = n - 1; i >= 0; --i)
    {
        REQUIRE(tree.remove(items[i]) == true);
        REQUIRE(tree.verify_invariants() == true);
    }
    REQUIRE(tree.is_empty() == true);
}

const int g_data[] = {10, 20, 30, 15, 25, 5, 1, 50, 60, 55, 52, 58, 40, 45, 42, 41};

TEST_CASE("RedBlackTree invariants", "[tree]")
{
    InspectableRedBlackTree tree;
    run_mixed_ops(tree, g_data, 16);

    // Sequential deletion after bulk insert.
    const int r1[] = {8, 9, 10, 11, 12, 13, 14, 15, 7, 6, 5, 4, 3, 2, 1};
    const int r2[] = {15, 60, 30, 22, 45, 17, 18, 27, 7, 16, 37, 52, 70, 75, 80};
    InspectableRedBlackTree t1 = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
    for (int v : r1)
    {
        REQUIRE(t1.remove(v) == true);
        REQUIRE(t1.verify_invariants() == true);
    }
    REQUIRE(t1.is_empty() == true);
    InspectableRedBlackTree t2 = {30, 15, 60, 7, 22, 45, 75, 17, 27, 37, 52, 70, 80, 16, 18};
    for (int v : r2)
    {
        REQUIRE(t2.remove(v) == true);
        REQUIRE(t2.verify_invariants() == true);
    }
    REQUIRE(t2.is_empty() == true);
}

TEST_CASE("AVLTree invariants", "[tree]")
{
    // Mixed random-like operations.
    InspectableAVLTree tree;
    run_mixed_ops(tree, g_data, 16);

    // Ascending insertion (worst case for naive BST).
    InspectableAVLTree asc;
    for (int i = 0; i < 100; ++i)
    {
        REQUIRE(asc.insert(i) == true);
        REQUIRE(asc.verify_invariants() == true);
    }
    REQUIRE(asc.size() == 100);
    for (int i = 0; i < 100; ++i)
    {
        REQUIRE(asc.remove(i) == true);
        REQUIRE(asc.verify_invariants() == true);
    }
    REQUIRE(asc.is_empty() == true);

    // Descending insertion.
    InspectableAVLTree desc;
    for (int i = 99; i >= 0; --i)
    {
        REQUIRE(desc.insert(i) == true);
        REQUIRE(desc.verify_invariants() == true);
    }
    REQUIRE(desc.size() == 100);
    for (int i = 99; i >= 0; --i)
    {
        REQUIRE(desc.remove(i) == true);
        REQUIRE(desc.verify_invariants() == true);
    }
    REQUIRE(desc.is_empty() == true);

    // Alternating insertion and clear.
    InspectableAVLTree alt;
    for (int i = 0; i < 50; ++i)
    {
        REQUIRE(alt.insert(i) == true);
        REQUIRE(alt.insert(99 - i) == true);
        REQUIRE(alt.verify_invariants() == true);
    }
    REQUIRE(alt.size() == 100);
    alt.clear();
    REQUIRE(alt.is_empty() == true);
    REQUIRE(alt.verify_invariants() == true);
}
