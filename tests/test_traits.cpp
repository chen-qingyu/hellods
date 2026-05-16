#include <iterator>
#include <type_traits>

#include "tool.hpp"

#include "../sources/Deque/ArrayDeque.hpp"
#include "../sources/Deque/LinkedDeque.hpp"
#include "../sources/Graph/ListGraph.hpp"
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
#include "../sources/Tree/AVLTree.hpp"
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
static_assert(kFullFeaturedContainer<ListGraph<>>);
static_assert(kFullFeaturedContainer<MatrixGraph<>>);
static_assert(kFullFeaturedContainer<TreeSet<int>>);
static_assert(kFullFeaturedContainer<TreeMap<int, int>>);

static_assert(kConstBeginReference<ArrayList<int>>);
static_assert(kConstBeginReference<LinkedList<int>>);
static_assert(kConstBeginReference<SinglyLinkedList<int>>);
static_assert(kConstBeginReference<ArrayDeque<int>>);
static_assert(kConstBeginReference<HashMap<int, int>>);

static_assert(std::bidirectional_iterator<decltype(std::declval<HashSet<int>&>().begin())>);
static_assert(std::bidirectional_iterator<decltype(std::declval<TreeSet<int>&>().begin())>);
static_assert(std::bidirectional_iterator<decltype(std::declval<HashMap<int, int>&>().begin())>);
static_assert(std::bidirectional_iterator<decltype(std::declval<TreeMap<int, int>&>().begin())>);
static_assert(!std::is_const_v<std::remove_reference_t<decltype(std::declval<HashMap<int, int>&>().begin()->value())>>);
static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<const HashMap<int, int>&>().begin()->value())>>);

// Tree containers support EqLtType
static_assert(requires(BinarySearchTree<EqLtType>& t, const EqLtType& e) { t.insert(e); });
static_assert(requires(RedBlackTree<EqLtType>& t, const EqLtType& e) { t.insert(e); });
static_assert(requires(AVLTree<EqLtType>& t, const EqLtType& e) { t.insert(e); });
static_assert(requires(SplayTree<EqLtType>& t, const EqLtType& e) { t.insert(e); });
static_assert(requires(TreeSet<EqLtType>& s, const EqLtType& e) { s.insert(e); });
static_assert(requires(TreeMap<EqLtType, int>& m, const EqLtType& k, int v) { m.insert(k, v); });
