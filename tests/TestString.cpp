#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

extern "C"
{
#include "../sources/String/String.h"
}

TEST_CASE("String: String")
{
    String *s1, *s2, *s3, *s4, *s5;

    // Constructor String_Size String_IsEmpty

    s1 = String_Create();
    REQUIRE(String_Size(s1) == 0);
    REQUIRE(String_IsEmpty(s1) == true);

    s2 = String_From("Hello");
    REQUIRE(String_Size(s2) == 5);
    REQUIRE(String_IsEmpty(s2) == false);

    s3 = String_Copy(s2);
    REQUIRE(String_Size(s3) == 5);
    REQUIRE(String_IsEmpty(s3) == false);

    s4 = String_Move(s3);
    REQUIRE(String_Size(s4) == 5);
    REQUIRE(String_IsEmpty(s4) == false);
    REQUIRE(String_Size(s3) == 0);
    REQUIRE(String_IsEmpty(s3) == true);

    s5 = String_From("");
    REQUIRE(String_Size(s5) == 0);
    REQUIRE(String_IsEmpty(s5) == true);

    // String_CopyAssign

    String_Set(s1, "Hello");
    String_Set(s2, "World");
    String_CopyAssign(s1, s2);
    REQUIRE(String_Equal(s1, s2));

    // String_MoveAssign

    String_Set(s1, "Hello");
    String_Set(s2, "World");
    String_Set(s3, "World");
    String_Set(s4, "");
    String_MoveAssign(s1, s2);
    REQUIRE(String_Equal(s1, s3));
    REQUIRE(String_Equal(s2, s4));

    // String_Get String_Set

    String_Set(s1, "");
    String_Set(s2, "Hello World!");
    char* str = String_Get(s2);
    str[0] = 'Y';
    String_Set(s1, str);
    String_Set(s3, "Yello World!");
    REQUIRE(String_Equal(s1, s3));
    free(str);

    // String_At

    String_Set(s1, "Hello World!");
    REQUIRE(String_At(s1, 0) == 'H');
    REQUIRE(String_At(s1, 5) == ' ');
    REQUIRE(String_At(s1, 11) == '!');
    REQUIRE(String_At(s1, -1) == '!');
    REQUIRE(String_At(s1, -12) == 'H');

    // String_Equal

    String_Set(s1, "new string");
    String_Set(s2, "new string");
    REQUIRE(String_Equal(s1, s2) == true);
    String_Set(s2, "new string!");
    REQUIRE(String_Equal(s1, s2) == false);

    // String_Compare

    String_Set(s1, "ab");
    String_Set(s2, "abc");
    String_Set(s3, "abc");
    String_Set(s4, "abcd");
    REQUIRE(String_Compare(s1, s2) == LT);
    REQUIRE(String_Compare(s2, s3) == EQ);
    REQUIRE(String_Compare(s3, s4) == LT);
    REQUIRE(String_Compare(s4, s1) == GT);
    String_Set(s3, "abd");
    REQUIRE(String_Compare(s2, s3) == LT);
    String_Set(s2, "cbc");
    REQUIRE(String_Compare(s2, s3) == GT);

    // String_Find

    String_Set(s1, "");
    String_Set(s2, "a");
    String_Set(s3, "g");
    String_Set(s4, "cde");
    String_Set(s5, "abcdefg");
    REQUIRE(String_Find(s1, s1, 0, 1) == 0);
    REQUIRE(String_Find(s5, s1, 0, 7) == 0);
    REQUIRE(String_Find(s5, s2, 0, 7) == 0);
    REQUIRE(String_Find(s5, s3, 0, 7) == 6);
    REQUIRE(String_Find(s5, s4, 0, 7) == 2);
    REQUIRE(String_Find(s5, s5, 0, 7) == 0);
    String_Set(s1, " ");
    REQUIRE(String_Find(s5, s1, 0, 7) == -1);
    String_Set(s1, "ac");
    REQUIRE(String_Find(s5, s1, 0, 7) == -1);

    // String_ToDecimal

    String_Set(s1, "233.33");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(233.33));
    String_Set(s1, "1e+600");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(HUGE_VAL));
    String_Set(s1, "nan");
    REQUIRE(isnan(String_ToDecimal(s1)));
    String_Set(s1, "inf");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(INFINITY));

    String_Set(s1, "0");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(0));
    String_Set(s1, "-0");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(0));
    String_Set(s1, "+0");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(0));
    String_Set(s1, ".0");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(0));
    String_Set(s1, "0.");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(0));

    String_Set(s1, "1");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1.0));
    String_Set(s1, "-1");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(-1.0));
    String_Set(s1, "+1");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1.0));
    String_Set(s1, ".1");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(0.1));
    String_Set(s1, "1.");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1.0));

    String_Set(s1, "1e2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1e2));
    String_Set(s1, "-1e2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(-1e2));
    String_Set(s1, "+1e2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1e2));
    String_Set(s1, ".1e2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(0.1e2));
    String_Set(s1, "1.e2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1.e2));

    String_Set(s1, "1e+2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1e+2));
    String_Set(s1, "-1e+2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(-1e+2));
    String_Set(s1, "+1e+2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1e+2));
    String_Set(s1, ".1e+2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(0.1e+2));
    String_Set(s1, "1.e+2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1.e+2));

    String_Set(s1, "1e-2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1e-2));
    String_Set(s1, "-1e-2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(-1e-2));
    String_Set(s1, "+1e-2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1e-2));
    String_Set(s1, ".1e-2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(0.1e-2));
    String_Set(s1, "1.e-2");
    REQUIRE(String_ToDecimal(s1) == Catch::Approx(1.e-2));

    // String_ToInteger

    String_Set(s1, "233");
    REQUIRE(String_ToInteger(s1, 10) == 233);
    String_Set(s1, "cafebabe");
    REQUIRE(String_ToInteger(s1, 16) == 3405691582LL);
    String_Set(s1, "z");
    REQUIRE(String_ToInteger(s1, 36) == 35);

    String_Set(s1, "0001000");
    REQUIRE(String_ToInteger(s1, 10) == 1000);
    String_Set(s1, "1");
    REQUIRE(String_ToInteger(s1, 10) == 1);
    String_Set(s1, "0");
    REQUIRE(String_ToInteger(s1, 10) == 0);
    String_Set(s1, "f");
    REQUIRE(String_ToInteger(s1, 16) == 15);
    String_Set(s1, "11");
    REQUIRE(String_ToInteger(s1, 2) == 3);
    String_Set(s1, "zz");
    REQUIRE(String_ToInteger(s1, 36) == 35 * 36 + 35);
    String_Set(s1, "-1");
    REQUIRE(String_ToInteger(s1, 10) == -1);
    String_Set(s1, "-0");
    REQUIRE(String_ToInteger(s1, 10) == 0);
    String_Set(s1, "-10");
    REQUIRE(String_ToInteger(s1, 10) == -10);
    String_Set(s1, "-10");
    REQUIRE(String_ToInteger(s1, 16) == -16);
    String_Set(s1, "-z");
    REQUIRE(String_ToInteger(s1, 36) == -35);
    String_Set(s1, "+1");
    REQUIRE(String_ToInteger(s1, 10) == 1);
    String_Set(s1, "+0");
    REQUIRE(String_ToInteger(s1, 10) == 0);
    String_Set(s1, "+10");
    REQUIRE(String_ToInteger(s1, 10) == 10);
    String_Set(s1, "+10");
    REQUIRE(String_ToInteger(s1, 16) == 16);
    String_Set(s1, "+z");
    REQUIRE(String_ToInteger(s1, 36) == 35);
    String_Set(s1, "-0101");
    REQUIRE(String_ToInteger(s1, 2) == -5);
    String_Set(s1, "-1010");
    REQUIRE(String_ToInteger(s1, 2) == -10);
    String_Set(s1, "+0101");
    REQUIRE(String_ToInteger(s1, 2) == 5);
    String_Set(s1, "+1010");
    REQUIRE(String_ToInteger(s1, 2) == 10);
    String_Set(s1, "\n\r\n\t  233  \t\r\n\r");
    REQUIRE(String_ToInteger(s1, 10) == 233);

    // String_Count

    String_Set(s1, "Hello World");
    REQUIRE(String_Count(s1, ' ') == 1);
    REQUIRE(String_Count(s1, 'o') == 2);
    REQUIRE(String_Count(s1, 'l') == 3);
    REQUIRE(String_Count(s1, '!') == 0);
    String_Set(s1, "Hello World!!!");
    REQUIRE(String_Count(s1, '!') == 3);

    // String_Lower String_Upper

    String_Set(s1, "hahaha");
    String_Set(s2, "HAHAHA");
    String_Lower(s2);
    REQUIRE(String_Equal(s1, s2) == true);
    String_Upper(s1);
    REQUIRE(String_Equal(s1, s2) == false);
    String_Upper(s2);
    REQUIRE(String_Equal(s1, s2) == true);

    // String_Append

    String_Set(s1, "");
    String_Set(s2, "");
    String_Append(s1, s2);
    REQUIRE(String_Equal(s1, s2) == true);

    String_Set(s3, "lalala");
    String_Set(s4, "lalalalalala");
    String_Append(s1, s3);
    String_Append(s1, s1);
    REQUIRE(String_Equal(s1, s4) == true);

    // String_Erase

    String_Set(s1, "abcdefg");
    String_Erase(s1, 0, 1);
    String_Set(s2, "bcdefg");
    REQUIRE(String_Equal(s1, s2) == true);

    String_Set(s1, "abcdefg");
    String_Erase(s1, 1, 2);
    String_Set(s2, "acdefg");
    REQUIRE(String_Equal(s1, s2) == true);

    String_Set(s1, "abcdefg");
    String_Erase(s1, 1, 6);
    String_Set(s2, "ag");
    REQUIRE(String_Equal(s1, s2) == true);

    String_Set(s1, "abcdefg");
    String_Erase(s1, 0, 7);
    String_Set(s2, "");
    REQUIRE(String_Equal(s1, s2) == true);

    // String_Reverse

    String_Set(s1, "wooooow");
    String_Reverse(s1);
    REQUIRE(String_Equal(s1, s1) == true);

    String_Set(s2, "12345");
    String_Set(s3, "54321");
    String_Reverse(s2);
    REQUIRE(String_Equal(s2, s3) == true);

    // String_Replace

    String_Set(s1, "abcdefg");
    String_Set(s2, "a");
    String_Set(s3, "g");
    String_Replace(s1, s2, s3);
    String_Set(s4, "gbcdefg");
    REQUIRE(String_Equal(s1, s4) == true);

    String_Set(s1, "abcdefg");
    String_Set(s2, "g");
    String_Set(s3, "a");
    String_Replace(s1, s2, s3);
    String_Set(s4, "abcdefa");
    REQUIRE(String_Equal(s1, s4) == true);

    String_Set(s1, "abcdefg");
    String_Set(s2, "cde");
    String_Set(s3, "~~~");
    String_Replace(s1, s2, s3);
    String_Set(s4, "ab~~~fg");
    REQUIRE(String_Equal(s1, s4) == true);

    String_Set(s1, "abcdefg");
    String_Set(s2, "abcdefg");
    String_Set(s3, "");
    String_Replace(s1, s2, s3);
    String_Set(s4, "");
    REQUIRE(String_Equal(s1, s4) == true);

    String_Set(s1, "abcdefg");
    String_Set(s2, "abcdefg");
    String_Set(s3, "");
    String_Replace(s1, s2, s3);
    String_Set(s4, "");
    REQUIRE(String_Equal(s1, s4) == true);

    String_Set(s1, "");
    String_Set(s2, "abc");
    String_Set(s3, "~~~");
    String_Replace(s1, s2, s3);
    String_Set(s4, "");
    REQUIRE(String_Equal(s1, s4) == true);

    String_Set(s1, "hahaha");
    String_Set(s2, "h");
    String_Set(s3, "l");
    String_Replace(s1, s2, s3);
    String_Set(s4, "lalala");
    REQUIRE(String_Equal(s1, s4) == true);

    String_Set(s1, "hahaha");
    String_Set(s2, "a");
    String_Set(s3, "ooow~ ");
    String_Replace(s1, s2, s3);
    String_Set(s4, "hooow~ hooow~ hooow~ ");
    REQUIRE(String_Equal(s1, s4) == true);

    String_Set(s1, "hooow~ hooow~ hooow~ ");
    String_Set(s2, "ooo");
    String_Set(s3, "o");
    String_Replace(s1, s2, s3);
    String_Set(s4, "how~ how~ how~ ");
    REQUIRE(String_Equal(s1, s4) == true);

    // String_Strip

    String_Set(s1, "hello");

    String_Set(s2, "\t\nhello\t\n");
    String_Strip(s2);
    REQUIRE(String_Equal(s2, s1) == true);

    String_Set(s2, "           hello           ");
    String_Strip(s2);
    REQUIRE(String_Equal(s2, s1) == true);

    String_Set(s2, "\n\n\n\n \t\n\b\n   hello  \n\n\t\n \r\b\n\r");
    String_Strip(s2);
    REQUIRE(String_Equal(s2, s1) == true);

    // String_Swap

    String_Set(s1, "hello");
    String_Set(s2, "world");
    String_Swap(s1, s2);
    String_Set(s3, "hello");
    String_Set(s4, "world");
    REQUIRE(String_Equal(s1, s4) == true);
    REQUIRE(String_Equal(s2, s3) == true);

    // String_Clear

    String_Set(s1, "hello");
    String_Clear(s1);
    String_Set(s2, "");
    REQUIRE(String_Equal(s1, s2) == true);
    String_Clear(s1); // double clear
    REQUIRE(String_Equal(s1, s2) == true);

    // String_Split String_DestroyArray

    String** str_arr = NULL;

    String_Set(s1, "this is my code!");
    String_Set(s2, " ");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "this");
    REQUIRE(String_Equal(str_arr[0], s3) == true);
    String_Set(s3, "is");
    REQUIRE(String_Equal(str_arr[1], s3) == true);
    String_Set(s3, "my");
    REQUIRE(String_Equal(str_arr[2], s3) == true);
    String_Set(s3, "code!");
    REQUIRE(String_Equal(str_arr[3], s3) == true);
    REQUIRE(str_arr[4] == (String*)NULL);
    String_DestroyArray(str_arr);

    String_Set(s1, " this is my code! ");
    String_Set(s2, " ");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "");
    REQUIRE(String_Equal(str_arr[0], s3) == true);
    String_Set(s3, "this");
    REQUIRE(String_Equal(str_arr[1], s3) == true);
    String_Set(s3, "is");
    REQUIRE(String_Equal(str_arr[2], s3) == true);
    String_Set(s3, "my");
    REQUIRE(String_Equal(str_arr[3], s3) == true);
    String_Set(s3, "code!");
    REQUIRE(String_Equal(str_arr[4], s3) == true);
    REQUIRE(str_arr[5] == (String*)NULL);
    String_DestroyArray(str_arr);

    String_Set(s1, "aaa");
    String_Set(s2, "a");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "");
    for (int i = 0; i < 3; i++)
    {
        REQUIRE(String_Equal(str_arr[i], s3) == true);
    }
    REQUIRE(str_arr[3] == (String*)NULL);
    String_DestroyArray(str_arr);

    String_Set(s1, "this is my code!");
    String_Set(s2, "this is my code!");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "");
    REQUIRE(String_Equal(str_arr[0], s3) == true);
    REQUIRE(str_arr[1] == (String*)NULL);
    String_DestroyArray(str_arr);

    String_Set(s1, "one, two, three");
    String_Set(s2, ", ");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "one");
    REQUIRE(String_Equal(str_arr[0], s3) == true);
    String_Set(s3, "two");
    REQUIRE(String_Equal(str_arr[1], s3) == true);
    String_Set(s3, "three");
    REQUIRE(String_Equal(str_arr[2], s3) == true);
    REQUIRE(str_arr[3] == (String*)NULL);
    String_DestroyArray(str_arr);

    // String_Slice

    String_Set(s1, "12345");
    String* slice;

    slice = String_Slice(s1, -1, 1, 1);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, -1, 1, -1);
    String_Set(s2, "543");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, 1, -1, 1);
    String_Set(s2, "234");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, 1, -1, -1);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, 0, 5, 1);
    String_Set(s2, "12345");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, 0, 5, 2);
    String_Set(s2, "135");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, 0, 5, -1);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, 0, 5, -2);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, -1, -6, 1);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, -1, -6, 2);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, -1, -6, -1);
    String_Set(s2, "54321");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, -1, -6, -2);
    String_Set(s2, "531");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, 0, 0, 1);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, 1, 1, 1);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, -1, -1, 1);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    slice = String_Slice(s1, -1, -1, -1);
    String_Set(s2, "");
    REQUIRE(String_Equal(slice, s2) == true);
    String_Destroy(slice);

    // String_Destroy

    String_Destroy(s1);
    String_Destroy(s2);
    String_Destroy(s3);
    String_Destroy(s4);
    String_Destroy(s5);
}
