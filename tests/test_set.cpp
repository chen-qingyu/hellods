#include "tool.hpp"

#include "../sources/Set/HashSet.hpp"

using namespace hellods;

TEMPLATE_TEST_CASE("Set", "[set]", HashSet<int>)
{
    using Set = TestType;

    // Constructor / Destructor
    Set empty;
    Set some = {1, 2, 3};

    // Comparison
    REQUIRE(empty == Set());
    REQUIRE(some == Set({1, 2, 3}));
    REQUIRE(empty != some);
    REQUIRE(some != Set({1, 2, 4}));
    REQUIRE(some != Set({1, 2}));

    // Iterator
    REQUIRE(empty.begin() == empty.end());

    int sum = 0;
    for (auto it = some.begin(); it != some.end(); ++it)
    {
        sum += *it;
    }
    REQUIRE(sum == 6);

    sum = 0;
    for (const auto& e : some)
    {
        sum += e;
    }
    REQUIRE(sum == 6);

    auto it = some.begin();
    REQUIRE(*it == 1);
    REQUIRE(*++it == 2);
    REQUIRE(*++it == 3);
    REQUIRE(++it == some.end());
    REQUIRE(*--it == 3);
    REQUIRE(*--it == 2);
    REQUIRE(*--it == 1);
    REQUIRE(it == some.begin());

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

TEMPLATE_TEST_CASE("Set with user-defined type", "[set]", HashSet<EqType>)
{
    using Set = TestType;

    Set empty;
    Set some = {EqType(), EqType(), EqType()};
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 3);
}
