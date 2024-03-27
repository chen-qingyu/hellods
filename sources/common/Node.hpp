/**
 * @file Node.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Common node class for HelloDS.
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

#ifndef NODE_HPP
#define NODE_HPP

namespace hellods::common
{

/// Common node of linked list.
template <typename T>
struct Node
{
    // Data stored in the node.
    T data_;

    // Successor.
    Node* succ_;

    // Create a node with given element.
    Node(const T& data, Node* succ = nullptr)
        : data_(data)
        , succ_(succ)
    {
    }
};

} // namespace hellods::common

#endif // NODE_HPP
