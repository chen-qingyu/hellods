/**
 * @file HashMap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Hash map.
 * @date 2022.01.29
 */

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "Map.hpp"

namespace hellods
{

/// Hash map.
template <typename K, typename V, typename Hash = std::hash<K>, typename Eq = std::equal_to<K>>
class HashMap : public Map<K, V>
{
protected:
    // State of the slot: 0 = empty, 1 = occupied, 2 = deleted
    enum State
    {
        EMPTY = 0,
        OCCUPIED = 1,
        DELETED = 2
    };

    using Slot = std::pair<detail::MapEntry<K, V>, State>;

    // Initial capacity for hash map.
    static const int INIT_PRIME_CAPACITY = 7;

    // Maximum capacity for hash map.
    static const int MAX_PRIME_CAPACITY = 2147483629; // maximum prime number that < INT_MAX

    // Number of elements.
    int size_;

    // Available capacity.
    int capacity_;

    // Pointer to the slots.
    Slot* data_;

public:
    /// Map iterator class.
    ///
    /// Walk the map in random order.
    template <bool Const>
    class Iter
    {
        friend class HashMap;

    protected:
        using SlotPtr = std::conditional_t<Const, const Slot*, Slot*>;
        using Value = std::conditional_t<Const, const detail::MapEntry<K, V>, detail::MapEntry<K, V>>;

        SlotPtr current_;

        // Begin of the buffer.
        SlotPtr buffer_begin_;

        // End of the buffer.
        SlotPtr buffer_end_;

        // Constructor.
        Iter(SlotPtr current, SlotPtr begin, SlotPtr end)
            : current_(current)
            , buffer_begin_(begin)
            , buffer_end_(end)
        {
            while (current_ != buffer_end_ && current_->second != OCCUPIED)
            {
                ++current_;
            }
        }

    public:
        Value& operator*() const
        {
            return current_->first;
        }

        bool operator==(const Iter& that) const
        {
            return current_ == that.current_;
        }

        Iter& operator++()
        {
            while (++current_ != buffer_end_ && current_->second != OCCUPIED)
            {
            }
            return *this;
        }

        Iter& operator--()
        {
            while (--current_ != buffer_begin_ && current_->second != OCCUPIED)
            {
            }
            return *this;
        }
    };

protected:
    int probe_pos(const K& key, bool for_insert) const
    {
        int current_pos = Hash()(key) % capacity_;
        int new_pos = current_pos;
        int conflict_cnt = 0;
        int first_deleted = -1;

        while (data_[new_pos].second != EMPTY)
        {
            if (data_[new_pos].second == OCCUPIED)
            {
                if (Eq()(data_[new_pos].first.key(), key))
                {
                    return new_pos;
                }
            }
            else if (for_insert && first_deleted == -1)
            {
                first_deleted = new_pos;
            }

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

        return for_insert ? (first_deleted == -1 ? new_pos : first_deleted) : -1;
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

        // if n is even, let it odd and < this, because n > 2 is odd and while n += 2
        if (n % 2 == 0)
        {
            --n;
        }

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
        Slot* old_data = data_;

        // expand to the next prime greater than twice the current capacity
        int new_capacity = next_prime(capacity_ * 2);

        // create new slots (value-initialized: state zeroed to EMPTY)
        Slot* new_data = new Slot[new_capacity]();

        // move elements (rehash)
        data_ = new_data;
        capacity_ = new_capacity;
        size_ = 0;
        for (int i = 0; i < old_capacity; i++)
        {
            if (old_data[i].second == OCCUPIED)
            {
                insert(old_data[i].first.key(), old_data[i].first.value());
            }
        }

        // free old slots
        delete[] old_data;
    }

    // Swap with another map.
    void swap(HashMap& that)
    {
        std::swap(size_, that.size_);
        std::swap(capacity_, that.capacity_);
        std::swap(data_, that.data_);
    }

public:
    /// @name Lifecycle
    /// @{

    /// Create an empty map.
    HashMap()
        : size_(0)
        , capacity_(INIT_PRIME_CAPACITY)
        , data_(new Slot[capacity_]())
    {
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

    /// Copy constructor.
    HashMap(const HashMap& that)
        : size_(0)
        , capacity_(that.capacity_)
        , data_(new Slot[capacity_]())
    {
        for (int i = 0; i < that.capacity_; ++i)
        {
            if (that.data_[i].second == OCCUPIED)
            {
                insert(that.data_[i].first.key(), that.data_[i].first.value());
            }
        }
    }

    /// Move constructor.
    HashMap(HashMap&& that)
        : HashMap()
    {
        swap(that);
    }

    HashMap& operator=(HashMap that)
    {
        swap(that);
        return *this;
    }

    /// Destroy the map object.
    ~HashMap()
    {
        delete[] data_;
    }
    /// @}

    /// @name Comparison
    /// @{

    /// Check whether two maps are equal.
    bool operator==(const HashMap& that) const
    {
        if (size_ != that.size_)
        {
            return false;
        }

        for (const auto& entry : *this)
        {
            auto it = that.find(entry.key());
            if (it == that.end() || entry.value() != it->value())
            {
                return false;
            }
        }

        return true;
    }
    /// @}

    /// @name Access
    /// @{

    /// Return the reference of value for key if key is in the map, else throw exception.
    V& operator[](const K& key) override
    {
        int pos = probe_pos(key, false);

        if (pos == -1)
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }

        return data_[pos].first.value();
    }

    /// Return the const reference of value for key if key is in the map, else throw exception.
    const V& operator[](const K& key) const override
    {
        int pos = probe_pos(key, false);

        if (pos == -1)
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }

        return data_[pos].first.value();
    }
    /// @}

