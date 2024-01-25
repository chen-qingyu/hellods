#include <catch2/catch_test_macros.hpp>

extern "C"
{
#include "../sources/Tree/BinarySearchTree.h"
}

// for test traverse
static char str[64] = {0};

static void Visit(const BinarySearchTreeItem n)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", n);
    strcat(str, tmp);
}

TEST_CASE("Tree: BinarySearchTree")
{
    // BinarySearchTree_Create BinarySearchTree_Size BinarySearchTree_IsEmpty
    BinarySearchTree* tree = BinarySearchTree_Create();
    REQUIRE(BinarySearchTree_Size(tree) == 0);
    REQUIRE(BinarySearchTree_IsEmpty(tree) == true);

    // BinarySearchTree_Find BinarySearchTree_FindMax BinarySearchTree_FindMin
    REQUIRE(BinarySearchTree_Find(tree, 0) == BINARY_SEARCH_TREE_NOT_FOUND);
    REQUIRE(BinarySearchTree_FindMax(tree) == BINARY_SEARCH_TREE_NOT_FOUND);
    REQUIRE(BinarySearchTree_FindMin(tree) == BINARY_SEARCH_TREE_NOT_FOUND);

    // BinarySearchTree_Insert
    BinarySearchTree_Insert(tree, 3);
    BinarySearchTree_Insert(tree, 1);
    BinarySearchTree_Insert(tree, 2);
    BinarySearchTree_Insert(tree, 4);
    BinarySearchTree_Insert(tree, 5);
    BinarySearchTree_Insert(tree, 5);
    BinarySearchTree_Insert(tree, 5);
    BinarySearchTree_Insert(tree, 1);
    REQUIRE(BinarySearchTree_Size(tree) == 5);

    // BinarySearchTree_Traverse
    BinarySearchTree_Traverse(tree, PRE_ORDER, Visit);
    REQUIRE(strcmp(str, "3 1 2 4 5 ") == 0);
    memset(str, 0, sizeof(str));

    BinarySearchTree_Traverse(tree, IN_ORDER, Visit);
    REQUIRE(strcmp(str, "1 2 3 4 5 ") == 0);
    memset(str, 0, sizeof(str));

    BinarySearchTree_Traverse(tree, POST_ORDER, Visit);
    REQUIRE(strcmp(str, "2 1 5 4 3 ") == 0);
    memset(str, 0, sizeof(str));

    BinarySearchTree_Traverse(tree, LEVEL_ORDER, Visit);
    REQUIRE(strcmp(str, "3 1 4 2 5 ") == 0);
    memset(str, 0, sizeof(str));

    // BinarySearchTree_Find
    REQUIRE(BinarySearchTree_Find(tree, 2) == 2);
    REQUIRE(BinarySearchTree_Find(tree, 0) == BINARY_SEARCH_TREE_NOT_FOUND);

    // BinarySearchTree_FindMin BinarySearchTree_FindMax
    REQUIRE(BinarySearchTree_FindMin(tree) == 1);
    REQUIRE(BinarySearchTree_FindMax(tree) == 5);

    // BinarySearchTree_Depth
    REQUIRE(BinarySearchTree_Depth(tree) == 3);

    // BinarySearchTree_Remove
    BinarySearchTree_Remove(tree, 1);
    REQUIRE(BinarySearchTree_FindMin(tree) == 2);
    BinarySearchTree_Remove(tree, 5);
    REQUIRE(BinarySearchTree_FindMax(tree) == 4);
    REQUIRE(BinarySearchTree_Size(tree) == 3);

    // BinarySearchTree_Depth
    REQUIRE(BinarySearchTree_Depth(tree) == 2);

    // BinarySearchTree_Clear
    BinarySearchTree_Clear(tree);
    REQUIRE(BinarySearchTree_Size(tree) == 0);
    REQUIRE(BinarySearchTree_Depth(tree) == 0);
    BinarySearchTree_Clear(tree); // double clear
    REQUIRE(BinarySearchTree_Size(tree) == 0);
    REQUIRE(BinarySearchTree_Depth(tree) == 0);

    // BinarySearchTree_Destroy
    BinarySearchTree_Destroy(tree);
}
