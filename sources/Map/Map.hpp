/**
 * @file Map.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract map interface.
 * @date 2026.05.10
 */

#ifndef MAP_HPP
#define MAP_HPP

#include "../detail.hpp"

namespace hellods
{

/// Abstract map interface.
template <typename K, typename V>
class Map : public detail::Container
{
public:
    using Entry = detail::MapEntry<K, V>;

    /// Iterator type — keys are read-only, values are mutable through iterators.
    using Iterator = detail::BasicIterator<Entry, false, std::bidirectional_iterator_tag>;
    using ConstIterator = detail::BasicIterator<Entry, true, std::bidirectional_iterator_tag>;

    /*
     * Lifecycle
     */

    /// Virtual destructor.
    virtual ~Map() = default;

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the map.
    virtual Iterator begin() = 0;

    /// Return a const iterator to the first element of the map.
    virtual ConstIterator begin() const = 0;

    /// Return an iterator to the element following the last element of the map.
    virtual Iterator end() = 0;

    /// Return a const iterator to the element following the last element of the map.
    virtual ConstIterator end() const = 0;

    /*
     * Access
     */

    /// Return the reference of value for key if key is in the map, else throw exception.
    virtual V& operator[](const K& key) = 0;

    /// Return the const reference of value for key if key is in the map, else throw exception.
    virtual const V& operator[](const K& key) const = 0;

    /*
     * Search
     */

    /// Return an iterator to the first occurrence of the specified key, or end() if the map does not contain the key.
    virtual Iterator find(const K& key) = 0;

    /// Return a const iterator to the first occurrence of the specified key, or end() if the map does not contain the key.
    virtual ConstIterator find(const K& key) const = 0;

    /// Check if the map contains the specified key.
    virtual bool contains(const K& key) const
    {
        return find(key) != end();
    }

    /*
     * Manipulation
     */

    /// Insert a new key-value pair into the map. Return whether the pair was newly inserted.
    virtual bool insert(const K& key, const V& value) = 0;

    /// Remove the key-value pair corresponding to the key in the map. Return whether such a key was present.
    virtual bool remove(const K& key) = 0;

    /// Remove all of the elements from the map.
    virtual void clear() = 0;
};

} // namespace hellods

#endif // MAP_HPP
