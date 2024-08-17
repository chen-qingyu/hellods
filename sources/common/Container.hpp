/**
 * @file Container.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Base container class of HelloDS.
 * @date 2024.03.27
 */

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

namespace hellods::common
{

/// Base container class for HelloDS.
class Container
{
protected:
    // Initial capacity.
    static const int INIT_CAPACITY = 8;

    // Maximum capacity.
    static const int MAX_CAPACITY = INT_MAX - 1;

    // Number of elements in the container.
    int size_;

public:
    /// Constructor.
    Container(int size)
        : size_(size)
    {
    }

    /// Get the number of elements of the container.
    int size() const
    {
        return size_;
    }

    /// Check if the container is empty.
    bool is_empty() const
    {
        return size_ == 0;
    }
};

} // namespace hellods::common

#endif // CONTAINER_HPP
