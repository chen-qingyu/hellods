#include <type_traits>

#include "tool.hpp"

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
#include "../sources/Tree/SplayTree.hpp"
#include "../sources/detail.hpp"

using namespace hellods;

namespace dsd = hellods::detail;

template <typename T>
constexpr bool kMoveConstructibleContainer =
    std::is_copy_constructible_v<T> &&
    !std::is_copy_assignable_v<T> &&
    std::is_move_constructible_v<T> &&
    !std::is_move_assignable_v<T>;

template <typename T>
constexpr bool kConstBeginReference = std::is_const_v<std::remove_reference_t<decltype(*std::declval<const T&>().begin())>>;

static_assert(std::has_virtual_destructor_v<dsd::Container>);

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
static_assert(kMoveConstructibleContainer<SplayTree<int>>);
static_assert(kMoveConstructibleContainer<MatrixGraph<>>);

static_assert(dsd::StoredElement<EqType>);
static_assert(dsd::LinearElement<EqType>);
static_assert(!dsd::OrderedElement<EqType>);
static_assert(dsd::OrderedElement<EqLtType>);
static_assert(dsd::HashKey<EqType, std::hash<EqType>, std::equal_to<EqType>>);
static_assert(!dsd::HashKey<EqLtType, std::hash<EqLtType>, std::equal_to<EqLtType>>);
static_assert(dsd::StoredElement<int>);
static_assert(std::equality_comparable<EqType>);
static_assert(dsd::ComparatorFor<int, std::greater<int>>);
static_assert(dsd::ComparatorFor<EqLtType, std::less<EqLtType>>);

static_assert(kConstBeginReference<ArrayList<int>>);
static_assert(kConstBeginReference<LinkedList<int>>);
static_assert(kConstBeginReference<SinglyLinkedList<int>>);
static_assert(kConstBeginReference<ArrayDeque<int>>);
static_assert(kConstBeginReference<HashMap<int, int>>);