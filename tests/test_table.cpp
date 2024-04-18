#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "../sources/Table/HashTable.hpp"

using Catch::Matchers::Message;

using namespace hellods;

template <typename Table>
void test()
{
    // Constructor / Destructor
    Table empty;
    Table some = {{1, "one"}, {2, "two"}, {3, "three"}};

    // Comparison
    REQUIRE(empty == Table());
    REQUIRE(some == Table({{1, "one"}, {2, "two"}, {3, "three"}}));
    REQUIRE(empty != some);
    REQUIRE(some != Table({{1, "one"}, {2, "two"}, {4, "four"}}));

    REQUIRE(Table({{1, "one"}, {2, "two"}, {3, "three"}}) != Table({{1, "one"}, {2, "two"}, {3, "333"}}));
    REQUIRE(Table({{1, "one"}, {2, "two"}, {3, "three"}}) != Table({{1, "one"}, {2, "two"}, {4, "three"}}));

    // Access
    REQUIRE(some[1] == "one");
    some[1] = "+1";
    REQUIRE(some[1] == "+1");
    some[1] = "one";
    REQUIRE(some[1] == "one");
    const Table const_table = {{1, "one"}, {2, "two"}, {3, "three"}};
    REQUIRE(const_table[1] == "one");
    REQUIRE_THROWS_MATCHES(some[4], std::runtime_error, Message("Error: The key-value pair does not exist."));
    REQUIRE_THROWS_MATCHES(empty[1], std::runtime_error, Message("Error: The key-value pair does not exist."));

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
    REQUIRE(empty == Table({{1, "one"}}));
    REQUIRE(empty.insert(2, "two") == true);
    REQUIRE(empty == Table({{1, "one"}, {2, "two"}}));
    REQUIRE(empty.insert(3, "three") == true);
    REQUIRE(empty == Table({{1, "one"}, {2, "two"}, {3, "three"}}));
    REQUIRE(empty.insert(3, "three!") == false);
    REQUIRE(empty == Table({{1, "one"}, {2, "two"}, {3, "three"}}));

    REQUIRE(empty.remove(3) == true);
    REQUIRE(empty == Table({{1, "one"}, {2, "two"}}));
    REQUIRE(empty.remove(2) == true);
    REQUIRE(empty == Table({{1, "one"}}));
    REQUIRE(empty.remove(1) == true);
    REQUIRE(empty == Table({}));
    REQUIRE(empty.remove(1) == false);
    REQUIRE(empty == Table({}));

    REQUIRE(some.clear() == empty);
    REQUIRE(some.clear() == empty); // double clear

    // Print
    std::ostringstream oss;

    oss << Table({});
    REQUIRE(oss.str() == "Table()");
    oss.str("");

    oss << Table({{1, "one"}});
    REQUIRE(oss.str() == "Table(1: one)");
    oss.str("");

    oss << Table({{1, "one"}, {2, "two"}, {3, "three"}});
    REQUIRE(oss.str() == "Table(1: one, 2: two, 3: three)");
    oss.str("");
}

TEST_CASE("HashTable")
{
    test<HashTable<int, std::string>>();
}
