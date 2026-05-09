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
    requires detail::HashKey<V, std::hash<V>, std::equal_to<V>>
class MatrixGraph : public Graph<V, E, Directed>
{
protected:
    using detail::Container::INIT_CAPACITY;
    using detail::Container::MAX_CAPACITY;

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
        : size_(that.size_)
        , capacity_(that.capacity_)
        , matrix_(that.matrix_)
        , vertex_to_idx_(std::move(that.vertex_to_idx_))
        , idx_to_vertex_(std::move(that.idx_to_vertex_))
    {
        that.size_ = 0;
        that.capacity_ = INIT_CAPACITY;
        that.matrix_ = new std::optional<E>[that.capacity_ * that.capacity_]();
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
        auto visited = std::make_unique<bool[]>(size_);
        auto dist = std::make_unique<std::optional<E>[]>(size_);
        auto path = std::make_unique<int[]>(size_);

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

    /*
     * Print
     */

    /// Print the graph.
    friend std::ostream& operator<<(std::ostream& os, const MatrixGraph& graph)
    {
        int edges = 0;
        for (int i = 0; i < graph.size_; ++i)
        {
            for (int j = (Directed ? 0 : i); j < graph.size_; ++j)
            {
                if (graph.at(i, j).has_value())
                {
                    ++edges;
                }
            }
        }

        os << "Graph {\n"
           << "  type: " << (Directed ? "directed" : "undirected") << "\n"
           << "  vertices: " << graph.size_ << "\n"
           << "  edges: " << edges << "\n";

        if constexpr (Directed)
        {
            for (int i = 0; i < graph.size_; ++i)
            {
                os << "  " << graph.idx_to_vertex_[i] << ": [";

                bool first = true;
                for (int j = 0; j < graph.size_; ++j)
                {
                    if (!graph.at(i, j).has_value())
                    {
                        continue;
                    }

                    if (!first)
                    {
                        os << ", ";
                    }
                    first = false;
                    os << graph.idx_to_vertex_[j] << "(w=" << graph.at(i, j).value() << ")";
                }

                os << "]\n";
            }
        }
        else
        {
            for (int i = 0; i < graph.size_; ++i)
            {
                for (int j = i; j < graph.size_; ++j)
                {
                    if (graph.at(i, j).has_value())
                    {
                        os << "  " << graph.idx_to_vertex_[i] << " -- " << graph.idx_to_vertex_[j]
                           << "(w=" << graph.at(i, j).value() << ")\n";
                    }
                }
            }
        }

        return os << "}";
    }

    /// Export the graph as Graphviz DOT.
    std::string to_dot() const override
    {
        auto quote = [](const auto& value)
        {
            std::ostringstream oss;
            oss << '"' << value << '"';
            return oss.str();
        };

        std::ostringstream oss;
        oss << (Directed ? "digraph G {\n" : "graph G {\n");

        for (int i = 0; i < size_; ++i)
        {
            oss << "  " << quote(idx_to_vertex_[i]) << ";\n";
        }

        const char* connector = Directed ? " -> " : " -- ";
        for (int i = 0; i < size_; ++i)
        {
            for (int j = (Directed ? 0 : i); j < size_; ++j)
            {
                if (at(i, j).has_value())
                {
                    oss << "  " << quote(idx_to_vertex_[i]) << connector << quote(idx_to_vertex_[j])
                        << " [label=\"" << at(i, j).value() << "\"];\n";
                }
            }
        }

        return oss << "}", oss.str();
    }
};

} // namespace hellods

#endif // MATRIXGRAPH_HPP
