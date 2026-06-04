/**
 * @file MatrixGraph.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Graph implemented by adjacency matrix. Default is directed graph.
 * @date 2022.01.29
 */

#ifndef MATRIXGRAPH_HPP
#define MATRIXGRAPH_HPP

#include "Graph.hpp"

#include "../List/ArrayList.hpp"
#include "../Queue/ArrayQueue.hpp"

namespace hellods
{

/// Graph implemented by adjacency matrix. Default is directed graph.
template <typename V = int, typename E = int, bool Directed = true>
class MatrixGraph : public Graph<V, E, Directed>
{
protected:
    using Graph<V, E, Directed>::INIT_CAPACITY;
    using Graph<V, E, Directed>::MAX_CAPACITY;

    // Number of vertices.
    int size_;

    // Allocated capacity (matrix is capacity_ x capacity_ flat array).
    int capacity_;

    // Adjacency matrix: flat array of size capacity_ * capacity_.
    // Entry (i, j) is at matrix_[i * capacity_ + j].
    std::optional<E>* matrix_;

    // Map from vertex to internal index.
    HashMap<V, int> vertex_to_idx_;

    // Inverse map: internal index to vertex.
    ArrayList<V> idx_to_vertex_;

    // Get internal index of a vertex, throws if not found.
    int index(const V& v) const
    {
        auto it = vertex_to_idx_.find(v);
        if (it == vertex_to_idx_.end())
        {
            throw std::runtime_error("Error: Vertex does not exist.");
        }
        return it->value();
    }

    // Access matrix entry by internal indices.
    std::optional<E>& at(int i, int j)
    {
        return matrix_[i * capacity_ + j];
    }

    const std::optional<E>& at(int i, int j) const
    {
        return matrix_[i * capacity_ + j];
    }

    // Expand capacity (doubles). Active region (size_ x size_) is preserved.
    void expand_capacity()
    {
        int old_cap = capacity_;
        capacity_ = (capacity_ < MAX_CAPACITY / 2) ? capacity_ * 2 : MAX_CAPACITY;

        auto* new_matrix = new std::optional<E>[capacity_ * capacity_]();

        // Copy active region
        for (int i = 0; i < size_; i++)
        {
            for (int j = 0; j < size_; j++)
            {
                new_matrix[i * capacity_ + j] = std::move(matrix_[i * old_cap + j]);
            }
        }

        delete[] matrix_;
        matrix_ = new_matrix;
    }

    // Swap with another graph.
    void swap(MatrixGraph& that)
    {
        std::swap(size_, that.size_);
        std::swap(capacity_, that.capacity_);
        std::swap(matrix_, that.matrix_);
        std::swap(vertex_to_idx_, that.vertex_to_idx_);
        std::swap(idx_to_vertex_, that.idx_to_vertex_);
    }

