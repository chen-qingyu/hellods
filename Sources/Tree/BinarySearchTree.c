#include "BinarySearchTree.h"

#include <stdio.h>  // fprintf stderr
#include <stdlib.h> // malloc free exit EXIT_FAILURE NULL

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

struct BinarySearchTreeNode
{
    /// Data stored in the node.
    BinarySearchTreeItem data;

    /// Pointer to the left child.
    struct BinarySearchTreeNode* left;

    /// Pointer to the right child.
    struct BinarySearchTreeNode* right;
};

struct BinarySearchTree
{
    /// Number of elements.
    int size;

    /// Pointer to the root.
    struct BinarySearchTreeNode* root;
};

/*******************************
Helper functions implementation.
*******************************/

typedef struct BinarySearchTreeNode* ArrayQueueItem;

typedef struct ArrayQueue ArrayQueue;

#define ARRAYQUEUE_CAPACITY 256

struct ArrayQueue
{
    ArrayQueueItem data[ARRAYQUEUE_CAPACITY + 1]; // 循环队列，数组容量为队列有效容量加一
    int front;
    int rear;
};

static ArrayQueue* ArrayQueue_Create(void)
{
    ArrayQueue* queue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
    check_pointer(queue);

    queue->front = -1;
    queue->rear = -1;

    return queue;
}

static void ArrayQueue_Destroy(ArrayQueue* self)
{
    free(self);
}

static int ArrayQueue_Size(const ArrayQueue* self)
{
    return (self->rear - self->front + (ARRAYQUEUE_CAPACITY + 1)) % (ARRAYQUEUE_CAPACITY + 1);
}

static bool ArrayQueue_IsEmpty(const ArrayQueue* self)
{
    return ArrayQueue_Size(self) == 0;
}

static void ArrayQueue_Enqueue(ArrayQueue* self, ArrayQueueItem data)
{
    check_full(ArrayQueue_Size(self), ARRAYQUEUE_CAPACITY);

    self->rear = (self->rear + 1) % ARRAYQUEUE_CAPACITY;
    self->data[self->rear] = data;
}

static ArrayQueueItem ArrayQueue_Dequeue(ArrayQueue* self)
{
    check_empty(ArrayQueue_Size(self));

    self->front = (self->front + 1) % ARRAYQUEUE_CAPACITY;

    return self->data[self->front];
}

static void destroy_node(struct BinarySearchTreeNode* node)
{
    if (node)
    {
        destroy_node(node->left);
        destroy_node(node->right);
        free(node);
    }
}

static void traverse_node(struct BinarySearchTreeNode* node, traverse_t type, void (*p_trav)(BinarySearchTreeItem data))
{
    if (node)
    {
        switch (type)
        {
            case PRE_ORDER:
            {
                p_trav(node->data);
                traverse_node(node->left, PRE_ORDER, p_trav);
                traverse_node(node->right, PRE_ORDER, p_trav);
                break;
            }

            case IN_ORDER:
            {
                traverse_node(node->left, IN_ORDER, p_trav);
                p_trav(node->data);
                traverse_node(node->right, IN_ORDER, p_trav);
                break;
            }

            case POST_ORDER:
            {
                traverse_node(node->left, POST_ORDER, p_trav);
                traverse_node(node->right, POST_ORDER, p_trav);
                p_trav(node->data);
                break;
            }

            case LEVEL_ORDER:
            {
                ArrayQueue* queue = ArrayQueue_Create();
                ArrayQueue_Enqueue(queue, node);
                while (!ArrayQueue_IsEmpty(queue))
                {
                    node = ArrayQueue_Dequeue(queue);
                    p_trav(node->data);
                    if (node->left)
                    {
                        ArrayQueue_Enqueue(queue, node->left);
                    }
                    if (node->right)
                    {
                        ArrayQueue_Enqueue(queue, node->right);
                    }
                }
                ArrayQueue_Destroy(queue);
                break;
            }

            default:
            {
                fprintf(stderr, "ERROR: Invalid type for traverse.\n");
                exit(EXIT_FAILURE);
                break;
            }
        }
    }
}

