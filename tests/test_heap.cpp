#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "../sources/Heap/BinaryHeap.hpp"

using Catch::Matchers::Message;

using namespace hellods;

template <typename Heap>
void test()
{
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

    // Access
    REQUIRE(some.peek() == 5);
    REQUIRE_THROWS_MATCHES(empty.peek(), std::runtime_error, Message("Error: The container is empty."));

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(empty.is_empty() == true);

    REQUIRE(some.size() == 5);
    REQUIRE(some.is_empty() == false);

    // Manipulation
    empty.push(1);
    REQUIRE(empty == Heap({1}));
    empty.push(0);
    REQUIRE(empty == Heap({1, 0}));
    empty.push(2);
    REQUIRE(empty == Heap({2, 1, 0}));
    empty.push(3);
    REQUIRE(empty == Heap({3, 2, 1, 0}));

    REQUIRE(empty.pop() == 3);
    REQUIRE(empty.pop() == 2);
    REQUIRE(empty.pop() == 1);
    REQUIRE(empty.pop() == 0);
    REQUIRE_THROWS_MATCHES(empty.pop(), std::runtime_error, Message("Error: The container is empty."));

    REQUIRE(some.clear() == empty);
    REQUIRE(some.clear() == empty); // double clear

    // Print
    std::ostringstream oss;

    oss << Heap({});
    REQUIRE(oss.str() == "Heap()");
    oss.str("");

    oss << Heap({1});
    REQUIRE(oss.str() == "Heap(1)");
    oss.str("");

    oss << Heap({1, 2, 3, 4, 5});
    REQUIRE(oss.str() == "Heap(5, 4, 3, 1, 2)");
    oss.str("");
}

TEST_CASE("BinaryHeap")
{
    test<BinaryHeap<int>>();
    test<BinaryHeap<double>>();

    BinaryHeap<int, std::less<int>> min_heap = {3, 2, 1};
    REQUIRE(min_heap.peek() == 1);
    REQUIRE(min_heap.pop() == 1);
    REQUIRE(min_heap.pop() == 2);
    REQUIRE(min_heap.pop() == 3);
}
