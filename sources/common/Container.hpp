/**
 * @file Container.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Base container class for HelloDS.
 * @date 2024.03.27
 *
 * @copyright Copyright (C) 2024
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

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

namespace hellods::internal
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

} // namespace hellods::internal

#endif // CONTAINER_HPP
