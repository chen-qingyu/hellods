#include <catch2/catch_test_macros.hpp>

extern "C"
{
#include "../sources/Table/HashTable.h"
}

TEST_CASE("Table: HashTable")
{
    // HashTable_Create HashTable_Size HashTable_IsEmpty
    HashTable* table = HashTable_Create();
    REQUIRE(HashTable_Size(table) == 0);
    REQUIRE(HashTable_IsEmpty(table) == true);

    // HashTable_Clear
    HashTable_Insert(table, "233", 233);
    REQUIRE(HashTable_Size(table) == 1);
    HashTable_Clear(table);
    REQUIRE(HashTable_Size(table) == 0);
    HashTable_Clear(table); // double clear
    REQUIRE(HashTable_Size(table) == 0);

    // HashTable_Insert
    HashTable_Insert(table, "aaa", 1);
    HashTable_Insert(table, "bbb", 2);
    HashTable_Insert(table, "ccc", 3);
    HashTable_Insert(table, "ddd", 4);
    HashTable_Insert(table, "eee", 5);
    HashTable_Insert(table, "fff", 6);
    REQUIRE(HashTable_Size(table) == 6);

    // HashTable_Get
    REQUIRE(HashTable_Get(table, "aaa") == 1);
    REQUIRE(HashTable_Get(table, "bbb") == 2);
    REQUIRE(HashTable_Get(table, "ccc") == 3);
    REQUIRE(HashTable_Get(table, "ddd") == 4);

    // HashTable_Modify
    HashTable_Modify(table, "aaa", 233);
    REQUIRE(HashTable_Get(table, "aaa") == 233);

    // HashTable_Remove
    HashTable_Remove(table, "aaa");
    REQUIRE(HashTable_Get(table, "aaa") == HASH_TABLE_NOT_FOUND);

    // HashTable_Destroy
    HashTable_Destroy(table);
}
