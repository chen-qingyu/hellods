// Tested on Microsoft Visual Studio Community 2019: ALL PASSED

#include "../pch.h"

extern "C"
{
#include "../Sources/Table/HashTable.h"
}

TEST(Table, HashTable)
{
    // HashTable_Create HashTable_Size HashTable_IsEmpty
    HashTable* table = HashTable_Create();
    ASSERT_EQ(HashTable_Size(table), 0);
    ASSERT_EQ(HashTable_IsEmpty(table), true);

    // HashTable_Clear
    HashTable_Insert(table, "233", 233);
    ASSERT_EQ(HashTable_Size(table), 1);
    HashTable_Clear(table);
    ASSERT_EQ(HashTable_Size(table), 0);
    HashTable_Clear(table); // double clear
    ASSERT_EQ(HashTable_Size(table), 0);

    // HashTable_Insert
    HashTable_Insert(table, "aaa", 1);
    HashTable_Insert(table, "bbb", 2);
    HashTable_Insert(table, "ccc", 3);
    HashTable_Insert(table, "ddd", 4);
    HashTable_Insert(table, "eee", 5);
    HashTable_Insert(table, "fff", 6);
    ASSERT_EQ(HashTable_Size(table), 6);

    // HashTable_Get
    ASSERT_EQ(HashTable_Get(table, "aaa"), 1);
    ASSERT_EQ(HashTable_Get(table, "bbb"), 2);
    ASSERT_EQ(HashTable_Get(table, "ccc"), 3);
    ASSERT_EQ(HashTable_Get(table, "ddd"), 4);

    // HashTable_Modify
    HashTable_Modify(table, "aaa", 233);
    ASSERT_EQ(HashTable_Get(table, "aaa"), 233);

    // HashTable_Remove
    HashTable_Remove(table, "aaa");
    ASSERT_EQ(HashTable_Get(table, "aaa"), HASH_TABLE_NOT_FOUND);

    // HashTable_Destroy
    HashTable_Destroy(table);
}
