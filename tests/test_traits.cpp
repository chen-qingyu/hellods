#include <type_traits>

#include "../sources/Deque/ArrayDeque.hpp"
#include "../sources/Deque/LinkedDeque.hpp"
#include "../sources/Graph/MatrixGraph.hpp"
#include "../sources/Heap/BinaryHeap.hpp"
#include "../sources/List/ArrayList.hpp"
#include "../sources/List/LinkedList.hpp"
#include "../sources/List/SinglyLinkedList.hpp"
#include "../sources/Map/HashMap.hpp"
#include "../sources/Queue/ArrayQueue.hpp"
#include "../sources/Queue/LinkedQueue.hpp"
#include "../sources/Set/HashSet.hpp"
#include "../sources/Stack/ArrayStack.hpp"
#include "../sources/Stack/LinkedStack.hpp"
#include "../sources/Tree/BinarySearchTree.hpp"
#include "../sources/Tree/RedBlackTree.hpp"
#include "../sources/detail.hpp"

using namespace hellods;

template <typename T>
constexpr bool kMoveConstructibleContainer =
    std::is_copy_constructible_v<T> &&
    !std::is_copy_assignable_v<T> &&
    std::is_move_constructible_v<T> &&
    !std::is_move_assignable_v<T>;

static_assert(std::has_virtual_destructor_v<detail::Container>);

static_assert(kMoveConstructibleContainer<ArrayList<int>>);
static_assert(kMoveConstructibleContainer<LinkedList<int>>);
static_assert(kMoveConstructibleContainer<SinglyLinkedList<int>>);
static_assert(kMoveConstructibleContainer<ArrayDeque<int>>);
static_assert(kMoveConstructibleContainer<LinkedDeque<int>>);
static_assert(kMoveConstructibleContainer<ArrayQueue<int>>);
static_assert(kMoveConstructibleContainer<LinkedQueue<int>>);
static_assert(kMoveConstructibleContainer<ArrayStack<int>>);
static_assert(kMoveConstructibleContainer<LinkedStack<int>>);
static_assert(kMoveConstructibleContainer<HashMap<int, int>>);
static_assert(kMoveConstructibleContainer<HashSet<int>>);
static_assert(kMoveConstructibleContainer<BinaryHeap<int>>);
static_assert(kMoveConstructibleContainer<BinarySearchTree<int>>);
static_assert(kMoveConstructibleContainer<RedBlackTree<int>>);
static_assert(kMoveConstructibleContainer<MatrixGraph<>>);

static_assert(std::is_const_v<std::remove_reference_t<decltype(*std::declval<const ArrayList<int>&>().begin())>>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(*std::declval<const LinkedList<int>&>().begin())>>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(*std::declval<const SinglyLinkedList<int>&>().begin())>>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(*std::declval<const ArrayDeque<int>&>().begin())>>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(*std::declval<const HashMap<int, int>&>().begin())>>);