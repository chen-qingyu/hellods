/**
 * @file ListGraph.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Graph implemented by adjacency list. Default is directed graph.
 * @date 2026.05.09
 */

#ifndef LISTGRAPH_HPP
#define LISTGRAPH_HPP

#include "Graph.hpp"

#include "../List/ArrayList.hpp"
#include "../Queue/ArrayQueue.hpp"

namespace hellods
{

/// Graph implemented by adjacency list. Default is directed graph.
template <typename V = int, typename E = int, bool Directed = true>
class ListGraph : public Graph<V, E, Directed>
{
protected:
    struct Edge
    {
        int to_;
        E weight_;

        bool operator==(const Edge&) const = default;
    };

    HashMap<V, int> vertex_to_idx_;
    ArrayList<V> idx_to_vertex_;
    ArrayList<ArrayList<Edge>> adjacency_;

    int index(const V& v) const
    {
        auto it = vertex_to_idx_.find(v);
        if (it == vertex_to_idx_.end())
        {
            throw std::runtime_error("Error: Vertex does not exist.");
        }
        return it->value();
    }

    void link_one_way(int from, int to, const E& weight)
    {
        auto& edges = adjacency_[from];
        for (int i = 0; i < edges.size(); ++i)
        {
            if (edges[i].to_ == to)
            {
                edges[i].weight_ = weight;
                return;
            }

            if (edges[i].to_ > to)
            {
                edges.insert(i, {to, weight});
                return;
            }
        }
        edges.append({to, weight});
    }

    void unlink_one_way(int from, int to)
    {
        auto& edges = adjacency_[from];
        for (int i = 0; i < edges.size(); ++i)
        {
            if (edges[i].to_ == to)
            {
                edges.remove(i);
                return;
            }
        }
    }

    template <typename F>
    void dfs(int start, const F& action, bool* visited) const
    {
        action(idx_to_vertex_[start]);
        visited[start] = true;

        const auto& edges = adjacency_[start];
        for (int i = 0; i < edges.size(); ++i)
        {
            int to = edges[i].to_;
            if (!visited[to])
            {
                dfs(to, action, visited);
            }
        }
    }

    // Iterate each unique edge with a callback (from, to, weight).
    template <typename F>
    void for_each_edge(F&& callback) const
    {
        for (int i = 0; i < adjacency_.size(); ++i)
        {
            const auto& edges = adjacency_[i];
            for (int j = 0; j < edges.size(); ++j)
            {
                if constexpr (Directed)
                {
                    callback(i, edges[j].to_, edges[j].weight_);
                }
                else if (i <= edges[j].to_)
                {
                    callback(i, edges[j].to_, edges[j].weight_);
                }
            }
        }
    }

public:
    using ShortestPath = typename Graph<V, E, Directed>::ShortestPath;
    using Iterator = typename Graph<V, E, Directed>::Iterator;

    /*
     * Lifecycle
     */

    /// Create an empty graph.
    ListGraph() = default;

    /// Create a graph with the given vertices.
    ListGraph(std::initializer_list<V> vs)
    {
        this->add_vertices(vs);
    }

    ListGraph(const ListGraph&) = default;
    ListGraph(ListGraph&&) = default;

    ListGraph& operator=(const ListGraph&) = default;
    ListGraph& operator=(ListGraph&&) = default;

    /*
     * Comparison
     */

