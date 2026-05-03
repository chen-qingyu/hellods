/**
 * @file HashMap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Hash map.
 * @date 2022.01.29
 */

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "../detail.hpp"

namespace hellods
{

/// Hash map.
template <typename K, detail::StoredElement V, typename Hash = std::hash<K>, typename Eq = std::equal_to<K>>
    requires detail::HashKey<K, Hash, Eq>
class HashMap : public detail::Container
{
protected:
    // Hash map pair.
    struct Pair
    {
        using ValueType = std::pair<const K, V>;

        // The key-value pair stored in this slot.
        ValueType* pair_;

        // State of the key-value pair: 0 = empty, 1 = occupied, 2 = deleted
        enum State
        {
            EMPTY = 0,
            OCCUPIED = 1,
            DELETED = 2
        } state_;

        Pair()
            : pair_(nullptr)
            , state_(EMPTY)
        {
        }

        ~Pair()
        {
            clear();
        }

        const K& key() const
        {
            return pair_->first;
        }

        V& value()
        {
            return pair_->second;
        }

        const V& value() const
        {
            return pair_->second;
        }

        void reset(const K& key, const V& value)
        {
            clear();
            pair_ = new ValueType(key, value);
            state_ = OCCUPIED;
        }

        void clear()
        {
            if (pair_ != nullptr)
            {
                delete pair_;
                pair_ = nullptr;
            }
        }
    };

protected:
    // Initial capacity for hash map.
    static const int INIT_PRIME_CAPACITY = 7;

    // Maximum capacity for hash map.
    static const int MAX_PRIME_CAPACITY = 2147483629; // maximum prime number that < INT_MAX

    // Number of elements.
    int size_;

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
    template <bool Const>
    class BasicIterator
    {
        friend class HashMap;

    protected:
        using PairPtr = std::conditional_t<Const, const Pair*, Pair*>;
        using Value = std::conditional_t<Const, const std::pair<const K, V>, std::pair<const K, V>>;

        PairPtr current_;

        // Begin of the buffer.
        PairPtr buffer_begin_;

        // End of the buffer.
        PairPtr buffer_end_;

