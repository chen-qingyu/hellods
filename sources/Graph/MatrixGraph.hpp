/**
 * @file MatrixGraph.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Graph implemented by adjacency matrix. Default is directed graph.
 * @date 2022.01.29
 */

#ifndef MATRIXGRAPH_HPP
#define MATRIXGRAPH_HPP

#include "../detail.hpp"

#include "../Queue/ArrayQueue.hpp" // for breadth_first_search()

namespace hellods
{

/// Graph implemented by adjacency matrix. Default is directed graph.
template <bool Directed = true>
class MatrixGraph : public detail::Container
{
public:
    /// Vertex type.
    using V = int;

    /// Edge type.
    using E = int;

    /// A value of edge type indicating that this edge does not exist.
    static const E NO_EDGE = INT_MAX;

protected:
    // Number of elements.
    int size_;

    // Adjacency matrix.
    E** matrix_;

    // Free matrix memory.
    void free_matrix()
    {
        if (matrix_ != nullptr)
        {
            for (int i = 0; i < size_; i++)
            {
                delete[] matrix_[i];
            }
            delete[] matrix_;
        }
    }

    // Depth-first search helper.
    template <typename F>
    void dfs(const V& start, const F& action, std::vector<bool>& visited) const
    {
        action(start);
        visited[start] = true;

        for (V v = 0; v < size_; v++)
        {
            if (is_adjacent(start, v) && !visited[v])
            {
                dfs(v, action, visited);
            }
        }
    }

    // Finds the vertex with the smallest distance in an unaccessed set of vertices.
    V find_closest(std::vector<V>& dist, std::vector<bool>& visited) const
    {
        V min_v;
        E min_dist = NO_EDGE;

        for (V v = 0; v < size_; v++)
        {
            if (!visited[v] && dist[v] < min_dist)
            {
                min_dist = dist[v];
                min_v = v;
            }
        }

        return min_dist < NO_EDGE ? min_v : -1;
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty graph.
    MatrixGraph()
        : size_(0)
        , matrix_(nullptr)
    {
    }

    /// Create a graph with n vertices.
    MatrixGraph(int n)
        : MatrixGraph()
    {
        set_vertex_number(n);
    }

    /// Destroy the graph object.
    ~MatrixGraph()
    {
        free_matrix();
    }

    /*
     * Comparison
     */

    /// Check whether two graphs are equal.
    bool operator==(const MatrixGraph& that) const
    {
        if (size() != that.size())
        {
            return false;
        }

        for (V v1 = 0; v1 < size_; v1++)
        {
            for (V v2 = 0; v2 < size_; v2++)
            {
                if (matrix_[v1][v2] != that.matrix_[v1][v2])
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

    /// Get the number of elements.
    int size() const override
    {
        return size_;
    }

    /// Return the distance from vertex `from` to vertex `to`.
    E distance(const V& from, const V& to) const
    {
        detail::check_bounds(from, 0, size_);
        detail::check_bounds(to, 0, size_);

        return matrix_[from][to];
    }

    /// Determine if vertex `from` has a link to vertex `to`.
    bool is_adjacent(const V& from, const V& to) const
    {
        detail::check_bounds(from, 0, size_);
        detail::check_bounds(to, 0, size_);

        return matrix_[from][to] != NO_EDGE;
    }

    /// Depth-first search graph.
    template <typename F>
    void depth_first_search(const V& start, const F& action) const
    {
        detail::check_bounds(start, 0, size_);

        auto visited = std::vector<bool>(size_, false);

        dfs(start, action, visited);
    }

    /// Breadth-first search graph.
    template <typename F>
    void breadth_first_search(const V& start, const F& action) const
    {
        detail::check_bounds(start, 0, size_);

        auto visited = std::vector<bool>(size_, false);

        action(start);
        visited[start] = true;

        ArrayQueue<V> queue;
        queue.enqueue(start);
        while (!queue.is_empty())
        {
            V v1 = queue.dequeue();
            for (V v2 = 0; v2 < size_; v2++)
            {
                if (!visited[v2] && is_adjacent(v1, v2))
                {
                    action(v2);
                    visited[v2] = true;
                    queue.enqueue(v2);
                }
            }
        }
    }

    /// The Dijkstra algorithm on the graph. Return distance and path.
    std::pair<std::vector<E>, std::vector<V>> dijkstra(const V& start) const
    {
        detail::check_bounds(start, 0, size_);

        // init state
        auto visited = std::vector<bool>(size_, false);
        std::vector<V> dist(size_);
        std::vector<V> path(size_);
        for (V v = 0; v < size_; v++)
        {
            dist[v] = matrix_[start][v];
            path[v] = dist[v] < NO_EDGE ? start : -1;
        }

        dist[start] = 0;
        visited[start] = true;

        while (true)
        {
            V v1 = find_closest(dist, visited);
            if (v1 == -1)
            {
                break;
            }
            visited[v1] = true;
            for (V v2 = 0; v2 < size_; v2++)
            {
                if (!visited[v2] && matrix_[v1][v2] < NO_EDGE)
                {
                    if (matrix_[v1][v2] < 0)
                    {
                        throw std::runtime_error("Error: Cannot apply Dijkstra algorithm with a negative weighted egde.");
                    }
                    if (dist[v1] + matrix_[v1][v2] < dist[v2])
                    {
                        dist[v2] = dist[v1] + matrix_[v1][v2];
                        path[v2] = v1;
                    }
                }
            }
        }

        return {dist, path};
    }

    /*
     * Manipulation
     */

    /// Set the number of vertices in the graph.
    void set_vertex_number(int n)
    {
        free_matrix();

        size_ = n;

        matrix_ = new E*[n];
        for (int i = 0; i < n; i++)
        {
            matrix_[i] = new E[n];
        }

        for (V v1 = 0; v1 < n; v1++)
        {
            for (V v2 = 0; v2 < n; v2++)
            {
                matrix_[v1][v2] = NO_EDGE;
            }
        }
    }

    /// Link vertex `from` and vertex `to` with `weight`.
    void link(const V& from, const V& to, const E& weight)
    {
        matrix_[from][to] = weight;
        if constexpr (Directed == false)
        {
            matrix_[to][from] = weight;
        }
    }

    /// Disconnect the link from vertex `from` to vertex `to`.
    void unlink(const V& from, const V& to)
    {
        matrix_[from][to] = NO_EDGE;
        if constexpr (Directed == false)
        {
            matrix_[to][from] = NO_EDGE;
        }
    }

    /// Clear this graph.
    void clear()
    {
        if (size_ != 0)
        {
            free_matrix();
            size_ = 0;
            matrix_ = nullptr;
        }
    }

    /*
     * Print
     */

    /// Print the graph.
    friend std::ostream& operator<<(std::ostream& os, const MatrixGraph& graph)
    {
        os << "Graph(\n";
        for (V v1 = 0; v1 < graph.size(); v1++)
        {
            os << v1 << " -> ";
            for (V v2 = 0; v2 < graph.size(); v2++)
            {
                if (graph.is_adjacent(v1, v2))
                {
                    os << v2 << "(" << graph.distance(v1, v2) << ") ";
                }
            }
            os << "\n";
        }
        return os << ")";
    }
};

} // namespace hellods

#endif // MATRIXGRAPH_HPP
