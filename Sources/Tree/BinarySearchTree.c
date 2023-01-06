#include "BinarySearchTree.h"
#include "QueueForTree.h"

#include <stdio.h>  // fprintf stderr
#include <stdlib.h> // malloc free exit EXIT_FAILURE NULL

#include "../common/check_pointer.h"

struct node
{
    // The data stored in this node.
    TreeItem data;

    // A pointer to the left child of the node.
    struct node* left;

    // A pointer to the right child of the node.
    struct node* right;
};

struct tree
{
    // Number of elements.
    int size;

    // A pointer to the root node.
    struct node* root;
};

/*******************************
Helper functions implementation.
*******************************/

static void destroy_node(struct node* node)
{
    if (node)
    {
        destroy_node(node->left);
        destroy_node(node->right);
        free(node);
    }
}

static void traverse_node(struct node* node, traverse_t type, void (*p_trav)(TreeItem data))
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
                Queue* queue = QueueForTree_Create();
                QueueForTree_Enqueue(queue, node);
                while (!QueueForTree_IsEmpty(queue))
                {
                    node = QueueForTree_Dequeue(queue);
                    p_trav(node->data);
                    if (node->left)
                    {
                        QueueForTree_Enqueue(queue, node->left);
                    }
                    if (node->right)
                    {
                        QueueForTree_Enqueue(queue, node->right);
                    }
                }
                QueueForTree_Destroy(queue);
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

static struct node* insert_node(Tree* tree, struct node* node, TreeItem data)
{
    if (node == NULL)
    {
        node = (struct node*)malloc(sizeof(struct node));
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

static struct node* find_min_node(struct node* node)
{
    while (node->left) // node is not NULL
    {
        node = node->left;
    }

    return node;
}

static struct node* remove_node(Tree* tree, struct node* node, TreeItem data)
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
                struct node* tmp = find_min_node(node->right); // node->right is not NULL
                node->data = tmp->data;
                node->right = remove_node(tree, node->right, tmp->data);
            }
            else
            {
                struct node* tmp = node;
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

Tree* BinarySearchTree_Create(void)
{
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    check_pointer(tree);

    tree->root = NULL;
    tree->size = 0;

    return tree;
}

void BinarySearchTree_Destroy(Tree* self)
{
    destroy_node(self->root);
    free(self);
}

int BinarySearchTree_Size(const Tree* self)
{
    return self->size;
}

bool BinarySearchTree_IsEmpty(const Tree* self)
{
    return self->size == 0;
}

void BinarySearchTree_Traverse(Tree* self, traverse_t type, void (*p_trav)(TreeItem data))
{
    traverse_node(self->root, type, p_trav);
}

TreeItem BinarySearchTree_Find(const Tree* self, TreeItem data)
{
    struct node* current = self->root;

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

    return TREE_NOT_FOUND;
}

TreeItem BinarySearchTree_FindMin(const Tree* self)
{
    struct node* current = self->root;

    if (current)
    {
        while (current->left)
        {
            current = current->left;
        }
    }

    return current ? current->data : TREE_NOT_FOUND;
}

TreeItem BinarySearchTree_FindMax(const Tree* self)
{
    struct node* current = self->root;

    if (current)
    {
        while (current->right)
        {
            current = current->right;
        }
    }

    return current ? current->data : TREE_NOT_FOUND;
}

void BinarySearchTree_Insert(Tree* self, TreeItem data)
{
    self->root = insert_node(self, self->root, data);
}

void BinarySearchTree_Remove(Tree* self, TreeItem data)
{
    self->root = remove_node(self, self->root, data);
}