    // Depth-first search helper (internal indices).
    template <typename F>
    void dfs(int start, const F& action, bool* visited) const
    {
        action(idx_to_vertex_[start]);
        visited[start] = true;

        for (int v = 0; v < size_; v++)
        {
            if (at(start, v).has_value() && !visited[v])
            {
                dfs(v, action, visited);
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
    MatrixGraph()
        : size_(0)
        , capacity_(INIT_CAPACITY)
        , matrix_(new std::optional<E>[capacity_ * capacity_]())
        , vertex_to_idx_()
        , idx_to_vertex_()
    {
    }

    /// Create a graph with the given vertices.
    MatrixGraph(std::initializer_list<V> vs)
        : size_(0)
        , capacity_(std::max(INIT_CAPACITY, static_cast<int>(vs.size())))
        , matrix_(new std::optional<E>[capacity_ * capacity_]())
        , vertex_to_idx_()
        , idx_to_vertex_()
    {
        this->add_vertices(vs);
    }

    /// Copy constructor.
    MatrixGraph(const MatrixGraph& that)
        : size_(that.size_)
        , capacity_(that.capacity_)
        , matrix_(new std::optional<E>[capacity_ * capacity_]())
        , vertex_to_idx_(that.vertex_to_idx_)
        , idx_to_vertex_(that.idx_to_vertex_)
    {
        for (int i = 0; i < capacity_ * capacity_; i++)
        {
            matrix_[i] = that.matrix_[i];
        }
    }

    /// Move constructor.
    MatrixGraph(MatrixGraph&& that)
        : MatrixGraph()
    {
        swap(that);
    }

    MatrixGraph& operator=(MatrixGraph that)
    {
        swap(that);
        return *this;
    }

    /// Destroy the graph object.
    ~MatrixGraph()
    {
        delete[] matrix_;
    }

    /*
     * Comparison
     */

    /// Check whether two graphs are equal.
    bool operator==(const MatrixGraph& that) const
    {
        if (size_ != that.size_ || idx_to_vertex_ != that.idx_to_vertex_)
        {
            return false;
        }

        for (int i = 0; i < size_; ++i)
        {
            for (int j = 0; j < size_; ++j)
            {
                if (at(i, j) != that.at(i, j))
                {
                    return false;
                }
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
        return size_;
    }

    /// Return the distance from vertex `from` to vertex `to`, or nullopt if no edge exists.
    std::optional<E> distance(const V& from, const V& to) const override
    {
        return at(index(from), index(to));
    }

    /// Return the number of edges in the graph.
    int edge_count() const override
    {
        int count = 0;
        for_each_edge([&](const V&, const V&, const E&)
                      { ++count; });
        return count;
    }

    /// Invoke `action(from, to, weight)` for every edge in the graph.
    void for_each_edge(const std::function<void(const V&, const V&, const E&)>& action) const override
    {
        for (int i = 0; i < size_; ++i)
        {
            for (int j = (Directed ? 0 : i); j < size_; ++j)
            {
                if (at(i, j).has_value())
                {
                    action(idx_to_vertex_[i], idx_to_vertex_[j], at(i, j).value());
                }
            }
        }
    }

    /// Depth-first search graph.
    void depth_first_search(const V& start, const std::function<void(const V&)>& action) const override
    {
        int start_idx = index(start);

        auto visited = std::make_unique<bool[]>(size_);
        dfs(start_idx, action, visited.get());
    }

    /// Breadth-first search graph.
    void breadth_first_search(const V& start, const std::function<void(const V&)>& action) const override
    {
        int start_idx = index(start);

        auto visited = std::make_unique<bool[]>(size_);

        action(idx_to_vertex_[start_idx]);
        visited[start_idx] = true;

        ArrayQueue<int> queue;
        queue.enqueue(start_idx);
        while (!queue.is_empty())
        {
            int v1 = queue.dequeue();
            for (int v2 = 0; v2 < size_; v2++)
            {
                if (!visited[v2] && at(v1, v2).has_value())
                {
                    action(idx_to_vertex_[v2]);
                    visited[v2] = true;
                    queue.enqueue(v2);
                }
            }
        }
    }

    /// The Dijkstra algorithm on the graph. Return shortest paths from start.
    ShortestPath dijkstra(const V& start) const override
    {
        int start_idx = index(start);

        // Check for negative weights
        for (int i = 0; i < size_; ++i)
        {
            for (int j = 0; j < size_; ++j)
            {
                if (at(i, j).has_value() && at(i, j).value() < E(0))
                {
                    throw std::runtime_error("Error: Cannot apply Dijkstra algorithm with a negative weighted edge.");
                }
            }
        }

        // Init state
        ArrayList<bool> visited(size_);
        ArrayList<std::optional<E>> dist(size_);
        ArrayList<int> path(size_);

        for (int v = 0; v < size_; v++)
        {
            dist[v] = at(start_idx, v); // may be nullopt
            path[v] = dist[v].has_value() ? start_idx : -1;
        }

        dist[start_idx] = E(0);
        visited[start_idx] = true;

        while (true)
        {
            int v1 = -1;
            for (int v = 0; v < size_; ++v)
            {
                if (!visited[v] && dist[v].has_value() && (v1 == -1 || dist[v].value() < dist[v1].value()))
                {
                    v1 = v;
                }
            }

            if (v1 == -1)
            {
                break;
            }
            visited[v1] = true;

            for (int v2 = 0; v2 < size_; v2++)
            {
                if (!visited[v2] && at(v1, v2).has_value())
                {
                    E new_dist = dist[v1].value() + at(v1, v2).value();
                    if (!dist[v2].has_value() || new_dist < dist[v2].value())
                    {
                        dist[v2] = new_dist;
                        path[v2] = v1;
                    }
                }
            }
        }

        ShortestPath result;
        for (int i = 0; i < size_; ++i)
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

            int edges = edge_count();

            oss << "Graph {\n"
                << "  type: " << (Directed ? "directed" : "undirected") << "\n"
                << "  vertices: " << size_ << "\n"
                << "  edges: " << edges << "\n";

            if constexpr (Directed)
            {
                for (int i = 0; i < size_; ++i)
                {
                    oss << "  " << idx_to_vertex_[i] << ": [";

                    bool first = true;
                    for (int j = 0; j < size_; ++j)
                    {
                        if (!at(i, j).has_value())
                        {
                            continue;
                        }

                        if (!first)
                        {
                            oss << ", ";
                        }
                        first = false;
                        oss << idx_to_vertex_[j] << "(w=" << at(i, j).value() << ")";
                    }

                    oss << "]\n";
                }
            }
            else
            {
                for_each_edge([&](const V& f, const V& t, const E& w)
                              { oss << "  " << f << " -- " << t << "(w=" << w << ")\n"; });
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

            for (int i = 0; i < size_; ++i)
            {
                oss << "  " << quote(idx_to_vertex_[i]) << ";\n";
            }

            const char* connector = Directed ? " -> " : " -- ";
            for_each_edge([&](const V& f, const V& t, const E& w)
                          { oss << "  " << quote(f) << connector << quote(t) << " [label=\"" << w << "\"];\n"; });

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

        if (size_ == capacity_)
        {
            expand_capacity();
        }

        int idx = size_;
        vertex_to_idx_.insert(v, idx);
        idx_to_vertex_.append(v);
        size_++;

        return true;
    }

    /// Link vertex `from` and vertex `to` with `weight`.
    void link(const V& from, const V& to, const E& weight) override
    {
        int i = index(from);
        int j = index(to);

        at(i, j) = weight;
        if constexpr (!Directed)
        {
            at(j, i) = weight;
        }
    }

    /// Disconnect the link from vertex `from` to vertex `to`.
    void unlink(const V& from, const V& to) override
    {
        int i = index(from);
        int j = index(to);

        at(i, j).reset();
        if constexpr (!Directed)
        {
            at(j, i).reset();
        }
    }

    /// Clear this graph.
    void clear() override
    {
        if (size_ != 0)
        {
            size_ = 0;
            capacity_ = INIT_CAPACITY;
            delete[] matrix_;
            matrix_ = new std::optional<E>[capacity_ * capacity_]();
            vertex_to_idx_.clear();
            idx_to_vertex_.clear();
        }
    }
};

} // namespace hellods

#endif // MATRIXGRAPH_HPP
