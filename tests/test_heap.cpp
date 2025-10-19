#include "tool.hpp"

#include "../sources/Heap/BinaryHeap.hpp"

using namespace hellods;

TEMPLATE_TEST_CASE("Heap", "[heap]", BinaryHeap<int>, (BinaryHeap<int, std::less<int>>))
{
    using Heap = TestType;

    // Constructor / Destructor
    Heap empty;
    Heap some = {1, 2, 3, 4, 5};

    // Comparison
    REQUIRE(empty == Heap());
    REQUIRE(some == Heap({5, 4, 3, 2, 1}));
    REQUIRE(empty != some);
    REQUIRE(some != Heap({1, 2, 3, 4, 6}));

    REQUIRE(Heap({2, 3, 3, 3}) == Heap({3, 3, 3, 2}));
    REQUIRE(Heap({2, 3, 3, 3}) != Heap({2, 2, 3, 3}));

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);

    REQUIRE(empty.is_empty() == true);
    REQUIRE(some.is_empty() == false);

    if constexpr (std::is_same<Heap, BinaryHeap<int>>::value)
    {
        REQUIRE(some.peek() == 5);
    }
    else if constexpr (std::is_same<Heap, BinaryHeap<int, std::less<int>>>::value)
    {
        REQUIRE(some.peek() == 1);
    }
    else
    {
        FAIL();
    }

    REQUIRE_THROWS_MATCHES(empty.peek(), std::runtime_error, Message("Error: The container is empty."));

    // Manipulation
    empty.push(1);
    REQUIRE(empty == Heap({1}));
    empty.push(0);
    REQUIRE(empty == Heap({1, 0}));
    empty.push(2);
    REQUIRE(empty == Heap({2, 1, 0}));
    empty.push(3);
    REQUIRE(empty == Heap({3, 2, 1, 0}));

    if constexpr (std::is_same<Heap, BinaryHeap<int>>::value)
    {
        REQUIRE(empty.pop() == 3);
        REQUIRE(empty.pop() == 2);
        REQUIRE(empty.pop() == 1);
        REQUIRE(empty.pop() == 0);
    }
    else if constexpr (std::is_same<Heap, BinaryHeap<int, std::less<int>>>::value)
    {
        REQUIRE(empty.pop() == 0);
        REQUIRE(empty.pop() == 1);
        REQUIRE(empty.pop() == 2);
        REQUIRE(empty.pop() == 3);
    }
    else
    {
        FAIL();
    }
    REQUIRE_THROWS_MATCHES(empty.pop(), std::runtime_error, Message("Error: The container is empty."));

    some.clear();
    REQUIRE(some == empty);
    some.clear(); // double clear
    REQUIRE(some == empty);

    // Test with large number of elements
    Heap large;
    for (int i = 0; i < 100; ++i)
    {
        large.push(i);
    }
    REQUIRE(large.size() == 100);

    if constexpr (std::is_same<Heap, BinaryHeap<int>>::value)
    {
        REQUIRE(large.peek() == 99);
        for (int i = 99; i >= 0; --i)
        {
            REQUIRE(large.pop() == i);
        }
    }
    else if constexpr (std::is_same<Heap, BinaryHeap<int, std::less<int>>>::value)
    {
        REQUIRE(large.peek() == 0);
        for (int i = 0; i < 100; ++i)
        {
            REQUIRE(large.pop() == i);
        }
    }
    else
    {
        FAIL();
    }
    REQUIRE(large.is_empty() == true);

    // Print
    std::ostringstream oss;

    oss << Heap({});
    REQUIRE(oss.str() == "Heap()");
    oss.str("");

    oss << Heap({1});
    REQUIRE(oss.str() == "Heap(1)");
    oss.str("");

    oss << Heap({3, 1, 2, 4, 5});
    if constexpr (std::is_same<Heap, BinaryHeap<int>>::value)
    {
        REQUIRE(oss.str() == "Heap(5, 4, 2, 3, 1)");
    }
    else if constexpr (std::is_same<Heap, BinaryHeap<int, std::less<int>>>::value)
    {
        REQUIRE(oss.str() == "Heap(1, 3, 2, 4, 5)");
    }
    else
    {
        FAIL();
    }
    oss.str("");
}

TEMPLATE_TEST_CASE("Heap with user-defined type", "[heap]", (BinaryHeap<EqLtType, std::less<EqLtType>>))
{
    using Heap = TestType;

    Heap empty;
    Heap some = {EqLtType(), EqLtType(), EqLtType(), EqLtType(), EqLtType()};
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);
}
