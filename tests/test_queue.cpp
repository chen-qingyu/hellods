#include "tool.hpp"

#include "../sources/Queue/ArrayQueue.hpp"
#include "../sources/Queue/LinkedQueue.hpp"

TEMPLATE_TEST_CASE("Queue", "[queue]", ArrayQueue<int>, LinkedQueue<int>)
{
    using Queue = TestType;

    // Lifecycle
    Queue empty;
    Queue some = {1, 2, 3, 4, 5};

    Queue copy = some; // Copy constructor
    REQUIRE(copy == Queue({1, 2, 3, 4, 5}));

    copy = empty; // Copy assignment
    REQUIRE(copy == Queue());
    copy = some;
    REQUIRE(copy == Queue({1, 2, 3, 4, 5}));
    copy = copy;
    REQUIRE(copy == Queue({1, 2, 3, 4, 5}));

    Queue mv = std::move(copy); // Move constructor
    REQUIRE(mv == Queue({1, 2, 3, 4, 5}));

    copy = std::move(mv); // Move assignment
    REQUIRE(copy == Queue({1, 2, 3, 4, 5}));
    copy = std::move(copy);
    REQUIRE(copy == Queue({1, 2, 3, 4, 5}));

    // Comparison
    REQUIRE(empty == Queue());
    REQUIRE(some == Queue({1, 2, 3, 4, 5}));
    REQUIRE(empty != some);
    REQUIRE(some != Queue({1, 2, 3, 4, 6}));

    // Iterator
    REQUIRE(empty.begin() == empty.end());

    std::set<int> items;
    for (const auto& x : some)
    {
        items.insert(x);
    }
    REQUIRE(items == std::set<int>({1, 2, 3, 4, 5}));
    REQUIRE(std::distance(some.begin(), some.end()) == some.size());

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
