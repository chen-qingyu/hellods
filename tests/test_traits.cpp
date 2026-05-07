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
#include "../sources/Map/TreeMap.hpp"
#include "../sources/Queue/ArrayQueue.hpp"
#include "../sources/Queue/LinkedQueue.hpp"
#include "../sources/Set/HashSet.hpp"
#include "../sources/Set/TreeSet.hpp"
#include "../sources/Stack/ArrayStack.hpp"
#include "../sources/Stack/LinkedStack.hpp"
#include "../sources/Tree/BinarySearchTree.hpp"
#include "../sources/Tree/RedBlackTree.hpp"
#include "../sources/Tree/SplayTree.hpp"
#include "../sources/detail.hpp"

using namespace hellods;
using namespace hellods::detail;

template <typename T>
constexpr bool kFullFeaturedContainer =
    std::is_copy_constructible_v<T> &&
    std::is_copy_assignable_v<T> &&
    std::is_move_constructible_v<T> &&
    std::is_move_assignable_v<T>;

template <typename T>
constexpr bool kConstBeginReference = std::is_const_v<std::remove_reference_t<decltype(*std::declval<const T&>().begin())>>;

static_assert(std::has_virtual_destructor_v<Container>);

static_assert(kFullFeaturedContainer<ArrayList<int>>);
static_assert(kFullFeaturedContainer<LinkedList<int>>);
static_assert(kFullFeaturedContainer<SinglyLinkedList<int>>);
static_assert(kFullFeaturedContainer<ArrayDeque<int>>);
static_assert(kFullFeaturedContainer<LinkedDeque<int>>);
static_assert(kFullFeaturedContainer<ArrayQueue<int>>);
static_assert(kFullFeaturedContainer<LinkedQueue<int>>);
static_assert(kFullFeaturedContainer<ArrayStack<int>>);
static_assert(kFullFeaturedContainer<LinkedStack<int>>);
static_assert(kFullFeaturedContainer<HashMap<int, int>>);
static_assert(kFullFeaturedContainer<HashSet<int>>);
static_assert(kFullFeaturedContainer<BinaryHeap<int>>);
static_assert(kFullFeaturedContainer<BinarySearchTree<int>>);
static_assert(kFullFeaturedContainer<RedBlackTree<int>>);
static_assert(kFullFeaturedContainer<SplayTree<int>>);
static_assert(kFullFeaturedContainer<MatrixGraph<>>);
static_assert(kFullFeaturedContainer<TreeSet<int>>);
static_assert(kFullFeaturedContainer<TreeMap<int, int>>);

static_assert(StoredElement<EqType>);
static_assert(LinearElement<EqType>);
static_assert(!OrderedElement<EqType>);
static_assert(OrderedElement<EqLtType>);
static_assert(HashKey<EqType, std::hash<EqType>, std::equal_to<EqType>>);
static_assert(!HashKey<EqLtType, std::hash<EqLtType>, std::equal_to<EqLtType>>);
static_assert(StoredElement<int>);
static_assert(std::equality_comparable<EqType>);
static_assert(ComparatorFor<int, std::greater<int>>);
static_assert(ComparatorFor<EqLtType, std::less<EqLtType>>);

static_assert(kConstBeginReference<ArrayList<int>>);
static_assert(kConstBeginReference<LinkedList<int>>);
static_assert(kConstBeginReference<SinglyLinkedList<int>>);
static_assert(kConstBeginReference<ArrayDeque<int>>);
static_assert(kConstBeginReference<HashMap<int, int>>);