        // Constructor.
        BasicIterator(PairPtr current, PairPtr begin, PairPtr end)
            : current_(current)
            , buffer_begin_(begin)
            , buffer_end_(end)
        {
            while (current_ != buffer_end_ && current_->state_ != Pair::OCCUPIED)
            {
                ++current_;
            }
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::pair<const K, V>;
        using difference_type = int;
        using pointer = Value*;
        using reference = Value&;

        bool operator==(const BasicIterator& that) const
        {
            return current_ == that.current_;
        }

        reference operator*() const
        {
            return *current_->pair_;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        BasicIterator& operator++()
        {
            while (++current_ != buffer_end_ && current_->state_ != Pair::OCCUPIED)
            {
            }
            return *this;
        }

        BasicIterator operator++(int)
        {
            auto it = *this;
            ++*this;
            return it;
        }

        BasicIterator& operator--()
        {
            while (--current_ != buffer_begin_ && current_->state_ != Pair::OCCUPIED)
            {
            }
            return *this;
        }

        BasicIterator operator--(int)
        {
            auto it = *this;
            --*this;
            return it;
        }
    };

    using Iterator = BasicIterator<false>;
    using ConstIterator = BasicIterator<true>;

protected:
    int probe_pos(const K& key, bool for_insert) const
    {
        int current_pos = Hash()(key) % capacity_;
        int new_pos = current_pos;
        int conflict_cnt = 0;
        int first_deleted = -1;

        while (data_[new_pos].state_ != Pair::EMPTY)
        {
            if (data_[new_pos].state_ == Pair::OCCUPIED)
            {
                if (Eq()(data_[new_pos].key(), key))
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
        Pair* old_data = data_;

        // expand to the next prime greater than twice the current capacity
        int new_capacity = next_prime(capacity_ * 2);

        // create new pairs
        Pair* new_data = new Pair[new_capacity];
        for (int i = 0; i < new_capacity; i++)
        {
            new_data[i].state_ = Pair::EMPTY;
        }

        // move elements (rehash)
        data_ = new_data;
        capacity_ = new_capacity;
        size_ = 0;
        for (int i = 0; i < old_capacity; i++)
        {
            if (old_data[i].state_ == Pair::OCCUPIED)
            {
                insert(old_data[i].key(), old_data[i].value());
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
        : size_(0)
        , capacity_(INIT_PRIME_CAPACITY)
        , data_(new Pair[capacity_])
    {
        for (int i = 0; i < capacity_; i++)
        {
            data_[i].state_ = Pair::EMPTY;
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

    /// Copy constructor.
    HashMap(const HashMap& that)
        : size_(0)
        , capacity_(that.capacity_)
        , data_(new Pair[capacity_])
    {
        for (int i = 0; i < capacity_; ++i)
        {
            data_[i].state_ = Pair::EMPTY;
        }
        for (int i = 0; i < that.capacity_; ++i)
        {
            if (that.data_[i].state_ == Pair::OCCUPIED)
            {
                insert(that.data_[i].key(), that.data_[i].value());
            }
        }
    }

    /// Move constructor.
    HashMap(HashMap&& that)
        : size_(that.size_)
        , capacity_(that.capacity_)
        , data_(that.data_)
    {
        that.size_ = 0;
        that.capacity_ = INIT_PRIME_CAPACITY;
        that.data_ = new Pair[that.capacity_];
        for (int i = 0; i < that.capacity_; ++i)
        {
            that.data_[i].state_ = Pair::EMPTY;
        }
    }

    HashMap& operator=(const HashMap&) = delete;
    HashMap& operator=(HashMap&&) = delete;

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
        requires detail::LinearElement<V>
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

    /*
     * Access
     */

    /// Return the reference of value for key if key is in the map, else throw exception.
    V& operator[](const K& key)
    {
        int pos = probe_pos(key, false);

        if (pos == -1)
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }

        return data_[pos].value();
    }

    /// Return the const reference of value for key if key is in the map, else throw exception.
    const V& operator[](const K& key) const
    {
        int pos = probe_pos(key, false);

        if (pos == -1)
        {
            throw std::runtime_error("Error: The key-value pair does not exist.");
        }

        return data_[pos].value();
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the map.
    auto begin()
    {
        return Iterator(data_, data_, data_ + capacity_);
    }

    auto begin() const
    {
        return ConstIterator(data_, data_, data_ + capacity_);
    }

    /// Return an iterator to the element following the last element of the map.
    auto end()
    {
        return Iterator(data_ + capacity_, data_, data_ + capacity_);
    }

    auto end() const
    {
        return ConstIterator(data_ + capacity_, data_, data_ + capacity_);
    }

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return size_;
    }

    /// Return an iterator to the first occurrence of the specified key, or end() if the map does not contains the key.
    Iterator find(const K& key)
    {
        int pos = probe_pos(key, false);
        return pos == -1 ? end() : Iterator(data_ + pos, data_, data_ + capacity_);
    }

    ConstIterator find(const K& key) const
    {
        int pos = probe_pos(key, false);
        return pos == -1 ? end() : ConstIterator(data_ + pos, data_, data_ + capacity_);
    }

    /// Determine whether a key is in the map.
    bool contains(const K& key) const
    {
        return probe_pos(key, false) != -1;
    }

    /*
     * Manipulation
     */

    /// Insert a new key-value pair into the map. Return whether the pair was newly inserted.
    bool insert(const K& key, const V& value)
    {
        detail::check_full(size_, MAX_PRIME_CAPACITY >> 1);

        int pos = probe_pos(key, true);

        if (data_[pos].state_ == Pair::OCCUPIED)
        {
            return false;
        }

        data_[pos].reset(key, value);

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
        int pos = probe_pos(key, false);

        if (pos == -1)
        {
            return false;
        }

        data_[pos].clear();
        data_[pos].state_ = Pair::DELETED;
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
                data_[i].clear();
                data_[i].state_ = Pair::EMPTY;
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
        return detail::print(os, map.begin(), map.end(), "Map");
    }
};

} // namespace hellods

#endif // HASHMAP_HPP
