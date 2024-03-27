/**
 * @file Node.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Common node class for HelloDS.
 * @date 2024.03.27
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