    /// @name Iterator
    /// @{

    /// Return an iterator to the first element of the map.
    Map<K, V>::Iterator begin() override
    {
        return typename Map<K, V>::Iterator(Iter<false>(data_, data_, data_ + capacity_));
    }

    Map<K, V>::ConstIterator begin() const override
    {
        return typename Map<K, V>::ConstIterator(Iter<true>(data_, data_, data_ + capacity_));
    }

    /// Return an iterator to the element following the last element of the map.
    Map<K, V>::Iterator end() override
    {
        return typename Map<K, V>::Iterator(Iter<false>(data_ + capacity_, data_, data_ + capacity_));
    }

    Map<K, V>::ConstIterator end() const override
    {
        return typename Map<K, V>::ConstIterator(Iter<true>(data_ + capacity_, data_, data_ + capacity_));
    }
    /// @}

    /// @name Examination
    /// @{

    /// Get the number of elements.
    int size() const override
    {
        return size_;
    }

    /// Return an iterator to the first occurrence of the specified key, or end() if the map does not contains the key.
    Map<K, V>::Iterator find(const K& key) override
    {
        int pos = probe_pos(key, false);
        return pos == -1 ? end() : typename Map<K, V>::Iterator(Iter<false>(data_ + pos, data_, data_ + capacity_));
    }

    /// Return a const iterator to the first occurrence of the specified key, or end() if the map does not contains the key.
    Map<K, V>::ConstIterator find(const K& key) const override
    {
        int pos = probe_pos(key, false);
        return pos == -1 ? end() : typename Map<K, V>::ConstIterator(Iter<true>(data_ + pos, data_, data_ + capacity_));
    }
    /// @}

    /// @name Manipulation
    /// @{

    /// Insert a new key-value pair into the map. Return whether the pair was newly inserted.
    bool insert(const K& key, const V& value) override
    {
        detail::check_full(size_, MAX_PRIME_CAPACITY >> 1);

        int pos = probe_pos(key, true);

        if (data_[pos].second == OCCUPIED)
        {
            return false;
        }

        data_[pos] = {{key, value}, OCCUPIED};

        size_++;

        // expand capacity when the loading factor is too large (> 0.5)
        if (size_ > (capacity_ >> 1))
        {
            expand_capacity();
        }
        return true;
    }

    /// Remove the key-value pair corresponding to the key in the map. Return whether such a key was present.
    bool remove(const K& key) override
    {
        int pos = probe_pos(key, false);

        if (pos == -1)
        {
            return false;
        }

        data_[pos].second = DELETED;
        size_--;
        return true;
    }

    /// Remove all of the elements from the map.
    void clear() override
    {
        if (size_ != 0)
        {
            for (int i = 0; i < capacity_; ++i)
            {
                data_[i].second = EMPTY;
            }
            size_ = 0;
        }
    }

    /// @}
};

} // namespace hellods

#endif // HASHMAP_HPP
