#include <catch2/catch_test_macros.hpp>

#include "../sources/List/ArrayList.hpp"
#include "../sources/List/DoublyLinkedList.hpp"
#include "../sources/List/LinkedList.hpp"

using namespace hellods;

template <typename List>
void test()
{
    // Constructor / Destructor
    List empty;
    List list = {1, 2, 3, 4, 5};

    // Comparison
    REQUIRE(empty == List());
    REQUIRE(list == List({1, 2, 3, 4, 5}));
    REQUIRE(empty != list);

    // Access
    for (int i = 0; i < 5; ++i)
    {
        REQUIRE(list[i] == i + 1);
    }

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(empty.is_empty() == true);
    REQUIRE(empty.find(1) == -1);

    REQUIRE(list.size() == 5);
    REQUIRE(list.is_empty() == false);
    REQUIRE(list.find(1) == 0);

    // Manipulation
    empty.insert(0, 1);
    REQUIRE(empty == List({1}));
    empty.insert(0, 2);
    REQUIRE(empty == List({2, 1}));
    empty.insert(2, 3);
    REQUIRE(empty == List({2, 1, 3}));

    REQUIRE(empty.remove(1) == 1);
    REQUIRE(empty.remove(0) == 2);
    REQUIRE(empty.remove(0) == 3);

    REQUIRE(list.map([&](auto& e)
                     { e *= 2; }) == List({2, 4, 6, 8, 10}));

    REQUIRE(list.reverse() == List({10, 8, 6, 4, 2}));

    REQUIRE(list.clear() == empty);
    REQUIRE(list.clear() == empty); // double clear
}

TEST_CASE("ArrayList")
{
    test<ArrayList<int>>();
    test<ArrayList<double>>();
}

TEST_CASE("DoublyLinkedList")
{
    test<DoublyLinkedList<int>>();
    test<DoublyLinkedList<double>>();
}

TEST_CASE("LinkedList")
{
    test<LinkedList<int>>();
    test<LinkedList<double>>();
}
