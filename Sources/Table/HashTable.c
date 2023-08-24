#include "HashTable.h"

#include <assert.h> // assert
#include <stdio.h>  // fprintf stderr
#include <stdlib.h> // malloc free exit EXIT_FAILURE NULL
#include <string.h> // strcmp strlen strcpy

#include "../common/utility.h"

#define INIT_CAPACITY 3

/// Hash Table State.
enum HashTableState
{
    EMPTY,
    FULL,
    REMOVED
};

/// Hash Table Pair.
struct HashTablePair
{
    /// Key of the key-value pair.
    HashTableKey key;

    /// Value of the key-value pair.
    HashTableValue value;

    /// State of the key-value pair.
    enum HashTableState state;
};

/// Hash Table.
struct HashTable
{
    /// Number of elements.
    int size;

    /// Available capacity.
    int capacity;

    /// Pointer to the pairs.
    struct HashTablePair* pairs;
};

/*
 * Helpers
 */

static int hash(HashTableKey key, int mod)
{
    unsigned int index = 0;

    while (*key != '\0')
    {
        index = (index << 5) + *key++;
    }

    return index % mod;
}

static int find_pos(const HashTable* table, HashTableKey key)
{
    int current_pos = hash(key, table->capacity);
    int new_pos = current_pos;
    int conflict_cnt = 0;

    while (table->pairs[new_pos].state != EMPTY && strcmp(table->pairs[new_pos].key, key) != 0)
    {
        if (++conflict_cnt % 2)
        {
            new_pos = current_pos + (conflict_cnt + 1) * (conflict_cnt + 1) / 4;
            if (new_pos >= table->capacity)
            {
                new_pos %= table->capacity;
            }
        }
        else
        {
            new_pos = current_pos - conflict_cnt * conflict_cnt / 4;
            while (new_pos < 0)
            {
                new_pos += table->capacity;
            }
        }
    }

    return new_pos;
}

// Remove all of the elements.
static inline void clear(HashTable* self)
{
    for (int i = 0; i < self->capacity; ++i)
    {
        if (self->pairs[i].key)
        {
            free((char*)self->pairs[i].key);
            self->pairs[i].key = NULL;
        }
        self->pairs[i].state = EMPTY;
    }

    self->size = 0;
}

// Calculate the next prime that > n
static inline int next_prime(int n)
{
    assert(n > 1);

    while (n < INT_MAX)
    {
        n++;
        bool is_prime = true;
        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                is_prime = false;
                break; // n is not prime, continue while loop
            }
        }
        if (is_prime)
        {
            break; // n is prime, return
        }
    }

    assert(n < INT_MAX);

    return n;
}

// Expand capacity and rehash.
static inline void expand_capacity(HashTable* self)
{
    int old_capacity = self->capacity;
    struct HashTablePair* old_pairs = self->pairs;

    // expand to the next prime greater than twice the current capacity
    int new_capacity = next_prime(self->capacity * 2);

    // create new pairs
    struct HashTablePair* new_pairs = (struct HashTablePair*)malloc(sizeof(struct HashTablePair) * new_capacity);
    check_pointer(new_pairs);
    for (int i = 0; i < new_capacity; i++)
    {
        new_pairs[i].key = NULL;
        new_pairs[i].state = EMPTY;
    }

    // move elements (rehash)
    self->pairs = new_pairs;
    self->capacity = new_capacity;
    self->size = 0;
    for (int i = 0; i < old_capacity; i++)
    {
        if (old_pairs[i].state == FULL)
        {
            HashTable_Insert(self, old_pairs[i].key, old_pairs[i].value);
        }
    }

    // free old pairs
    for (int i = 0; i < old_capacity; ++i)
    {
        if (old_pairs[i].key)
        {
            free((char*)old_pairs[i].key);
        }
    }
    free(old_pairs);
}

/*
 * Functions
 */

HashTable* HashTable_Create(void)
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    check_pointer(table);

    table->size = 0;
    table->capacity = INIT_CAPACITY;
    table->pairs = (struct HashTablePair*)malloc(sizeof(struct HashTablePair) * table->capacity);
    check_pointer(table->pairs);
    for (int i = 0; i < table->capacity; i++)
    {
        table->pairs[i].key = NULL;
        table->pairs[i].state = EMPTY;
    }

    return table;
}

void HashTable_Destroy(HashTable* self)
{
    // let it crush if self is invalid

    clear(self);

    free(self->pairs);
    free(self);
}

int HashTable_Size(const HashTable* self)
{
    return self->size;
}

bool HashTable_IsEmpty(const HashTable* self)
{
    return self->size == 0;
}

HashTableValue HashTable_Get(const HashTable* self, HashTableKey key)
{
    int pos = find_pos(self, key);

    return self->pairs[pos].state == FULL ? self->pairs[pos].value : HASH_TABLE_NOT_FOUND;
}

void HashTable_Modify(HashTable* self, HashTableKey key, HashTableValue value)
{
    int pos = find_pos(self, key);

    if (self->pairs[pos].state == FULL)
    {
        self->pairs[pos].value = value;
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

    if (self->pairs[pos].state != FULL)
    {
        if (self->pairs[pos].state == REMOVED)
        {
            free((char*)self->pairs[pos].key);
            self->pairs[pos].key = NULL;
        }
        self->pairs[pos].state = FULL;
        self->pairs[pos].key = (char*)malloc(strlen(key) * sizeof(char) + 1);
        check_pointer(self->pairs[pos].key);

        strcpy((char*)self->pairs[pos].key, key);
        self->pairs[pos].value = value;

        self->size++;

        // expand_capacity when the loading factor is too large (> 0.5)
        if (self->size * 2 > self->capacity)
        {
            expand_capacity(self);
        }
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

    if (self->pairs[pos].state == FULL)
    {
        self->pairs[pos].state = REMOVED;

        self->size--;
    }
    else
    {
        fprintf(stderr, "ERROR: Key-value pair does not exist.\n");
        exit(EXIT_FAILURE);
    }
}

void HashTable_Clear(HashTable* self)
{
    if (self->size != 0)
    {
        clear(self);
    }
}
