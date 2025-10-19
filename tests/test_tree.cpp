#include "tool.hpp"

#include "../sources/Tree/BinarySearchTree.hpp"
#include "../sources/Tree/RedBlackTree.hpp"

using namespace hellods;

TEMPLATE_TEST_CASE("Tree", "[tree]", BinarySearchTree<int>, RedBlackTree<int>)
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
    if constexpr (std::is_same<Tree, BinarySearchTree<int>>::value)
    {
        REQUIRE(oss.str() == "Tree(1, 2, 3, 4, 5)");
    }
    else if constexpr (std::is_same<Tree, RedBlackTree<int>>::value)
    {
        REQUIRE(oss.str() == "Tree(1, 2, 3, 4, 5)");
    }
    else
    {
        FAIL();
    }
    oss.str("");
}

TEMPLATE_TEST_CASE("Tree with user-defined type", "[tree]", BinarySearchTree<EqLtType>, RedBlackTree<EqLtType>)
{
    using Tree = TestType;

    Tree empty;
    Tree some = {EqLtType(), EqLtType(), EqLtType(), EqLtType(), EqLtType()};
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);
}
