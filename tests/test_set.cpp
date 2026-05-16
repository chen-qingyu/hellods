#include "tool.hpp"

TEMPLATE_TEST_CASE("Set", "[set]", HashSet<int>, TreeSet<int>)
{
    using Set = TestType;

    // Lifecycle
    Set empty;
    Set some = {1, 2, 3};

    Set copy = some; // Copy constructor
    REQUIRE(copy == Set({1, 2, 3}));

    copy = empty; // Copy assignment
    REQUIRE(copy == Set());
    copy = some;
    REQUIRE(copy == Set({1, 2, 3}));
    copy = copy;
    REQUIRE(copy == Set({1, 2, 3}));

    Set mv = std::move(copy); // Move constructor
    REQUIRE(mv == Set({1, 2, 3}));

    copy = std::move(mv); // Move assignment
    REQUIRE(copy == Set({1, 2, 3}));
    copy = std::move(copy);
    REQUIRE(copy == Set({1, 2, 3}));

    // Comparison
    REQUIRE(empty == Set());
    REQUIRE(some == Set({1, 2, 3}));
    REQUIRE(empty != some);
    REQUIRE(some != Set({1, 2, 4}));
    REQUIRE(some != Set({1, 2}));

    // Iterator
    REQUIRE(empty.begin() == empty.end());

    // forward iteration (range-for uses ++it internally)
    std::set<int> elements;
    for (const auto& e : some)
    {
        elements.insert(e);
    }
    REQUIRE(elements == std::set<int>({1, 2, 3}));

    // backward iteration via --it from end back to begin
    auto it = some.end();
    elements.clear();
    while (it != some.begin())
    {
        --it;
        elements.insert(*it);
    }
    REQUIRE(elements == std::set<int>({1, 2, 3}));

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 3);

    REQUIRE(empty.is_empty() == true);
    REQUIRE(some.is_empty() == false);

    REQUIRE(empty.find(1) == empty.end());
    REQUIRE(*some.find(2) == 2);
    REQUIRE(some.find(4) == some.end());

    REQUIRE(empty.contains(1) == false);
    REQUIRE(empty.contains(0) == false);
    REQUIRE(some.contains(1) == true);
    REQUIRE(some.contains(0) == false);

    // Manipulation
    REQUIRE(empty.insert(1) == true);
    REQUIRE(empty == Set({1}));
    REQUIRE(empty.insert(1) == false);
    REQUIRE(empty == Set({1}));

    REQUIRE(empty.remove(1) == true);
    REQUIRE(empty == Set({}));
    REQUIRE(empty.remove(1) == false);
    REQUIRE(empty == Set({}));

    some.clear();
    REQUIRE(some == empty);
    some.clear(); // double clear
    REQUIRE(some == empty);

    for (int i = 0; i < 100; i++)
    {
        REQUIRE(empty.insert(i) == true);
    }
    REQUIRE(empty.size() == 100);
    for (int i = 0; i < 100; i++)
    {
        REQUIRE(empty.contains(i) == true);
    }
    for (int i = 0; i < 100; i++)
    {
        REQUIRE(empty.remove(i) == true);
    }
    REQUIRE(empty.size() == 0);

    // Print
    std::ostringstream oss;

    oss << Set({});
    REQUIRE(oss.str() == "Set()");
    oss.str("");

    oss << Set({1});
    REQUIRE(oss.str() == "Set(1)");
    oss.str("");

    oss << Set({1, 2, 3});
    REQUIRE(oss.str() == "Set(1, 2, 3)");
    oss.str("");
}
