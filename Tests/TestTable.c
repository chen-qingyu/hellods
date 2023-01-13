#include "../Sources/Table/HashTable.h"

#include <assert.h>
#include <stdio.h>

void TestHashTable()
{
    // HashTable_Create
    HashTable* table = HashTable_Create();

    // HashTable_Insert
    HashTable_Insert(table, (char*)"aaa", 1);
    HashTable_Insert(table, (char*)"bbb", 2);
    HashTable_Insert(table, (char*)"ccc", 3);
    HashTable_Insert(table, (char*)"ddd", 4);

    // HashTable_Get
    assert(HashTable_Get(table, (char*)"aaa") == 1);
    assert(HashTable_Get(table, (char*)"bbb") == 2);
    assert(HashTable_Get(table, (char*)"ccc") == 3);
    assert(HashTable_Get(table, (char*)"ddd") == 4);

    // HashTable_Modify
    HashTable_Modify(table, (char*)"aaa", 233);
    assert(HashTable_Get(table, (char*)"aaa") == 233);

    // HashTable_Remove
    HashTable_Remove(table, (char*)"aaa");
    assert(HashTable_Get(table, (char*)"aaa") == HASH_TABLE_NOT_FOUND);

    // HashTable_Destroy
    HashTable_Destroy(table);

    printf("Hash Table Test OK.\n");
}
