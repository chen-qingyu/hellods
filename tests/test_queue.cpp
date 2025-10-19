#include "tool.hpp"

#include "../sources/Queue/ArrayQueue.hpp"
#include "../sources/Queue/LinkedQueue.hpp"

using namespace hellods;

TEMPLATE_TEST_CASE("Queue", "[queue]", ArrayQueue<int>, LinkedQueue<int>)
{
    using Queue = TestType;

    // Constructor / Destructor
    Queue empty;
    Queue some = {1, 2, 3, 4, 5};

    // Comparison
    REQUIRE(empty == Queue());
    REQUIRE(some == Queue({1, 2, 3, 4, 5}));
    REQUIRE(empty != some);
    REQUIRE(some != Queue({1, 2, 3, 4, 6}));

    // Access
    REQUIRE(some.front() == 1);
    some.front() = 0;
    REQUIRE(some.front() == 0);
    REQUIRE_THROWS_MATCHES(empty.front(), std::runtime_error, Message("Error: The container is empty."));
    const Queue cqueue = {1};
    REQUIRE(cqueue.front() == 1);

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);

    REQUIRE(empty.is_empty() == true);
    REQUIRE(some.is_empty() == false);

    // Manipulation
    empty.enqueue(1);
    REQUIRE(empty == Queue({1}));
    empty.enqueue(2);
    REQUIRE(empty == Queue({1, 2}));
    empty.enqueue(3);
    REQUIRE(empty == Queue({1, 2, 3}));

    REQUIRE(empty.dequeue() == 1);
    REQUIRE(empty.dequeue() == 2);
    REQUIRE(empty.dequeue() == 3);
    REQUIRE_THROWS_MATCHES(empty.dequeue(), std::runtime_error, Message("Error: The container is empty."));

    some.clear();
    REQUIRE(some == empty);
    some.clear(); // double clear
    REQUIRE(some == empty);

    // Print
    std::ostringstream oss;

    oss << Queue({});
    REQUIRE(oss.str() == "Queue()");
    oss.str("");

    oss << Queue({1});
    REQUIRE(oss.str() == "Queue(1)");
    oss.str("");

    oss << Queue({1, 2, 3, 4, 5});
    REQUIRE(oss.str() == "Queue(1, 2, 3, 4, 5)");
    oss.str("");
}

TEMPLATE_TEST_CASE("Queue with user-defined type", "[queue]", ArrayQueue<EqType>, LinkedQueue<EqType>)
{
    using Queue = TestType;

    Queue empty;
    Queue some = {EqType(), EqType(), EqType(), EqType(), EqType()};
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 5);
}
