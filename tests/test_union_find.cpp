#include "tool.hpp"

#include "../sources/DisjointSet/UnionFind.hpp"

TEST_CASE("UnionFind", "[union_find]")
{
    using hellods::UnionFind;

    // Lifecycle
    UnionFind<int> empty;
    REQUIRE(empty.size() == 0);
    REQUIRE(empty.is_empty() == true);

    UnionFind<int> uf = {0, 1, 2, 3, 4};
    REQUIRE(uf.size() == 5);
    REQUIRE(uf.is_empty() == false);

    // Initial state: all isolated
    REQUIRE_FALSE(uf.is_connected(0, 1));
    REQUIRE_FALSE(uf.is_connected(0, 4));

    // Initial state equals a freshly built set with same elements
    REQUIRE(uf == UnionFind<int>({0, 1, 2, 3, 4}));
    REQUIRE(uf != UnionFind<int>({0, 1, 2, 3, 5}));

    // Unite and check connectivity
    REQUIRE(uf.unite(0, 1) == true);
    REQUIRE(uf.is_connected(0, 1));
    REQUIRE_FALSE(uf.is_connected(0, 2));
    REQUIRE_FALSE(uf.is_connected(0, 4));

    REQUIRE(uf.unite(2, 3) == true);
    REQUIRE(uf.is_connected(2, 3));
    REQUIRE_FALSE(uf.is_connected(0, 2));

    REQUIRE(uf.unite(0, 2) == true);
    REQUIRE(uf.is_connected(0, 2));
    REQUIRE(uf.is_connected(1, 3));
    REQUIRE_FALSE(uf.is_connected(0, 4));

    // Unite already-connected returns false
    REQUIRE_FALSE(uf.unite(0, 1));

    // find returns same representative for connected elements
    int rep = uf.find(0);
    REQUIRE(uf.find(1) == rep);
    REQUIRE(uf.find(2) == rep);
    REQUIRE(uf.find(3) == rep);

    // Comparison
    REQUIRE(empty == UnionFind<int>());
    REQUIRE(empty != uf);
    REQUIRE(uf != UnionFind<int>({0, 1, 2, 3, 4})); // different connectivity

    // Copy constructor
    UnionFind<int> copy = uf;
    REQUIRE(copy == uf);

    // Copy assignment
    copy = empty;
    REQUIRE(copy == UnionFind<int>());
    copy = uf;
    REQUIRE(copy == uf);

    // Move constructor
    UnionFind<int> mv = std::move(copy);
    REQUIRE(mv == uf);

    // Move assignment
    copy = std::move(mv);
    REQUIRE(copy == uf);

    // Self move
    copy = std::move(copy);
    REQUIRE(copy == uf);

    // Dynamic add
    UnionFind<int> dynamic;
    REQUIRE(dynamic.add(10) == true);
    REQUIRE(dynamic.add(20) == true);
    REQUIRE(dynamic.add(30) == true);
    REQUIRE(dynamic.add(10) == false); // already exists
    REQUIRE(dynamic.size() == 3);
    REQUIRE(dynamic.contains(10));
    REQUIRE_FALSE(dynamic.contains(99));

    dynamic.unite(10, 20);
    REQUIRE(dynamic.is_connected(10, 20));
    REQUIRE_FALSE(dynamic.is_connected(10, 30));

    // String elements
    UnionFind<std::string> str_uf;
    str_uf.add("alice");
    str_uf.add("bob");
    str_uf.add("charlie");
    str_uf.unite("alice", "bob");
    REQUIRE(str_uf.is_connected("alice", "bob"));
    REQUIRE_FALSE(str_uf.is_connected("alice", "charlie"));
    REQUIRE(str_uf.find("alice") == str_uf.find("bob"));

    // Clear
    uf.clear();
    REQUIRE(uf.size() == 0);
    REQUIRE(uf.is_empty() == true);
}
