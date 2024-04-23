#include "tool.hpp"

#include "../sources/Graph/MatrixGraph.hpp"

using namespace hellods;

TEST_CASE("MatrixGraph")
{
    // Constructor / Destructor
    MatrixGraph empty;
    MatrixGraph some(7);

    // Comparison
    REQUIRE(empty == MatrixGraph());
    REQUIRE(some == MatrixGraph(7));
    REQUIRE(empty != some);
    REQUIRE(some != MatrixGraph(6));

    // Manipulation & Comparison
    MatrixGraph g1(2);
    MatrixGraph g2(2);
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

    REQUIRE_THROWS_MATCHES(empty.is_adjacent(0, 1), std::runtime_error, Message("Error: Index out of range."));
    REQUIRE(some.is_adjacent(0, 1) == false);

    REQUIRE_THROWS_MATCHES(empty.distance(0, 1), std::runtime_error, Message("Error: Index out of range."));
    REQUIRE(some.distance(0, 1) == MatrixGraph<>::NO_EDGE);

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
    REQUIRE(some.distance(0, 1) == 2);
    REQUIRE(some.distance(0, 6) == MatrixGraph<>::NO_EDGE);

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

    auto [dist, path] = some.dijkstra(0);
    REQUIRE(dist == std::vector<MatrixGraph<>::E>{0, 2, 3, 1, 3, 6, 5});
    REQUIRE(path == std::vector<MatrixGraph<>::V>{-1, 0, 3, 0, 3, 6, 3});

    // Print
    std::ostringstream oss;

    oss << empty;
    REQUIRE(oss.str() == "Graph(\n)");
    oss.str("");

    oss << some;
    REQUIRE(oss.str() == "\
Graph(\n\
0 -> 1(2) 3(1) \n\
1 -> 3(3) 4(10) \n\
2 -> 0(4) 5(5) \n\
3 -> 2(2) 4(2) 5(8) 6(4) \n\
4 -> 6(6) \n\
5 -> \n\
6 -> 5(1) \n\
)");
    oss.str("");

    // Manipulation
    some.clear();
    REQUIRE(some == empty);
    some.clear(); // double clear
    REQUIRE(some == empty);
}