static struct BinarySearchTreeNode* insert_node(BinarySearchTree* tree, struct BinarySearchTreeNode* node, BinarySearchTreeItem data)
{
    if (node == NULL)
    {
        node = (struct BinarySearchTreeNode*)malloc(sizeof(struct BinarySearchTreeNode));
        check_pointer(node);

        node->data = data;
        node->left = NULL;
        node->right = NULL;
        tree->size++;
    }
    else
    {
        if (data < node->data)
        {
            node->left = insert_node(tree, node->left, data);
        }
        else if (data > node->data)
        {
            node->right = insert_node(tree, node->right, data);
        }
    }

    return node;
}

static struct BinarySearchTreeNode* find_min_node(struct BinarySearchTreeNode* node)
{
    while (node->left) // node is not NULL
    {
        node = node->left;
    }

    return node;
}

static struct BinarySearchTreeNode* remove_node(BinarySearchTree* tree, struct BinarySearchTreeNode* node, BinarySearchTreeItem data)
{
    if (node)
    {
        if (data < node->data)
        {
            node->left = remove_node(tree, node->left, data);
        }
        else if (data > node->data)
        {
            node->right = remove_node(tree, node->right, data);
        }
        else // data == node->data
        {
            if (node->left && node->right)
            {
                struct BinarySearchTreeNode* tmp = find_min_node(node->right); // node->right is not NULL
                node->data = tmp->data;
                node->right = remove_node(tree, node->right, tmp->data);
            }
            else
            {
                struct BinarySearchTreeNode* tmp = node;
                node = node->left ? node->left : node->right;
                free(tmp);
                tree->size--;
            }
        }
    }

    return node;
}

/*******************************
Interface functions implementation.
*******************************/

BinarySearchTree* BinarySearchTree_Create(void)
{
    BinarySearchTree* tree = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    check_pointer(tree);

    tree->root = NULL;
    tree->size = 0;

    return tree;
}

void BinarySearchTree_Destroy(BinarySearchTree* self)
{
    destroy_node(self->root);
    free(self);
}

int BinarySearchTree_Size(const BinarySearchTree* self)
{
    return self->size;
}

bool BinarySearchTree_IsEmpty(const BinarySearchTree* self)
{
    return self->size == 0;
}

void BinarySearchTree_Traverse(BinarySearchTree* self, traverse_t type, void (*p_trav)(BinarySearchTreeItem data))
{
    traverse_node(self->root, type, p_trav);
}

BinarySearchTreeItem BinarySearchTree_Find(const BinarySearchTree* self, BinarySearchTreeItem data)
{
    struct BinarySearchTreeNode* current = self->root;

    while (current)
    {
        if (data > current->data)
        {
            current = current->right;
        }
        else if (data < current->data)
        {
            current = current->left;
        }
        else
        {
            return current->data;
        }
    }

    return BINARY_SEARCH_TREE_NOT_FOUND;
}

BinarySearchTreeItem BinarySearchTree_FindMin(const BinarySearchTree* self)
{
    struct BinarySearchTreeNode* current = self->root;

    if (current)
    {
        while (current->left)
        {
            current = current->left;
        }
    }

    return current ? current->data : BINARY_SEARCH_TREE_NOT_FOUND;
}

BinarySearchTreeItem BinarySearchTree_FindMax(const BinarySearchTree* self)
{
    struct BinarySearchTreeNode* current = self->root;

    if (current)
    {
        while (current->right)
        {
            current = current->right;
        }
    }

    return current ? current->data : BINARY_SEARCH_TREE_NOT_FOUND;
}

void BinarySearchTree_Insert(BinarySearchTree* self, BinarySearchTreeItem data)
{
    self->root = insert_node(self, self->root, data);
}

void BinarySearchTree_Remove(BinarySearchTree* self, BinarySearchTreeItem data)
{
    self->root = remove_node(self, self->root, data);
}
