/**
 * @file Graph.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract graph interface.
 * @date 2026.05.09
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>

#include "../Map/HashMap.hpp"

namespace hellods
{

/// Abstract graph interface. Default is directed graph.
template <typename V = int, typename E = int, bool Directed = true>
    requires detail::HashKey<V, std::hash<V>, std::equal_to<V>>
class Graph : public detail::Container
{
public:
    /// Result of the Dijkstra shortest path algorithm.
    /// Query by vertex: sp.dist(v), sp.prev(v).
    struct ShortestPath
    {
        HashMap<V, std::optional<E>> dist_;
        HashMap<V, std::optional<V>> prev_;

        /// Shortest distance from start to vertex v (nullopt if unreachable).
        std::optional<E> dist(const V& v) const
        {
            auto it = dist_.find(v);
            return it == dist_.end() ? std::nullopt : it->value();
        }

        /// Predecessor of vertex v on the shortest path (nullopt if start or unreachable).
        std::optional<V> prev(const V& v) const
        {
            auto it = prev_.find(v);
            return it == prev_.end() ? std::nullopt : it->value();
        }
    };

    /*
     * Lifecycle
     */

    /// Virtual destructor.
    virtual ~Graph() = default;

    /*
     * Examination
     */

    /// Return the distance from vertex `from` to vertex `to`, or nullopt if no edge exists.
    virtual std::optional<E> distance(const V& from, const V& to) const = 0;

    /// Determine if vertex `from` has a link to vertex `to`.
    bool is_adjacent(const V& from, const V& to) const
    {
        return distance(from, to).has_value();
    }

    /// Depth-first search graph.
    virtual void depth_first_search(const V& start, const std::function<void(const V&)>& action) const = 0;

    /// Breadth-first search graph.
    virtual void breadth_first_search(const V& start, const std::function<void(const V&)>& action) const = 0;

    /// The Dijkstra algorithm on the graph. Return shortest paths from start.
    virtual ShortestPath dijkstra(const V& start) const = 0;

    /// Export the graph as Graphviz DOT.
    virtual std::string to_dot() const = 0;

    /*
     * Manipulation
     */

    /// Add a vertex. Return whether it was newly inserted (false if already exists).
    virtual bool add_vertex(const V& vertex) = 0;

    /// Add multiple vertices at once.
    virtual void add_vertices(std::initializer_list<V> vertices)
    {
        for (const auto& vertex : vertices)
        {
            add_vertex(vertex);
        }
    }

    /// Link vertex `from` and vertex `to` with `weight`.
    virtual void link(const V& from, const V& to, const E& weight) = 0;

    /// Disconnect the link from vertex `from` to vertex `to`.
    virtual void unlink(const V& from, const V& to) = 0;

    /// Remove all of the elements from the graph.
    virtual void clear() = 0;
};

} // namespace hellods

#endif // GRAPH_HPP