#include "HashTable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLE_CAPACITY 17

typedef enum
{
    EMPTY,
    FULL,
    DELETED
} TableState;

struct item
{
    TableKey key;
    TableValue value;
    TableState state;
};

/*******************************
Helper functions implementation.
*******************************/

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void* pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

static int hash(TableKey key)
{
    unsigned int index = 0;

    while (*key != '\0')
    {
        index = (index << 5) + *key++;
    }

    return index % HASHTABLE_CAPACITY;
}

static int find_pos(const Table* table, TableKey key)
{
    int current_pos = hash(key);
    int new_pos = current_pos;
    int conflict_cnt = 0;

    while (table[new_pos].state != EMPTY && strcmp(table[new_pos].key, key) != 0)
    {
        if (++conflict_cnt % 2)
        {
            new_pos = current_pos + (conflict_cnt + 1) * (conflict_cnt + 1) / 4;
            if (new_pos >= HASHTABLE_CAPACITY)
            {
                new_pos = new_pos % HASHTABLE_CAPACITY;
            }
        }
        else
        {
            new_pos = current_pos - conflict_cnt * conflict_cnt / 4;
            while (new_pos < 0)
            {
                new_pos += HASHTABLE_CAPACITY;
            }
        }
    }

    return new_pos;
}

/*******************************
Interface functions implementation.
*******************************/

Table* HashTable_Create(void)
{
    Table* table = (Table*)malloc(sizeof(struct item) * HASHTABLE_CAPACITY);
    check_pointer(table);

    for (int i = 0; i < HASHTABLE_CAPACITY; i++)
    {
        table[i].key = NULL;
        table[i].state = EMPTY;
    }

    return table;
}

void HashTable_Destroy(Table* self)
{
    for (int i = 0; i < HASHTABLE_CAPACITY; ++i)
    {
        if (self[i].key)
        {
            free(self[i].key);
        }
    }
    free(self);
}

TableValue HashTable_Get(const Table* self, TableKey key)
{
    int pos = find_pos(self, key);

    return self[pos].state == FULL ? self[pos].value : TABLE_NOT_FOUND;
}

void HashTable_Modify(Table* self, TableKey key, TableValue value)
{
    int pos = find_pos(self, key);

    if (self[pos].state == FULL)
    {
        self[pos].value = value;
    }
    else
    {
        fprintf(stderr, "ERROR: Key-value pair does not exist.\n");
        exit(EXIT_FAILURE);
    }
}

void HashTable_Insert(Table* self, TableKey key, TableValue value)
{
    int pos = find_pos(self, key);

    if (self[pos].state != FULL)
    {
        if (self[pos].state == DELETED)
        {
            free(self[pos].key);
            self[pos].key = NULL;
        }
        self[pos].state = FULL;
        self[pos].key = (char*)malloc(strlen(key) * sizeof(char) + 1);
        check_pointer(self[pos].key);

        strcpy(self[pos].key, key);
        self[pos].value = value;
    }
    else
    {
        fprintf(stderr, "ERROR: Key-value pair already exists.\n");
        exit(EXIT_FAILURE);
    }
}

void HashTable_Delete(Table* self, TableKey key)
{
    int pos = find_pos(self, key);

    if (self[pos].state == FULL)
    {
        self[pos].state = DELETED;
    }
    else
    {
        fprintf(stderr, "ERROR: Key-value pair does not exist.\n");
        exit(EXIT_FAILURE);
    }
}
