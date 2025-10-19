#include "tool.hpp"

#include "../sources/Map/HashMap.hpp"

using namespace hellods;

TEMPLATE_TEST_CASE("Map", "[map]", (HashMap<int, std::string>))
{
    using Map = TestType;

    // Constructor / Destructor
    Map empty;
    Map some = {{1, "one"}, {2, "two"}, {3, "three"}};

    // Comparison
    REQUIRE(empty == Map());
    REQUIRE(some == Map({{1, "one"}, {2, "two"}, {3, "three"}}));
    REQUIRE(empty != some);
    REQUIRE(some != Map({{1, "one"}, {2, "two"}, {4, "four"}}));

    REQUIRE(Map({{1, "one"}, {2, "two"}, {3, "three"}}) != Map({{1, "one"}, {2, "two"}, {3, "333"}}));
    REQUIRE(Map({{1, "one"}, {2, "two"}, {3, "three"}}) != Map({{1, "one"}, {2, "two"}, {4, "three"}}));

    // Access
    REQUIRE(some[1] == "one");
    some[1] = "+1";
    REQUIRE(some[1] == "+1");
    some[1] = "one";
    REQUIRE(some[1] == "one");

    const Map const_map = {{1, "one"}, {2, "two"}, {3, "three"}};
    REQUIRE(const_map[1] == "one");

    REQUIRE_THROWS_MATCHES(empty[1], std::runtime_error, Message("Error: The key-value pair does not exist."));
    REQUIRE_THROWS_MATCHES(some[4], std::runtime_error, Message("Error: The key-value pair does not exist."));

    // Iterator
    REQUIRE(empty.begin() == empty.end());

    int i = 1;
    for (auto it = some.begin(); it != some.end(); ++it)
    {
        REQUIRE(it->first == i++);
    }

    i = 1;
    for (const auto& e : some)
    {
        REQUIRE(e.first == i++);
    }

    auto it = some.begin();
    REQUIRE(*it == std::pair{1, "one"});
    REQUIRE(*++it == std::pair{2, "two"});
    REQUIRE(*++it == std::pair{3, "three"});
    REQUIRE(++it == some.end());
    REQUIRE(*--it == std::pair{3, "three"});
    REQUIRE(*--it == std::pair{2, "two"});
    REQUIRE(*--it == std::pair{1, "one"});
    REQUIRE(it == some.begin());

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 3);

    REQUIRE(empty.is_empty() == true);
    REQUIRE(some.is_empty() == false);

    REQUIRE(empty.find(1) == empty.end());
    REQUIRE(*some.find(2) == std::pair{2, "two"});
    REQUIRE(some.find(4) == some.end());

    REQUIRE(empty.contains(1) == false);
    REQUIRE(empty.contains(0) == false);
    REQUIRE(some.contains(1) == true);
    REQUIRE(some.contains(0) == false);

    // Manipulation
    REQUIRE(empty.insert(1, "one") == true);
    REQUIRE(empty == Map({{1, "one"}}));
    REQUIRE(empty.insert(1, "one!") == false);
    REQUIRE(empty == Map({{1, "one"}}));

    REQUIRE(empty.remove(1) == true);
    REQUIRE(empty == Map({}));
    REQUIRE(empty.remove(1) == false);
    REQUIRE(empty == Map({}));

    some.clear();
    REQUIRE(some == empty);
    some.clear(); // double clear
    REQUIRE(some == empty);

    for (int i = 0; i < 100; i++)
    {
        REQUIRE(empty.insert(i, std::to_string(i)) == true);
    }
    REQUIRE(empty.size() == 100);
    for (int i = 0; i < 100; i++)
    {
        REQUIRE(empty.contains(i) == true);
        REQUIRE(empty[i] == std::to_string(i));
    }
    for (int i = 0; i < 100; i++)
    {
        REQUIRE(empty.remove(i) == true);
    }
    REQUIRE(empty.size() == 0);

    // Print
    std::ostringstream oss;

    oss << Map({});
    REQUIRE(oss.str() == "Map()");
    oss.str("");

    oss << Map({{1, "one"}});
    REQUIRE(oss.str() == "Map(1: one)");
    oss.str("");

    oss << Map({{1, "one"}, {2, "two"}, {3, "three"}});
    REQUIRE(oss.str() == "Map(1: one, 2: two, 3: three)");
    oss.str("");
}

TEMPLATE_TEST_CASE("Map with user-defined type", "[map]", (HashMap<EqType, EqType>))
{
    using Map = TestType;

    Map empty;
    Map some = {{EqType(), EqType()}, {EqType(), EqType()}, {EqType(), EqType()}};
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 3);
}
