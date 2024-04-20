#include "tool.hpp"

#include "../sources/Deque/ArrayDeque.hpp"
#include "../sources/Deque/LinkedDeque.hpp"

using namespace hellods;

template <typename Deque>
void test()
{
    // Constructor / Destructor
    Deque empty;
    Deque some = {1, 2, 3, 4, 5};

    // Comparison
    REQUIRE(empty == Deque());
    REQUIRE(some == Deque({1, 2, 3, 4, 5}));
    REQUIRE(empty != some);
    REQUIRE(some != Deque({1, 2, 3, 4, 6}));

    // Access
    REQUIRE(some.front() == 1);
    some.front() = 0;
    REQUIRE(some.front() == 0);
    REQUIRE_THROWS_MATCHES(empty.front(), std::runtime_error, Message("Error: The container is empty."));

    REQUIRE(some.back() == 5);
    some.back() = 6;
    REQUIRE(some.back() == 6);
    REQUIRE_THROWS_MATCHES(empty.back(), std::runtime_error, Message("Error: The container is empty."));

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);

    REQUIRE(empty.is_empty() == true);
    REQUIRE(some.is_empty() == false);

    // Manipulation
    empty.push_front(1);
    REQUIRE(empty == Deque({1}));
    empty.push_front(0);
    REQUIRE(empty == Deque({0, 1}));
    empty.push_back(2);
    REQUIRE(empty == Deque({0, 1, 2}));
    empty.push_back(3);
    REQUIRE(empty == Deque({0, 1, 2, 3}));

    REQUIRE(empty.pop_front() == 0);
    REQUIRE(empty.pop_front() == 1);
    REQUIRE(empty.pop_back() == 3);
    REQUIRE(empty.pop_back() == 2);
    REQUIRE_THROWS_MATCHES(empty.pop_front(), std::runtime_error, Message("Error: The container is empty."));
    REQUIRE_THROWS_MATCHES(empty.pop_back(), std::runtime_error, Message("Error: The container is empty."));

    REQUIRE(some.clear() == empty);
    REQUIRE(some.clear() == empty); // double clear

    // Print
    std::ostringstream oss;

    oss << Deque({});
    REQUIRE(oss.str() == "Deque()");
    oss.str("");

    oss << Deque({1});
    REQUIRE(oss.str() == "Deque(1)");
    oss.str("");

    oss << Deque({1, 2, 3, 4, 5});
    REQUIRE(oss.str() == "Deque(1, 2, 3, 4, 5)");
    oss.str("");
}

TEST_CASE("ArrayDeque")
{
    test<ArrayDeque<int>>();

    ArrayDeque<EqType> empty;
    ArrayDeque<EqType> some = {EqType(), EqType(), EqType()};
}

TEST_CASE("LinkedDeque")
{
    test<LinkedDeque<int>>();

    LinkedDeque<EqType> empty;
    LinkedDeque<EqType> some = {EqType(), EqType(), EqType()};
}
