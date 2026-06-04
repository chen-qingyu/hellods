/**
 * @file UnionFind.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Union-find set (disjoint set) with path compression and union by rank.
 * @date 2026.06.03
 */

#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include "../List/ArrayList.hpp"
#include "../Map/HashMap.hpp"

namespace hellods
{

/// Union-find set (disjoint set) with path compression and union by rank.
///
/// Supports arbitrary element types via internal element-to-index mapping.
/// Elements are added dynamically with `add()`.
/// All operations run in near-constant O(α(N)) amortized time.
template <typename T>
class UnionFind : public detail::Container
{
protected:
    // Number of elements.
    int size_ = 0;

    // Parent pointer: parent_[i] is the parent of element i.
    // Roots point to themselves.
    ArrayList<int> parent_;

    // Rank (tree height upper bound): rank_[i] is the rank of the root i.
    ArrayList<int> rank_;

    // Element-to-index mapping.
    HashMap<T, int> map_;

    // Index-to-element inverse mapping (for returning representative).
    ArrayList<T> elements_;

    // Swap with another union-find set.
    void swap(UnionFind& that)
    {
        std::swap(size_, that.size_);
        std::swap(parent_, that.parent_);
        std::swap(rank_, that.rank_);
        std::swap(map_, that.map_);
        std::swap(elements_, that.elements_);
    }

    // Get the internal index of an element. Throws if not found.
    int index(const T& element) const
    {
        auto it = map_.find(element);
        if (it == map_.end())
        {
            throw std::runtime_error("Error: Element does not exist in the union-find set.");
        }
        return it->value();
    }

    // Non-const find: with path compression.
    int find_by_index(int x)
    {
        while (parent_[x] != x)
        {
            parent_[x] = parent_[parent_[x]];
            x = parent_[x];
        }
        return x;
    }

    // Const find: without path compression.
    int find_by_index(int x) const
    {
        while (parent_[x] != x)
        {
            x = parent_[x];
        }
        return x;
    }

public:
    /*
     * Lifecycle
     */

    /// Create an empty union-find set.
    UnionFind() = default;

    /// Create a union-find set from the given initializer list.
    UnionFind(std::initializer_list<T> il)
        : UnionFind()
    {
        for (const auto& elem : il)
        {
            add(elem);
        }
    }

    UnionFind(const UnionFind&) = default;
    UnionFind(UnionFind&&) = default;

    UnionFind& operator=(const UnionFind&) = default;
    UnionFind& operator=(UnionFind&&) = default;

    /*
     * Comparison
     */

    /// Check whether two union-find sets are structurally equal.
    bool operator==(const UnionFind& that) const
    {
        if (size_ != that.size_)
        {
            return false;
        }

        if (elements_ != that.elements_)
        {
            return false;
        }

        for (int i = 0; i < size_; ++i)
        {
            if (find_by_index(i) != that.find_by_index(i))
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const UnionFind& that) const
    {
        return !(*this == that);
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return size_;
    }

    /// Check if the union-find set contains the specified element.
    bool contains(const T& element) const
    {
        return map_.contains(element);
    }

    /// Find the representative element of the set containing `element`.
    /// Returns the representative element (root).
    /// Throws if `element` has not been added.
    const T& find(const T& element) const
    {
        return elements_[find_by_index(index(element))];
    }

    /// Check if elements `a` and `b` are in the same set.
    bool is_connected(const T& a, const T& b) const
    {
        return find_by_index(index(a)) == find_by_index(index(b));
    }

    /*
     * Manipulation
     */

    /// Add a new isolated element. Return true if newly inserted (false if already exists).
    bool add(const T& element)
    {
        if (map_.contains(element))
        {
            return false;
        }

        int idx = size_++;
        map_.insert(element, idx);
        elements_.append(element);
        parent_.append(idx);
        rank_.append(0);
        return true;
    }

    /// Merge the sets containing elements `a` and `b`.
    /// Uses union by rank. Returns true if the sets were distinct (a merge occurred).
    bool unite(const T& a, const T& b)
    {
        int ra = find_by_index(index(a));
        int rb = find_by_index(index(b));

        if (ra == rb)
        {
            return false;
        }

        // Union by rank: attach the shorter tree under the taller one.
        if (rank_[ra] < rank_[rb])
        {
            parent_[ra] = rb;
        }
        else if (rank_[ra] > rank_[rb])
        {
            parent_[rb] = ra;
        }
        else
        {
            parent_[rb] = ra;
            ++rank_[ra];
        }

        return true;
    }

    /// Remove all elements, resetting to empty state.
    void clear() override
    {
        size_ = 0;
        parent_.clear();
        rank_.clear();
        map_.clear();
        elements_.clear();
    }
};

} // namespace hellods

#endif // UNIONFIND_HPP
