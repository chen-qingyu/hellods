#include "tool.hpp"

TEMPLATE_TEST_CASE("Graph", "[graph]", MatrixGraph<>, ListGraph<>)
{
    using Graph = TestType;

    // Lifecycle
    Graph empty;
    Graph some = {0, 1, 2, 3, 4, 5, 6};

    Graph copy = some; // Copy constructor
    REQUIRE(copy == Graph({0, 1, 2, 3, 4, 5, 6}));

    copy = empty; // Copy assignment
    REQUIRE(copy == Graph());
    copy = some;
    REQUIRE(copy == Graph({0, 1, 2, 3, 4, 5, 6}));
    copy = copy;
    REQUIRE(copy == Graph({0, 1, 2, 3, 4, 5, 6}));

    Graph mv = std::move(copy); // Move constructor
    REQUIRE(mv == Graph({0, 1, 2, 3, 4, 5, 6}));

    copy = std::move(mv); // Move assignment
    REQUIRE(copy == Graph({0, 1, 2, 3, 4, 5, 6}));
    copy = std::move(copy);
    REQUIRE(copy == Graph({0, 1, 2, 3, 4, 5, 6}));

    // Comparison
    REQUIRE(empty == Graph());
    REQUIRE(some == Graph({0, 1, 2, 3, 4, 5, 6}));
    REQUIRE(empty != some);
    REQUIRE(some != Graph({0, 1, 2, 3, 4, 5}));

    // Manipulation & Comparison
    Graph g1 = {0, 1};
    Graph g2 = {0, 1};
    g1.link(0, 1, 1000);
    g2.link(0, 1, 1000);
    REQUIRE(g1 == g2);
    g2.link(0, 1, 1001);
    REQUIRE(g1 != g2);
    g1.link(0, 1, 1001);
    REQUIRE(g1 == g2);

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(some.size() == 7);

    REQUIRE(empty.is_empty() == true);
    REQUIRE(some.is_empty() == false);

    // Iterator
    REQUIRE(empty.begin() == empty.end());

    std::set<int> vertices;
    for (const auto& v : some)
    {
        vertices.insert(v);
    }
    REQUIRE(vertices == std::set<int>({0, 1, 2, 3, 4, 5, 6}));

    REQUIRE_THROWS_MATCHES(empty.is_adjacent(0, 1), std::runtime_error, Message("Error: Vertex does not exist."));
    REQUIRE(some.is_adjacent(0, 1) == false);

    REQUIRE_THROWS_MATCHES(empty.distance(0, 1), std::runtime_error, Message("Error: Vertex does not exist."));
    REQUIRE(some.distance(0, 1) == std::nullopt);

    // Manipulation & Examination
    some.link(0, 1, 2);
    some.link(0, 3, 1);
    some.link(1, 4, 10);
    some.link(1, 3, 3);
    some.link(2, 0, 4);
    some.link(2, 5, 5);
    some.link(3, 2, 2);
    some.link(3, 4, 2);
    some.link(3, 5, 8);
    some.link(3, 6, 4);
    some.link(4, 6, 6);
    some.link(6, 5, 1);

    /*
          +--+   2    +--+
          |V0|------->|V1|
          +--+        +--+
       +--^  | 1    3 |  |  10
      4|     +--v  v--+  +--v
    +--+    2   +--+   2    +--+
    |V2|<-------|V3|------->|V4|
    +--+        +--+        +--+
      5|      8 |  | 4      |6
       +--v  v--+  +--v  v--+
          +--+   1    +--+
          |V5|<-------|V6|
          +--+        +--+
    */

    REQUIRE(some.is_adjacent(0, 1) == true);
    REQUIRE(some.is_adjacent(0, 6) == false);
    REQUIRE(some.is_adjacent(6, 0) == false);
    REQUIRE(some.distance(0, 1) == std::optional<int>(2));
    REQUIRE(some.distance(0, 6) == std::nullopt);

    some.link(0, 6, 99);
    REQUIRE(some.is_adjacent(0, 6) == true);
    REQUIRE(some.is_adjacent(6, 0) == false);

    some.unlink(0, 6);
    REQUIRE(some.is_adjacent(0, 6) == false);
    REQUIRE(some.is_adjacent(6, 0) == false);

    std::ostringstream buf;
    auto action = [&](const auto& v)
    { buf << v << " "; };

    some.depth_first_search(0, action);
    REQUIRE(buf.str() == "0 1 3 2 5 4 6 ");
    buf.str("");

    some.breadth_first_search(0, action);
    REQUIRE(buf.str() == "0 1 3 4 2 5 6 ");
    buf.str("");

    auto sp = some.dijkstra(0);
    REQUIRE(sp.dist(0) == std::optional<int>(0));
    REQUIRE(sp.dist(1) == std::optional<int>(2));
    REQUIRE(sp.dist(2) == std::optional<int>(3));
    REQUIRE(sp.dist(3) == std::optional<int>(1));
    REQUIRE(sp.dist(4) == std::optional<int>(3));
    REQUIRE(sp.dist(5) == std::optional<int>(6));
    REQUIRE(sp.dist(6) == std::optional<int>(5));
    REQUIRE(sp.prev(0) == std::nullopt);
    REQUIRE(sp.prev(1) == std::optional<int>(0));
    REQUIRE(sp.prev(2) == std::optional<int>(3));
    REQUIRE(sp.prev(3) == std::optional<int>(0));
    REQUIRE(sp.prev(4) == std::optional<int>(3));
    REQUIRE(sp.prev(5) == std::optional<int>(6));
    REQUIRE(sp.prev(6) == std::optional<int>(3));

    // Print
    REQUIRE(empty.to_ascii() == "Graph {\n  type: directed\n  vertices: 0\n  edges: 0\n}");

    REQUIRE(some.to_ascii() ==
            "Graph {\n"
            "  type: directed\n"
            "  vertices: 7\n"
            "  edges: 12\n"
            "  0: [1(w=2), 3(w=1)]\n"
            "  1: [3(w=3), 4(w=10)]\n"
            "  2: [0(w=4), 5(w=5)]\n"
            "  3: [2(w=2), 4(w=2), 5(w=8), 6(w=4)]\n"
            "  4: [6(w=6)]\n"
            "  5: []\n"
            "  6: [5(w=1)]\n"
            "}");

    REQUIRE(some.to_dot() ==
            "digraph G {\n"
            "  \"0\";\n"
            "  \"1\";\n"
            "  \"2\";\n"
            "  \"3\";\n"
            "  \"4\";\n"
            "  \"5\";\n"
            "  \"6\";\n"
            "  \"0\" -> \"1\" [label=\"2\"];\n"
            "  \"0\" -> \"3\" [label=\"1\"];\n"
            "  \"1\" -> \"3\" [label=\"3\"];\n"
            "  \"1\" -> \"4\" [label=\"10\"];\n"
            "  \"2\" -> \"0\" [label=\"4\"];\n"
            "  \"2\" -> \"5\" [label=\"5\"];\n"
            "  \"3\" -> \"2\" [label=\"2\"];\n"
            "  \"3\" -> \"4\" [label=\"2\"];\n"
            "  \"3\" -> \"5\" [label=\"8\"];\n"
            "  \"3\" -> \"6\" [label=\"4\"];\n"
            "  \"4\" -> \"6\" [label=\"6\"];\n"
            "  \"6\" -> \"5\" [label=\"1\"];\n"
            "}");

    // Manipulation
    some.clear();
    REQUIRE(some == empty);
    some.clear(); // double clear
    REQUIRE(some == empty);
}

TEMPLATE_TEST_CASE("Undirected graph print and dot", "[graph]", (MatrixGraph<int, int, false>), (ListGraph<int, int, false>))
{
    using Graph = TestType;

    Graph g = {0, 1, 2, 3};
    g.link(0, 1, 2);
    g.link(1, 2, 3);
    g.link(2, 3, 4);

    REQUIRE(g.to_ascii() ==
            "Graph {\n"
            "  type: undirected\n"
            "  vertices: 4\n"
            "  edges: 3\n"
            "  0 -- 1(w=2)\n"
            "  1 -- 2(w=3)\n"
            "  2 -- 3(w=4)\n"
            "}");

    REQUIRE(g.to_dot() ==
            "graph G {\n"
            "  \"0\";\n"
            "  \"1\";\n"
            "  \"2\";\n"
            "  \"3\";\n"
            "  \"0\" -- \"1\" [label=\"2\"];\n"
            "  \"1\" -- \"2\" [label=\"3\"];\n"
            "  \"2\" -- \"3\" [label=\"4\"];\n"
            "}");

    // Print via operator<<
    std::ostringstream oss;

    oss << g;
    REQUIRE(oss.str() == "Graph(0, 1, 2, 3)");
    oss.str("");
}
