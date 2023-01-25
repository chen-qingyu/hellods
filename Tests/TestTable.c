#include "../Sources/Table/HashTable.h"

#include <assert.h>
#include <stdio.h>

void TestHashTable()
{
    // HashTable_Create HashTable_Size HashTable_IsEmpty
    HashTable* table = HashTable_Create();
    assert(HashTable_Size(table) == 0);
    assert(HashTable_IsEmpty(table) == true);

    // HashTable_Clear
    HashTable_Insert(table, "233", 233);
    assert(HashTable_Size(table) == 1);
    HashTable_Clear(table);
    assert(HashTable_Size(table) == 0);
    HashTable_Clear(table); // double clear
    assert(HashTable_Size(table) == 0);

    // HashTable_Insert
    HashTable_Insert(table, "aaa", 1);
    HashTable_Insert(table, "bbb", 2);
    HashTable_Insert(table, "ccc", 3);
    HashTable_Insert(table, "ddd", 4);

    // HashTable_Get
    assert(HashTable_Get(table, "aaa") == 1);
    assert(HashTable_Get(table, "bbb") == 2);
    assert(HashTable_Get(table, "ccc") == 3);
    assert(HashTable_Get(table, "ddd") == 4);

    // HashTable_Modify
    HashTable_Modify(table, "aaa", 233);
    assert(HashTable_Get(table, "aaa") == 233);

    // HashTable_Remove
    HashTable_Remove(table, "aaa");
    assert(HashTable_Get(table, "aaa") == HASH_TABLE_NOT_FOUND);

    // HashTable_Destroy
    HashTable_Destroy(table);

    printf("Hash Table Test OK.\n");
}
