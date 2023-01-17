#include "HashTable.h"

#include <stdio.h>  // fprintf stderr
#include <stdlib.h> // malloc free exit EXIT_FAILURE NULL
#include <string.h> // strcmp strlen strcpy

#include "../common/check_pointer.h"

// TODO 动态增长
#define MAX_CAPACITY 17

enum HashTableState
{
    EMPTY,
    FULL,
    REMOVED
};

struct HashTable
{
    /// Key of the key-value pair.
    HashTableKey key;

    /// Value of the key-value pair.
    HashTableValue value;

    /// State of the key-value pair.
    enum HashTableState state;
};

/*******************************
Helper functions implementation.
*******************************/

static int hash(HashTableKey key)
{
    unsigned int index = 0;

    while (*key != '\0')
    {
        index = (index << 5) + *key++;
    }

    return index % MAX_CAPACITY;
}

static int find_pos(const HashTable* table, HashTableKey key)
{
    int current_pos = hash(key);
    int new_pos = current_pos;
    int conflict_cnt = 0;

    while (table[new_pos].state != EMPTY && strcmp(table[new_pos].key, key) != 0)
    {
        if (++conflict_cnt % 2)
        {
            new_pos = current_pos + (conflict_cnt + 1) * (conflict_cnt + 1) / 4;
            if (new_pos >= MAX_CAPACITY)
            {
                new_pos = new_pos % MAX_CAPACITY;
            }
        }
        else
        {
            new_pos = current_pos - conflict_cnt * conflict_cnt / 4;
            while (new_pos < 0)
            {
                new_pos += MAX_CAPACITY;
            }
        }
    }

    return new_pos;
}

/*******************************
Interface functions implementation.
*******************************/

HashTable* HashTable_Create(void)
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable) * MAX_CAPACITY);
    check_pointer(table);

    for (int i = 0; i < MAX_CAPACITY; i++)
    {
        table[i].key = NULL;
        table[i].state = EMPTY;
    }

    return table;
}

void HashTable_Destroy(HashTable* self)
{
    // let it crush if self is invalid

    for (int i = 0; i < MAX_CAPACITY; ++i)
    {
        if (self[i].key)
        {
            free(self[i].key);
        }
    }
    free(self);
}

HashTableValue HashTable_Get(const HashTable* self, HashTableKey key)
{
    int pos = find_pos(self, key);

    return self[pos].state == FULL ? self[pos].value : HASH_TABLE_NOT_FOUND;
}

void HashTable_Modify(HashTable* self, HashTableKey key, HashTableValue value)
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

void HashTable_Insert(HashTable* self, HashTableKey key, HashTableValue value)
{
    int pos = find_pos(self, key);

    if (self[pos].state != FULL)
    {
        if (self[pos].state == REMOVED)
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

void HashTable_Remove(HashTable* self, HashTableKey key)
{
    int pos = find_pos(self, key);

    if (self[pos].state == FULL)
    {
        self[pos].state = REMOVED;
    }
    else
    {
        fprintf(stderr, "ERROR: Key-value pair does not exist.\n");
        exit(EXIT_FAILURE);
    }
}