    /// Check whether two graphs are equal.
    bool operator==(const ListGraph& that) const
    {
        if (idx_to_vertex_.size() != that.idx_to_vertex_.size())
        {
            return false;
        }

        for (int i = 0; i < idx_to_vertex_.size(); ++i)
        {
            if (idx_to_vertex_[i] != that.idx_to_vertex_[i] || adjacency_[i] != that.adjacency_[i])
            {
                return false;
            }
        }

        return true;
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first vertex of the graph.
    Iterator begin() const override
    {
        return idx_to_vertex_.begin();
    }

    /// Return an iterator to the vertex following the last vertex of the graph.
    Iterator end() const override
    {
        return idx_to_vertex_.end();
    }

    /*
     * Examination
     */

    /// Get the number of vertices.
    int size() const override
    {
        return idx_to_vertex_.size();
    }

    /// Return the distance from vertex `from` to vertex `to`, or nullopt if no edge exists.
    std::optional<E> distance(const V& from, const V& to) const override
    {
        int i = index(from);
        int j = index(to);

        const auto& edges = adjacency_[i];
        for (int k = 0; k < edges.size(); ++k)
        {
            if (edges[k].to_ == j)
            {
                return edges[k].weight_;
            }
        }
        return std::nullopt;
    }

    /// Depth-first search graph.
    void depth_first_search(const V& start, const std::function<void(const V&)>& action) const override
    {
        int start_idx = index(start);

        auto visited = std::make_unique<bool[]>(size());
        dfs(start_idx, action, visited.get());
    }

    /// Breadth-first search graph.
    void breadth_first_search(const V& start, const std::function<void(const V&)>& action) const override
    {
        int start_idx = index(start);

        auto visited = std::make_unique<bool[]>(size());

        action(idx_to_vertex_[start_idx]);
        visited[start_idx] = true;

        ArrayQueue<int> queue;
        queue.enqueue(start_idx);
        while (!queue.is_empty())
        {
            int from = queue.dequeue();
            const auto& edges = adjacency_[from];
            for (int i = 0; i < edges.size(); ++i)
            {
                int to = edges[i].to_;
                if (!visited[to])
                {
                    action(idx_to_vertex_[to]);
                    visited[to] = true;
                    queue.enqueue(to);
                }
            }
        }
    }

    /// The Dijkstra algorithm on the graph. Return shortest paths from start.
    ShortestPath dijkstra(const V& start) const override
    {
        int start_idx = index(start);

        for (int i = 0; i < adjacency_.size(); ++i)
        {
            const auto& edges = adjacency_[i];
            for (int j = 0; j < edges.size(); ++j)
            {
                if (edges[j].weight_ < E(0))
                {
                    throw std::runtime_error("Error: Cannot apply Dijkstra algorithm with a negative weighted edge.");
                }
            }
        }

        auto visited = std::make_unique<bool[]>(size());
        auto dist = std::make_unique<std::optional<E>[]>(size());
        auto path = std::make_unique<int[]>(size());

        for (int v = 0; v < size(); ++v)
        {
            dist[v] = std::nullopt;
            path[v] = -1;
        }

        const auto& start_edges = adjacency_[start_idx];
        for (int i = 0; i < start_edges.size(); ++i)
        {
            dist[start_edges[i].to_] = start_edges[i].weight_;
            path[start_edges[i].to_] = start_idx;
        }

        dist[start_idx] = E(0);
        visited[start_idx] = true;

        while (true)
        {
            int from = -1;
            for (int v = 0; v < size(); ++v)
            {
                if (!visited[v] && dist[v].has_value() && (from == -1 || dist[v].value() < dist[from].value()))
                {
                    from = v;
                }
            }

            if (from == -1)
            {
                break;
            }
            visited[from] = true;

            const auto& edges = adjacency_[from];
            for (int i = 0; i < edges.size(); ++i)
            {
                int to = edges[i].to_;
                E new_dist = dist[from].value() + edges[i].weight_;
                if (!visited[to] && (!dist[to].has_value() || new_dist < dist[to].value()))
                {
                    dist[to] = new_dist;
                    path[to] = from;
                }
            }
        }

        ShortestPath result;
        for (int i = 0; i < size(); ++i)
        {
            result.dist_.insert(idx_to_vertex_[i], dist[i]);
            if (path[i] != -1)
            {
                result.prev_.insert(idx_to_vertex_[i], idx_to_vertex_[path[i]]);
            }
        }

        return result;
    }

    /// Export the graph as ASCII art.
    std::string to_ascii() const override
    {
        if constexpr (detail::Printable<V> && detail::Printable<E>)
        {
            std::ostringstream oss;

            int edges = 0;
            for_each_edge([&](int, int, const E&)
                          { ++edges; });

            oss << "Graph {\n"
                << "  type: " << (Directed ? "directed" : "undirected") << "\n"
                << "  vertices: " << idx_to_vertex_.size() << "\n"
                << "  edges: " << edges << "\n";

            if constexpr (Directed)
            {
                for (int i = 0; i < idx_to_vertex_.size(); ++i)
                {
                    oss << "  " << idx_to_vertex_[i] << ": [";

                    const auto& edge_list = adjacency_[i];
                    for (int j = 0; j < edge_list.size(); ++j)
                    {
                        if (j != 0)
                        {
                            oss << ", ";
                        }
                        oss << idx_to_vertex_[edge_list[j].to_] << "(w=" << edge_list[j].weight_ << ")";
                    }

                    oss << "]\n";
                }
            }
            else
            {
                for_each_edge([&](int i, int j, const E& w)
                              { oss << "  " << idx_to_vertex_[i] << " -- " << idx_to_vertex_[j] << "(w=" << w << ")\n"; });
            }

            oss << "}";
            return oss.str();
        }

        throw std::runtime_error("Error: Graph export requires Printable vertices and weights.");
    }

    /// Export the graph as Graphviz DOT.
    std::string to_dot() const override
    {
        if constexpr (detail::Printable<V> && detail::Printable<E>)
        {
            auto quote = [](const auto& v)
            {
                std::ostringstream oss;
                oss << '"' << v << '"';
                return oss.str();
            };

            std::ostringstream oss;
            oss << (Directed ? "digraph G {\n" : "graph G {\n");

            for (int i = 0; i < idx_to_vertex_.size(); ++i)
            {
                oss << "  " << quote(idx_to_vertex_[i]) << ";\n";
            }

            const char* connector = Directed ? " -> " : " -- ";
            for_each_edge([&](int i, int j, const E& w)
                          { oss << "  " << quote(idx_to_vertex_[i]) << connector << quote(idx_to_vertex_[j])
                                << " [label=\"" << w << "\"];\n"; });

            oss << "}";
            return oss.str();
        }

        throw std::runtime_error("Error: Graph export requires Printable vertices and weights.");
    }

    /*
     * Manipulation
     */

    /// Add a vertex. Return whether it was newly inserted (false if already exists).
    bool add_vertex(const V& v) override
    {
        if (vertex_to_idx_.contains(v))
        {
            return false;
        }

        int idx = idx_to_vertex_.size();
        vertex_to_idx_.insert(v, idx);
        idx_to_vertex_.append(v);
        adjacency_.append({});
        return true;
    }

    /// Link vertex `from` and vertex `to` with `weight`.
    void link(const V& from, const V& to, const E& weight) override
    {
        int i = index(from);
        int j = index(to);

        link_one_way(i, j, weight);
        if constexpr (!Directed)
        {
            link_one_way(j, i, weight);
        }
    }

    /// Disconnect the link from vertex `from` to vertex `to`.
    void unlink(const V& from, const V& to) override
    {
        int i = index(from);
        int j = index(to);

        unlink_one_way(i, j);
        if constexpr (!Directed)
        {
            unlink_one_way(j, i);
        }
    }

    /// Clear this graph.
    void clear() override
    {
        vertex_to_idx_.clear();
        idx_to_vertex_.clear();
        adjacency_.clear();
    }
};

} // namespace hellods

#endif // LISTGRAPH_HPP