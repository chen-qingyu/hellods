/**
 * @file HashMap.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Hash map.
 * @date 2022.01.29
 *
 * @copyright Copyright (C) 2022
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "../common/Container.hpp"
#include "../common/utility.hpp"

namespace hellods
{

/// Hash map.
template <typename K, typename V, typename Hash = std::hash<K>, typename Eq = std::equal_to<K>>
class HashMap : public common::Container
{
private:
    // Hash map pair.
    struct Pair
    {
        // The pair of the key-value.
        std::pair<const K, V> pair_;

        // State of the key-value pair.
        bool full_;

        // For convenient.
        const K& key_ = pair_.first;
        V& value_ = pair_.second;
    };

private:
    // Initial capacity for hash map.
    static const int INIT_PRIME_CAPACITY = 7;

    // Maximum capacity for hash map.
    static const int MAX_PRIME_CAPACITY = 2147483629; // maximum prime number not exceeding INT_MAX

    // Available capacity.
    int capacity_;

    // Pointer to the pairs.
    Pair* data_;

public:
    /// Map iterator class.
    ///
    /// Walk the map in random order.
    ///
    /// Because the internal keys of the map have a fixed position,
    /// thus the iterator of the map does not support modification for key.
    class Iterator
    {
        friend class HashMap;

    protected:
        // Current data pointer.
        Pair* current_;

        // Begin of the buffer.
        Pair* buffer_begin_;

        // End of the buffer.
        Pair* buffer_end_;

        // Constructor.
        Iterator(Pair* current, Pair* begin, Pair* end)
            : current_(current)
            , buffer_begin_(begin)
            , buffer_end_(end)
        {
            while (current_ != buffer_end_ && !current_->full_)
            {
                ++current_;
            }
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::pair<const K, V>;
        using difference_type = int;
        using pointer = value_type*;
        using reference = value_type&;

        bool operator==(const Iterator& that) const
        {
            return current_ == that.current_;
        }

        bool operator!=(const Iterator& that) const
        {
            return !(*this == that);
        }

        std::pair<const K, V>& operator*() const
        {
            return current_->pair_;
        }

        std::pair<const K, V>* operator->() const
        {
            return &(operator*());
        }

        Iterator& operator++()
        {
            while (++current_ != buffer_end_ && !current_->full_)
            {
            }
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator it = *this;
            ++*this;
            return it;
        }

        Iterator& operator--()
        {
            while (--current_ != buffer_begin_ && !current_->full_)
            {
            }
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator it = *this;
            --*this;
            return it;
        }
    };

private:
    // Find the position for key.
    int find_pos(const K& key) const
    {
        int current_pos = Hash()(key) % capacity_;
        int new_pos = current_pos;
        int conflict_cnt = 0;

        while (data_[new_pos].full_ && !Eq()(data_[new_pos].key_, key))
        {
            if (++conflict_cnt % 2)
            {
                new_pos = current_pos + (conflict_cnt + 1) * (conflict_cnt + 1) / 4;
                if (new_pos >= capacity_)
                {
                    new_pos %= capacity_;
                }
            }
            else
            {
                new_pos = current_pos - conflict_cnt * conflict_cnt / 4;
                while (new_pos < 0)
                {
                    new_pos += capacity_;
                }
            }
        }

        return new_pos;
    }

    // Calculate the next prime that > n.
    static int next_prime(int n)
    {
        if (n < INIT_PRIME_CAPACITY)
        {
            return INIT_PRIME_CAPACITY;
        }

        if (n >= MAX_PRIME_CAPACITY)
        {
            return MAX_PRIME_CAPACITY;
        }

        // if n is even, let it odd, because prime > 2 is odd
        n |= 1;
        while (n < MAX_PRIME_CAPACITY)
        {
            n += 2;
            bool is_prime = true;
            for (int i = 2; i * i <= n; i++)
            {
                if (n % i == 0)
                {
                    is_prime = false;
                    break; // n is not prime, continue while loop
                }
            }
            if (is_prime)
            {
                break; // n is prime, return
            }
        }

        return n;
    }

    // Expand capacity and rehash.
    void expand_capacity()
    {
        int old_capacity = capacity_;
        Pair* old_data = data_;

        // expand to the next prime greater than twice the current capacity
        int new_capacity = next_prime(capacity_ * 2);

        // create new pairs
        Pair* new_data = new Pair[new_capacity];
        for (int i = 0; i < new_capacity; i++)
        {
            new_data[i].full_ = false;
        }

        // move elements (rehash)
        data_ = new_data;
        capacity_ = new_capacity;
        size_ = 0;
        for (int i = 0; i < old_capacity; i++)
        {
            if (old_data[i].full_)
            {
                insert(old_data[i].key_, old_data[i].value_);
            }
        }

        // free old pairs
        delete[] old_data;
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty map.
    HashMap()
        : common::Container(0)
        , capacity_(INIT_PRIME_CAPACITY)
        , data_(new Pair[capacity_])
    {
        for (int i = 0; i < capacity_; i++)
        {
            data_[i].full_ = false;
        }
    }

    /// Create a map based on the given initializer list.
    HashMap(const std::initializer_list<std::pair<const K, V>>& il)
        : HashMap()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            insert(it->first, it->second);
        }
    }

    /// Destroy the map object.
    ~HashMap()
    {
        delete[] data_;
    }

    /*
     * Comparison
     */

    /// Check whether two maps are equal.
    bool operator==(const HashMap& that) const
    {
        if (size_ != that.size_)
        {
            return false;
        }

        for (const auto& pair : *this)
        {
            auto it = that.find(pair.first);
            if (it == that.end() || pair.second != it->second)
            {
                return false;
            }
        }

        return true;
    }

    /// Check whether two maps are not equal.
    bool operator!=(const HashMap& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference of value for key if key is in the map, else throw exception.
    V& operator[](const K& key)
    {
        int pos = find_pos(key);

        if (!data_[pos].full_)
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }

        return data_[pos].value_;
    }

    /// Return the const reference of value for key if key is in the map, else throw exception.
    const V& operator[](const K& key) const
    {
        return const_cast<HashMap&>(*this)[key];
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the map.
    Iterator begin() const
    {
        return Iterator(data_, data_, data_ + capacity_);
    }

    /// Return an iterator to the element following the last element of the map.
    Iterator end() const
    {
        return Iterator(data_ + capacity_, data_, data_ + capacity_);
    }

    /*
     * Examination
     */

    /// Return an iterator to the first occurrence of the specified key, or end() if the map does not contains the key.
    Iterator find(const K& key) const
    {
        int pos = find_pos(key);
        return data_[pos].full_ ? Iterator(data_ + pos, data_, data_ + capacity_) : end();
    }

    /// Determine whether a key is in the map.
    bool contains(const K& key) const
    {
        return data_[find_pos(key)].full_;
    }

    /*
     * Manipulation
     */

    /// Insert a new key-value pair into the map. Return whether the pair was newly inserted.
    bool insert(const K& key, const V& value)
    {
        common::check_full(size_, MAX_PRIME_CAPACITY >> 1);

        int pos = find_pos(key);

        if (data_[pos].full_)
        {
            return false;
        }

        data_[pos].full_ = true;
        const_cast<K&>(data_[pos].key_) = key;
        data_[pos].value_ = value;

        size_++;

        // expand capacity when the loading factor is too large (> 0.5)
        if (size_ > (capacity_ >> 1))
        {
            expand_capacity();
        }
        return true;
    }

    /// Remove the key-value pair corresponding to the key in the map. Return whether such a key was present.
    bool remove(const K& key)
    {
        int pos = find_pos(key);

        if (!data_[pos].full_)
        {
            return false;
        }

        data_[pos].full_ = false;
        size_--;
        return true;
    }

    /// Remove all of the elements from the map.
    void clear()
    {
        if (size_ != 0)
        {
            for (int i = 0; i < capacity_; ++i)
            {
                data_[i].full_ = false;
            }
            size_ = 0;
        }
    }

    /*
     * Print
     */

    /// Print the map.
    friend std::ostream& operator<<(std::ostream& os, const HashMap& map)
    {
        return common::print(os, map, "Map");
    }
};

} // namespace hellods

#endif // HASHMAP_HPP
