#include "../Sources/String/String.h"

#include <assert.h>
#include <float.h>
#include <stdio.h>

static bool feq(const double a, const double b)
{
    return fabs(a - b) < DBL_EPSILON;
}

void TestString(void)
{
    // String_Create() String_Size() String_IsEmpty() String_Set()

    String* s1 = String_Create();
    assert(String_Size(s1) == 0);
    assert(String_IsEmpty(s1) == true);

    String_Set(s1, "Hello");
    assert(String_Size(s1) == 5);
    assert(String_IsEmpty(s1) == false);

    String_Set(s1, "Hello World!");
    assert(String_Size(s1) == 12);
    assert(String_IsEmpty(s1) == false);

    // String_Equal() String_At()

    String_Set(s1, "Hello World!");
    String* s2 = String_Create();
    assert(String_Equal(s1, s2) == false);
    String_Set(s2, "Hello World!");
    assert(String_Equal(s1, s2) == true);

    assert(String_At(s2, 0) == 'H');
    assert(String_At(s2, 5) == ' ');
    assert(String_At(s2, 11) == '!');
    assert(String_At(s2, -1) == '!');
    assert(String_At(s2, -String_Size(s2)) == 'H');

    // String_Reverse()

    String* s3 = String_Create();
    String* s4 = String_Create();
    String_Reverse(s3);
    assert(String_Equal(s3, s4) == true);

    String_Set(s3, "12345");
    String_Set(s4, "54321");
    String_Reverse(s3);
    assert(String_Equal(s3, s4) == true);

    // String_Lower() String_Upper()

    String_Set(s3, "hahaha");
    String_Set(s4, "HAHAHA");
    String_Lower(s4);
    assert(String_Equal(s3, s4) == true);
    String_Upper(s3);
    assert(String_Equal(s3, s4) == false);
    String_Upper(s4);
    assert(String_Equal(s3, s4) == true);

    // String_Copy()

    String* s5 = String_Copy(s4);
    assert(String_Equal(s4, s5) == true);

    // String_Compare()

    String_Set(s2, "ab");
    String_Set(s3, "abc");
    String_Set(s4, "abc");
    String_Set(s5, "abcd");
    assert(String_Compare(s2, s3) == LT);
    assert(String_Compare(s3, s4) == EQ);
    assert(String_Compare(s4, s5) == LT);
    assert(String_Compare(s5, s2) == GT);
    String_Set(s4, "abd");
    assert(String_Compare(s3, s4) == LT);
    String_Set(s3, "cbc");
    assert(String_Compare(s3, s4) == GT);

    // String_Find()

    String_Set(s1, "");
    String_Set(s2, "a");
    String_Set(s3, "g");
    String_Set(s4, "cde");
    String_Set(s5, "abcdefg");
    assert(String_Find(s1, s1, 0, 1) == 0);
    assert(String_Find(s5, s1, 0, 7) == 0);
    assert(String_Find(s5, s2, 0, 7) == 0);
    assert(String_Find(s5, s3, 0, 7) == 6);
    assert(String_Find(s5, s4, 0, 7) == 2);
    assert(String_Find(s5, s5, 0, 7) == 0);
    String_Set(s1, " ");
    assert(String_Find(s5, s1, 0, 7) == STRING_NOT_FOUND);
    String_Set(s1, "ac");
    assert(String_Find(s5, s1, 0, 7) == STRING_NOT_FOUND);

    // String_Append()

    String_Set(s1, "");
    String_Set(s5, "");
    String_Append(s1, s5);
    assert(String_Equal(s1, s5) == true);
    String_Append(s1, s2);
    assert(String_Equal(s1, s2) == true);
    String_Append(s1, s3);
    String_Append(s1, s4);
    String_Set(s5, "agcde");
    assert(String_Equal(s1, s5) == true);

    // String_Erase()

    String_Set(s1, "abcdefg");
    String_Erase(s1, 0, 1);
    String_Set(s2, "bcdefg");
    assert(String_Equal(s1, s2) == true);

    String_Set(s1, "abcdefg");
    String_Erase(s1, 1, 2);
    String_Set(s2, "acdefg");
    assert(String_Equal(s1, s2) == true);

    String_Set(s1, "abcdefg");
    String_Erase(s1, 1, 6);
    String_Set(s2, "ag");
    assert(String_Equal(s1, s2) == true);

    String_Set(s1, "abcdefg");
    String_Erase(s1, 0, 7);
    String_Set(s2, "");
    assert(String_Equal(s1, s2) == true);

    String_Set(s1, "abcdefg");
    String_Erase(s1, -1, 99);
    String_Set(s2, "");
    assert(String_Equal(s1, s2) == true);

    // String_Replace()

    String_Set(s1, "abcdefg");
    String_Set(s2, "a");
    String_Set(s3, "g");
    String_Replace(s1, s2, s3);
    String_Set(s4, "gbcdefg");
    assert(String_Equal(s1, s4) == true);

    String_Set(s1, "abcdefg");
    String_Set(s2, "g");
    String_Set(s3, "a");
    String_Replace(s1, s2, s3);
    String_Set(s4, "abcdefa");
    assert(String_Equal(s1, s4) == true);

    String_Set(s1, "abcdefg");
    String_Set(s2, "cde");
    String_Set(s3, "~~~");
    String_Replace(s1, s2, s3);
    String_Set(s4, "ab~~~fg");
    assert(String_Equal(s1, s4) == true);

    String_Set(s1, "abcdefg");
    String_Set(s2, "abcdefg");
    String_Set(s3, "");
    String_Replace(s1, s2, s3);
    String_Set(s4, "");
    assert(String_Equal(s1, s4) == true);

    String_Set(s1, "abcdefg");
    String_Set(s2, "abcdefg");
    String_Set(s3, "");
    String_Replace(s1, s2, s3);
    String_Set(s4, "");
    assert(String_Equal(s1, s4) == true);

    String_Set(s1, "");
    String_Set(s2, "abc");
    String_Set(s3, "~~~");
    String_Replace(s1, s2, s3);
    String_Set(s4, "");
    assert(String_Equal(s1, s4) == true);

    String_Set(s1, "hahaha");
    String_Set(s2, "h");
    String_Set(s3, "l");
    String_Replace(s1, s2, s3);
    String_Set(s4, "lalala");
    assert(String_Equal(s1, s4) == true);

    String_Set(s1, "hahaha");
    String_Set(s2, "a");
    String_Set(s3, "ooow~ ");
    String_Replace(s1, s2, s3);
    String_Set(s4, "hooow~ hooow~ hooow~ ");
    assert(String_Equal(s1, s4) == true);

    String_Set(s1, "hooow~ hooow~ hooow~ ");
    String_Set(s2, "ooo");
    String_Set(s3, "o");
    String_Replace(s1, s2, s3);
    String_Set(s4, "how~ how~ how~ ");
    assert(String_Equal(s1, s4) == true);

    // String_Split() String_DestroyArray()

    String** str_arr = NULL;

    String_Set(s1, "this is my code!");
    String_Set(s2, " ");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "this");
    assert(String_Equal(str_arr[0], s3) == true);
    String_Set(s3, "is");
    assert(String_Equal(str_arr[1], s3) == true);
    String_Set(s3, "my");
    assert(String_Equal(str_arr[2], s3) == true);
    String_Set(s3, "code!");
    assert(String_Equal(str_arr[3], s3) == true);
    assert(str_arr[4] == NULL);
    String_DestroyArray(str_arr);

    String_Set(s1, " this is my code! ");
    String_Set(s2, " ");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "");
    assert(String_Equal(str_arr[0], s3) == true);
    String_Set(s3, "this");
    assert(String_Equal(str_arr[1], s3) == true);
    String_Set(s3, "is");
    assert(String_Equal(str_arr[2], s3) == true);
    String_Set(s3, "my");
    assert(String_Equal(str_arr[3], s3) == true);
    String_Set(s3, "code!");
    assert(String_Equal(str_arr[4], s3) == true);
    assert(str_arr[5] == NULL);
    String_DestroyArray(str_arr);

    String_Set(s1, "aaa");
    String_Set(s2, "a");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "");
    assert(str_arr[3] == NULL);
    for (int i = 0; i < 3; i++)
    {
        assert(String_Equal(str_arr[i], s3) == true);
    }
    String_DestroyArray(str_arr);

    String_Set(s1, "this is my code!");
    String_Set(s2, "this is my code!");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "");
    assert(String_Equal(str_arr[0], s3) == true);
    assert(str_arr[1] == NULL);
    String_DestroyArray(str_arr);

    String_Set(s1, "one, two, three");
    String_Set(s2, ", ");
    str_arr = String_Split(s1, s2);

    String_Set(s3, "one");
    assert(String_Equal(str_arr[0], s3) == true);
    String_Set(s3, "two");
    assert(String_Equal(str_arr[1], s3) == true);
    String_Set(s3, "three");
    assert(String_Equal(str_arr[2], s3) == true);
    assert(str_arr[3] == NULL);
    String_DestroyArray(str_arr);

    // String_Strip()

    String_Set(s1, "\t\nhello\t\n");
    String_Strip(s1);
    String_Set(s2, "hello");
    assert(String_Equal(s1, s2) == true);

    String_Set(s1, "           hello           ");
    String_Strip(s1);
    String_Set(s2, "hello");
    assert(String_Equal(s1, s2) == true);

    String_Set(s1, "\n\n\n\n \t\n\b\n   hello  \n\n\t\n \r\b\n\r");
    String_Strip(s1);
    String_Set(s2, "hello");
    assert(String_Equal(s1, s2) == true);

    // String_ToInteger()

    String_Set(s1, "233");
    assert(String_ToInteger(s1, 10) == 233);
    String_Set(s1, "cafebabe");
    assert(String_ToInteger(s1, 16) == 3405691582LL);
    String_Set(s1, "z");
    assert(String_ToInteger(s1, 36) == 35);

    String_Set(s1, "0001000");
    assert(String_ToInteger(s1, 10) == 1000);
    String_Set(s1, "1");
    assert(String_ToInteger(s1, 10) == 1);
    String_Set(s1, "0");
    assert(String_ToInteger(s1, 10) == 0);
    String_Set(s1, "f");
    assert(String_ToInteger(s1, 16) == 15);
    String_Set(s1, "11");
    assert(String_ToInteger(s1, 2) == 3);
    String_Set(s1, "zz");
    assert(String_ToInteger(s1, 36) == 35 * 36 + 35);
    String_Set(s1, "-1");
    assert(String_ToInteger(s1, 10) == -1);
    String_Set(s1, "-0");
    assert(String_ToInteger(s1, 10) == 0);
    String_Set(s1, "-10");
    assert(String_ToInteger(s1, 10) == -10);
    String_Set(s1, "-10");
    assert(String_ToInteger(s1, 16) == -16);
    String_Set(s1, "-z");
    assert(String_ToInteger(s1, 36) == -35);
    String_Set(s1, "+1");
    assert(String_ToInteger(s1, 10) == 1);
    String_Set(s1, "+0");
    assert(String_ToInteger(s1, 10) == 0);
    String_Set(s1, "+10");
    assert(String_ToInteger(s1, 10) == 10);
    String_Set(s1, "+10");
    assert(String_ToInteger(s1, 16) == 16);
    String_Set(s1, "+z");
    assert(String_ToInteger(s1, 36) == 35);
    String_Set(s1, "-0101");
    assert(String_ToInteger(s1, 2) == -5);
    String_Set(s1, "-1010");
    assert(String_ToInteger(s1, 2) == -10);
    String_Set(s1, "+0101");
    assert(String_ToInteger(s1, 2) == 5);
    String_Set(s1, "+1010");
    assert(String_ToInteger(s1, 2) == 10);
    String_Set(s1, "\n\r\n\t  233  \t\r\n\r");
    assert(String_ToInteger(s1, 10) == 233);

    // String_ToDecimal()

    String_Set(s1, "233.33");
    assert(String_ToDecimal(s1) == 233.33);
    String_Set(s1, "1e+600");
    assert(String_ToDecimal(s1) == HUGE_VAL);
    String_Set(s1, "nan");
    assert(isnan(String_ToDecimal(s1)));
    String_Set(s1, "inf");
    assert(String_ToDecimal(s1) == INFINITY);

    String_Set(s1, "0");
    assert(String_ToDecimal(s1) == 0);
    String_Set(s1, "-0");
    assert(String_ToDecimal(s1) == 0);
    String_Set(s1, "+0");
    assert(String_ToDecimal(s1) == 0);
    String_Set(s1, ".0");
    assert(String_ToDecimal(s1) == 0);
    String_Set(s1, "0.");
    assert(String_ToDecimal(s1) == 0);

    String_Set(s1, "1");
    assert(String_ToDecimal(s1) == 1.0);
    String_Set(s1, "-1");
    assert(String_ToDecimal(s1) == -1.0);
    String_Set(s1, "+1");
    assert(String_ToDecimal(s1) == 1.0);
    String_Set(s1, ".1");
    assert(String_ToDecimal(s1) == 0.1);
    String_Set(s1, "1.");
    assert(String_ToDecimal(s1) == 1.0);

    String_Set(s1, "1e2");
    assert(String_ToDecimal(s1) == 1e2);
    String_Set(s1, "-1e2");
    assert(String_ToDecimal(s1) == -1e2);
    String_Set(s1, "+1e2");
    assert(String_ToDecimal(s1) == 1e2);
    String_Set(s1, ".1e2");
    assert(String_ToDecimal(s1) == 0.1e2);
    String_Set(s1, "1.e2");
    assert(String_ToDecimal(s1) == 1.e2);

    String_Set(s1, "1e+2");
    assert(String_ToDecimal(s1) == 1e+2);
    String_Set(s1, "-1e+2");
    assert(String_ToDecimal(s1) == -1e+2);
    String_Set(s1, "+1e+2");
    assert(String_ToDecimal(s1) == 1e+2);
    String_Set(s1, ".1e+2");
    assert(String_ToDecimal(s1) == 0.1e+2);
    String_Set(s1, "1.e+2");
    assert(String_ToDecimal(s1) == 1.e+2);

    String_Set(s1, "1e-2");
    assert(feq(String_ToDecimal(s1), 1e-2));
    String_Set(s1, "-1e-2");
    assert(feq(String_ToDecimal(s1), -1e-2));
    String_Set(s1, "+1e-2");
    assert(feq(String_ToDecimal(s1), 1e-2));
    String_Set(s1, ".1e-2");
    assert(feq(String_ToDecimal(s1), 0.1e-2));
    String_Set(s1, "1.e-2");
    assert(feq(String_ToDecimal(s1), 1.e-2));

    String_Set(s1, "0.0001");
    assert(feq(String_ToDecimal(s1), 0.0001));
    String_Set(s1, "0.000101");
    assert(!feq(String_ToDecimal(s1), 0.0001));

    String_Set(s1, "0.123e10");
    assert(feq(String_ToDecimal(s1), 0.123e10));
    String_Set(s1, "0.123e01");
    assert(!feq(String_ToDecimal(s1), 0.123e10));

    // String_From()

    String* s6 = String_From("new string");
    String_Set(s1, "new string");
    assert(String_Equal(s1, s6));
    String_Set(s1, "new string!");
    assert(String_Equal(s1, s6) == false);

    char s[] = "null-terminated byte string.";
    String* s7 = String_From(s);
    String_Set(s1, s);
    assert(String_Equal(s1, s7));
    s[0] = ' ';
    assert(String_Equal(s1, s7));

    // String_Count
    String_Set(s1, "Hello World");
    assert(String_Count(s1, ' ') == 1);
    assert(String_Count(s1, 'o') == 2);
    assert(String_Count(s1, 'l') == 3);
    assert(String_Count(s1, '!') == 0);
    String_Set(s1, "Hello World!!!");
    assert(String_Count(s1, '!') == 3);

    // String_Destroy()

    String_Destroy(s1);
    String_Destroy(s2);
    String_Destroy(s3);
    String_Destroy(s4);
    String_Destroy(s5);
    String_Destroy(s6);
    String_Destroy(s7);

    printf("String Test OK.\n");
}
