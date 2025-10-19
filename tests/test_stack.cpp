#include "tool.hpp"

#include "../sources/Stack/ArrayStack.hpp"
#include "../sources/Stack/LinkedStack.hpp"

using namespace hellods;

TEMPLATE_TEST_CASE("Stack", "[stack]", ArrayStack<int>, LinkedStack<int>)
{
    using Stack = TestType;

    // Constructor / Destructor
    Stack empty;
    Stack some = {1, 2, 3, 4, 5};

    // Comparison
    REQUIRE(empty == Stack());
    REQUIRE(some == Stack({1, 2, 3, 4, 5}));
    REQUIRE(empty != some);
    REQUIRE(some != Stack({1, 2, 3, 4, 6}));

    // Access
    REQUIRE(some.top() == 5);
    some.top() = 6;
    REQUIRE(some.top() == 6);
    REQUIRE_THROWS_MATCHES(empty.top(), std::runtime_error, Message("Error: The container is empty."));
    const Stack cstak = {1};
    REQUIRE(cstak.top() == 1);

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);

    REQUIRE(empty.is_empty() == true);
    REQUIRE(some.is_empty() == false);

    // Manipulation
    empty.push(1);
    REQUIRE(empty == Stack({1}));
    empty.push(2);
    REQUIRE(empty == Stack({1, 2}));
    empty.push(3);
    REQUIRE(empty == Stack({1, 2, 3}));

    REQUIRE(empty.pop() == 3);
    REQUIRE(empty.pop() == 2);
    REQUIRE(empty.pop() == 1);
    REQUIRE_THROWS_MATCHES(empty.pop(), std::runtime_error, Message("Error: The container is empty."));

    some.clear();
    REQUIRE(some == empty);
    some.clear(); // double clear
    REQUIRE(some == empty);

    // Print
    std::ostringstream oss;

    oss << Stack({});
    REQUIRE(oss.str() == "Stack()");
    oss.str("");

    oss << Stack({1});
    REQUIRE(oss.str() == "Stack(1)");
    oss.str("");

    oss << Stack({1, 2, 3, 4, 5});
    REQUIRE(oss.str() == "Stack(1, 2, 3, 4, 5)");
    oss.str("");
}

TEMPLATE_TEST_CASE("Stack with user-defined type", "[stack]", ArrayStack<EqType>, LinkedStack<EqType>)
{
    using Stack = TestType;

    Stack empty;
    Stack some = {EqType(), EqType(), EqType(), EqType(), EqType()};
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);
}
