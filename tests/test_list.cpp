#include "tool.hpp"

#include "../sources/List/ArrayList.hpp"
#include "../sources/List/LinkedList.hpp"
#include "../sources/List/SinglyLinkedList.hpp"

using namespace hellods;

template <typename List>
void test()
{
    // Constructor / Destructor
    List empty;
    List some = {1, 2, 3, 4, 5};

    // Comparison
    REQUIRE(empty == List());
    REQUIRE(some == List({1, 2, 3, 4, 5}));
    REQUIRE(empty != some);
    REQUIRE(some != List({1, 2, 3, 4, 6}));

    // Access
    for (int i = 0; i < 5; ++i)
    {
        REQUIRE(some[i] == i + 1);
    }
    for (int i = 0; i < 5; ++i)
    {
        some[i] = i;
        REQUIRE(some[i] == i);
    }
    REQUIRE_THROWS_MATCHES(some[5], std::runtime_error, Message("Error: Index out of range."));

    // Iterator
    REQUIRE(empty.begin() == empty.end());

    int i = 0;
    for (auto it = some.begin(); it != some.end(); ++it)
    {
        REQUIRE(*it == i++);
    }

    i = 0;
    for (const auto& e : some)
    {
        REQUIRE(e == i++);
    }

    auto it = some.begin();
    REQUIRE(*it == 0);
    REQUIRE(*++it == 1);
    REQUIRE(*++it == 2);
    REQUIRE(*++it == 3);
    REQUIRE(*++it == 4);
    REQUIRE(++it == some.end());
    if constexpr (!std::is_same<List, SinglyLinkedList<int>>::value)
    {
        REQUIRE(*--it == 4);
        REQUIRE(*--it == 3);
        REQUIRE(*--it == 2);
        REQUIRE(*--it == 1);
        REQUIRE(*--it == 0);
        REQUIRE(it == some.begin());
    }

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);

    REQUIRE(empty.is_empty() == true);
    REQUIRE(some.is_empty() == false);

    REQUIRE(empty.find(1) == empty.end());
    REQUIRE(*some.find(1) == 1);
    REQUIRE(some.find(6) == some.end());

    // Manipulation
    empty.insert(0, 1);
    REQUIRE(empty == List({1}));
    empty.insert(0, 2);
    REQUIRE(empty == List({2, 1}));
    empty.insert(2, 3);
    REQUIRE(empty == List({2, 1, 3}));
    REQUIRE_THROWS_MATCHES(empty.insert(4, 3), std::runtime_error, Message("Error: Index out of range."));

    REQUIRE(empty.remove(1) == 1);
    REQUIRE(empty.remove(0) == 2);
    REQUIRE(empty.remove(0) == 3);
    REQUIRE_THROWS_MATCHES(empty.remove(0), std::runtime_error, Message("Error: The container is empty."));

    REQUIRE(some.map([&](auto& e)
                     { e *= 2; }) == List({0, 2, 4, 6, 8}));

    REQUIRE(some.reverse() == List({8, 6, 4, 2, 0}));

    REQUIRE(some.clear() == empty);
    REQUIRE(some.clear() == empty); // double clear

    // Print
    std::ostringstream oss;

    oss << List({});
    REQUIRE(oss.str() == "List()");
    oss.str("");

    oss << List({1});
    REQUIRE(oss.str() == "List(1)");
    oss.str("");

    oss << List({1, 2, 3, 4, 5});
    REQUIRE(oss.str() == "List(1, 2, 3, 4, 5)");
    oss.str("");
}

TEST_CASE("ArrayList")
{
    test<ArrayList<int>>();

    ArrayList<EqType> empty;
    ArrayList<EqType> some = {EqType(), EqType(), EqType(), EqType(), EqType()};
}

TEST_CASE("LinkedList")
{
    test<LinkedList<int>>();

    LinkedList<EqType> empty;
    LinkedList<EqType> some = {EqType(), EqType(), EqType(), EqType(), EqType()};
}

TEST_CASE("SinglyLinkedList")
{
    test<SinglyLinkedList<int>>();

    SinglyLinkedList<EqType> empty;
    SinglyLinkedList<EqType> some = {EqType(), EqType(), EqType(), EqType(), EqType()};
}
