/**
 * @file Container.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Base container class for HelloDS.
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
    // Number of elements in the container.
    int size_;

public:
    /// Constructor.
    Container(int size)
        : size_(size)
    {
    }

    /// Get the number of elements of the container.
    virtual int size() const
    {
        return size_;
    }

    /// Check if the container is empty.
    virtual bool is_empty() const
    {
        return size_ == 0;
    }
};

} // namespace hellods::common

#endif // CONTAINER_HPP
