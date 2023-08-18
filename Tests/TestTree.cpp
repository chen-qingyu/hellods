// Tested on Microsoft Visual Studio Community 2019: ALL PASSED

#include "../pch.h"

extern "C"
{
#include "../Sources/Tree/BinarySearchTree.h"
}

// for test traverse
static char str[64] = {0};

static void Visit(const BinarySearchTreeItem n)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", n);
    strcat(str, tmp);
}

TEST(Tree, BinarySearchTree)
{
    // BinarySearchTree_Create BinarySearchTree_Size BinarySearchTree_IsEmpty
    BinarySearchTree* tree = BinarySearchTree_Create();
    ASSERT_EQ(BinarySearchTree_Size(tree), 0);
    ASSERT_EQ(BinarySearchTree_IsEmpty(tree), true);

    // BinarySearchTree_Find BinarySearchTree_FindMax BinarySearchTree_FindMin
    ASSERT_EQ(BinarySearchTree_Find(tree, 0), BINARY_SEARCH_TREE_NOT_FOUND);
    ASSERT_EQ(BinarySearchTree_FindMax(tree), BINARY_SEARCH_TREE_NOT_FOUND);
    ASSERT_EQ(BinarySearchTree_FindMin(tree), BINARY_SEARCH_TREE_NOT_FOUND);

    // BinarySearchTree_Insert
    BinarySearchTree_Insert(tree, 3);
    BinarySearchTree_Insert(tree, 1);
    BinarySearchTree_Insert(tree, 2);
    BinarySearchTree_Insert(tree, 4);
    BinarySearchTree_Insert(tree, 5);
    BinarySearchTree_Insert(tree, 5);
    BinarySearchTree_Insert(tree, 5);
    BinarySearchTree_Insert(tree, 1);
    ASSERT_EQ(BinarySearchTree_Size(tree), 5);

    // BinarySearchTree_Traverse
    BinarySearchTree_Traverse(tree, PRE_ORDER, Visit);
    ASSERT_EQ(strcmp(str, "3 1 2 4 5 "), 0);
    memset(str, 0, sizeof(str));

    BinarySearchTree_Traverse(tree, IN_ORDER, Visit);
    ASSERT_EQ(strcmp(str, "1 2 3 4 5 "), 0);
    memset(str, 0, sizeof(str));

    BinarySearchTree_Traverse(tree, POST_ORDER, Visit);
    ASSERT_EQ(strcmp(str, "2 1 5 4 3 "), 0);
    memset(str, 0, sizeof(str));

    BinarySearchTree_Traverse(tree, LEVEL_ORDER, Visit);
    ASSERT_EQ(strcmp(str, "3 1 4 2 5 "), 0);
    memset(str, 0, sizeof(str));

    // BinarySearchTree_Find
    ASSERT_EQ(BinarySearchTree_Find(tree, 2), 2);
    ASSERT_EQ(BinarySearchTree_Find(tree, 0), BINARY_SEARCH_TREE_NOT_FOUND);

    // BinarySearchTree_FindMin BinarySearchTree_FindMax
    ASSERT_EQ(BinarySearchTree_FindMin(tree), 1);
    ASSERT_EQ(BinarySearchTree_FindMax(tree), 5);

    // BinarySearchTree_Depth
    ASSERT_EQ(BinarySearchTree_Depth(tree), 3);

    // BinarySearchTree_Remove
    BinarySearchTree_Remove(tree, 1);
    ASSERT_EQ(BinarySearchTree_FindMin(tree), 2);
    BinarySearchTree_Remove(tree, 5);
    ASSERT_EQ(BinarySearchTree_FindMax(tree), 4);
    ASSERT_EQ(BinarySearchTree_Size(tree), 3);

    // BinarySearchTree_Depth
    ASSERT_EQ(BinarySearchTree_Depth(tree), 2);

    // BinarySearchTree_Clear
    BinarySearchTree_Clear(tree);
    ASSERT_EQ(BinarySearchTree_Size(tree), 0);
    ASSERT_EQ(BinarySearchTree_Depth(tree), 0);
    BinarySearchTree_Clear(tree); // double clear
    ASSERT_EQ(BinarySearchTree_Size(tree), 0);
    ASSERT_EQ(BinarySearchTree_Depth(tree), 0);

    // BinarySearchTree_Destroy
    BinarySearchTree_Destroy(tree);
}
