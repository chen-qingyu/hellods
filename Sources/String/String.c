/**
 * @file String.c
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief My simple C string library implementation.
 *        Because the <string.h> is too crude to use, so I wrote one myself.
 * @version 1.0
 * @date 2022.11.03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "String.h"

#include <math.h>   // pow INFINITY NAN
#include <stdio.h>  // fprintf stderr
#include <stdlib.h> // malloc realloc free exit EXIT_FAILURE NULL

#include "../common/check_bounds.h"
#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

/*******************************
 * Type definition.
 *******************************/

// String structure definition.
struct string
{
    // Number of chars.
    int size;

    // Available capacity.
    int capacity;

    // Pointer to the data.
    char* data;
};

// String initial capacity.
#define INIT_CAPACITY 8

// Used for FSM
enum state
{
    S_BEGIN_BLANK = 1 << 0,        // begin blank character
    S_SIGN = 1 << 1,               // positive or negative sign
    S_INT_PART = 1 << 2,           // integer part
    S_DEC_POINT_HAS_LEFT = 1 << 3, // decimal point has left digit
    S_DEC_POINT_NOT_LEFT = 1 << 4, // decimal point doesn't have left digit
    S_DEC_PART = 1 << 5,           // decimal part
    S_EXP = 1 << 6,                // scientific notation identifier
    S_EXP_SIGN = 1 << 7,           // positive or negative sign of exponent part
    S_EXP_PART = 1 << 8,           // exponent part
    S_END_BLANK = 1 << 9,          // end blank character
    S_OTHER = 1 << 10,             // other
};

// Used for FSM
enum event
{
    E_BLANK = 1 << 11,     // blank character: '\n', '\r', '\t', ' '
    E_SIGN = 1 << 12,      // positive or negative sign: '+', '-'
    E_NUMBER = 1 << 13,    // number: '[0-9a-zA-Z]'
    E_DEC_POINT = 1 << 14, // decimal point: '.'
    E_EXP = 1 << 15,       // scientific notation identifier: 'e', 'E'
    E_OTHER = 1 << 16,     // other
};

/*******************************
 * Helper function definition.
 *******************************/

// Use the KMP algorithm to find the position of the pattern.
static inline int kmp(const char* str, const char* pattern, int n, int m)
{
    if (n < m)
    {
        return STRING_NOT_FOUND;
    }

    if (m == 0) // "" is in any string at index 0.
    {
        return 0;
    }

    int* match = (int*)malloc(sizeof(int) * m);
    check_pointer(match);
    match[0] = STRING_NOT_FOUND;

    for (int j = 1; j < m; j++)
    {
        int i = match[j - 1];
        while ((i >= 0) && (pattern[i + 1] != pattern[j]))
        {
            i = match[i];
        }
        match[j] = (pattern[i + 1] == pattern[j]) ? i + 1 : STRING_NOT_FOUND;
    }

    int s = 0;
    int p = 0;
    while (s < n && p < m)
    {
        if (str[s] == pattern[p])
        {
            s++;
            p++;
        }
        else if (p > 0)
        {
            p = match[p - 1] + 1;
        }
        else
        {
            s++;
        }
    }

    free(match);

    return (p == m) ? (s - m) : STRING_NOT_FOUND;
}

// Calculate the length of null-terminated byte string (exclude '\0').
static inline int length(const char* chars)
{
    int len = 0;
    while (*chars != '\0')
    {
        chars++;
        len++;
    }
    return len;
}

// Try to transform a character to an integer based on 2-36 base.
static inline int char_to_integer(char digit, int base) // 2 <= base <= 36
{
    static const char* upper_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char* lower_digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < base; ++i)
    {
        if (digit == upper_digits[i] || digit == lower_digits[i])
        {
            return i;
        }
    }
    return -1; // not an integer
}

// Try to transform a character to an event.
static inline enum event get_event(char ch, int base)
{
    if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')
    {
        return E_BLANK;
    }
    else if (char_to_integer(ch, base) != -1)
    {
        return E_NUMBER;
    }
    else if (ch == '-' || ch == '+')
    {
        return E_SIGN;
    }
    else if (ch == '.')
    {
        return E_DEC_POINT;
    }
    else if (ch == 'e' || ch == 'E')
    {
        return E_EXP;
    }
    return E_OTHER;
}

// Append a char.
static inline void append_char(String* self, const char ch)
{
    check_full(self->size + 1, INT_MAX); // be careful: '\0'

    if (self->size + 1 == self->capacity) // need to expand capacity
    {
        self->capacity = (self->capacity < INT_MAX / 2) ? self->capacity * 2 : INT_MAX; // double the capacity until INT_MAX
        self->data = (char*)realloc(self->data, sizeof(char) * self->capacity);
        check_pointer(self->data);
    }

    self->data[self->size++] = ch;
    self->data[self->size] = '\0';
}

/*******************************
 * Interface functions definition.
 *******************************/

/**
 * Constructor / Destructor
 */

String* String_Create(void)
{
    String* str = (String*)malloc(sizeof(String));
    check_pointer(str);
    str->size = 0;
    str->capacity = INIT_CAPACITY;
    str->data = (char*)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    str->data[0] = '\0';

    return str;
}

String* String_From(const char* chars)
{
    String* str = (String*)malloc(sizeof(String));
    check_pointer(str);
    str->size = length(chars);
    str->capacity = str->size + 1; // '\0'
    str->data = (char*)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    for (int i = 0; i < str->size; ++i)
    {
        str->data[i] = chars[i];
    }
    str->data[str->size] = '\0';

    return str;
}

String* String_Copy(const String* str)
{
    String* copy = (String*)malloc(sizeof(String));
    check_pointer(copy);
    copy->size = str->size;
    copy->capacity = str->capacity;
    copy->data = (char*)malloc(sizeof(char) * copy->capacity);
    check_pointer(copy->data);
    for (int i = 0; i < copy->size; i++)
    {
        copy->data[i] = str->data[i];
    }
    copy->data[copy->size] = '\0';

    return copy;
}

String* String_Move(String* str)
{
    String* move = (String*)malloc(sizeof(String));
    check_pointer(move);
    move->size = str->size;
    move->capacity = str->capacity;
    move->data = str->data;

    str->size = 0;
    str->capacity = INIT_CAPACITY;
    str->data = (char*)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    str->data[0] = '\0';

    return move;
}

void String_Destroy(String* self)
{
    if (self != NULL)
    {
        free(self->data);
        free(self);
    }
}

/**
 * Assignment
 */

void String_CopyAssign(String* self, const String* that)
{
    free(self->data);

    self->size = that->size;
    self->capacity = that->capacity;
    self->data = (char*)malloc(sizeof(char) * self->capacity);
    check_pointer(self->data);
    for (int i = 0; i < self->size; i++)
    {
        self->data[i] = that->data[i];
    }
    self->data[self->size] = '\0';
}

void String_MoveAssign(String* self, String* that)
{
    free(self->data);

    self->size = that->size;
    self->capacity = that->capacity;
    self->data = that->data;

    that->size = 0;
    that->capacity = INIT_CAPACITY;
    that->data = (char*)malloc(sizeof(char) * that->capacity);
    check_pointer(that->data);
    that->data[0] = '\0';
}

/**
 * Getter / Setter
 */

char* String_Get(const String* self)
{
    char* chars = (char*)malloc(sizeof(char) * self->size + 1);
    check_pointer(chars);
    for (int i = 0; i < self->size; ++i)
    {
        chars[i] = self->data[i];
    }
    chars[self->size] = '\0';
    return chars;
}

void String_Set(String* self, const char* chars)
{
    free(self->data);

    self->size = length(chars);
    self->capacity = self->size + 1; // '\0'
    self->data = (char*)malloc(sizeof(char) * self->capacity);
    check_pointer(self->data);
    for (int i = 0; i < self->size; ++i)
    {
        self->data[i] = chars[i];
    }
    self->data[self->size] = '\0';
}

/**
 * Examination (will not change the object itself)
 */

int String_Size(const String* self)
{
    return self->size;
}

bool String_IsEmpty(const String* self)
{
    return self->size == 0;
}

void String_Print(const String* self)
{
    printf("%s\n", self->data);
}

char String_At(const String* self, int i)
{
    check_bounds(i, -self->size, self->size);

    return i >= 0 ? self->data[i] : self->data[i + self->size];
}

bool String_Equal(const String* self, const String* that)
{
    if (self->size != that->size)
    {
        return false;
    }

    for (int i = 0; i < self->size; ++i)
    {
        if (self->data[i] != that->data[i])
        {
            return false;
        }
    }

    return true;
}

enum order String_Compare(const String* self, const String* that)
{
    int diff = 0;
    for (int i = 0; i < self->size && i < that->size && diff == 0; i++)
    {
        diff = self->data[i] - that->data[i];
    }

    if (diff > 0)
    {
        return GT;
    }
    else if (diff < 0)
    {
        return LT;
    }
    else // diff == 0
    {
        if (self->size > that->size)
        {
            return GT;
        }
        else if (self->size < that->size)
        {
            return LT;
        }
        else // self->size == that->size
        {
            return EQ;
        }
    }
}

int String_Find(const String* self, const String* pattern, int start, int stop)
{
    const char* this_str = self->data + start;
    const char* patt_str = pattern->data;
    int n = stop - start;
    int m = String_Size(pattern);

    int pos = kmp(this_str, patt_str, n, m);

    return pos == -1 ? -1 : pos + start;
}

double String_ToDecimal(const String* self)
{
    // check infinity or nan
    String* inf_nan = String_Create();
    static const char* pos_infs[12] = {"inf", "INF", "Inf", "+inf", "+INF", "+Inf", "infinity", "INFINITY", "Infinity", "+infinity", "+INFINITY", "+Infinity"};
    static const char* neg_infs[6] = {"-inf", "-INF", "-Inf", "-infinity", "-INFINITY", "-Infinity"};
    static const char* nans[9] = {"nan", "NaN", "NAN", "+nan", "+NaN", "+NAN", "-nan", "-NaN", "-NAN"};
    for (int i = 0; i < 12; ++i)
    {
        String_Set(inf_nan, pos_infs[i]);
        if (String_Equal(self, inf_nan))
        {
            String_Destroy(inf_nan);
            return INFINITY;
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        String_Set(inf_nan, neg_infs[i]);
        if (String_Equal(self, inf_nan))
        {
            String_Destroy(inf_nan);
            return -INFINITY;
        }
    }
    for (int i = 0; i < 9; ++i)
    {
        String_Set(inf_nan, nans[i]);
        if (String_Equal(self, inf_nan))
        {
            String_Destroy(inf_nan);
            return NAN;
        }
    }
    String_Destroy(inf_nan);

    // not infinity or nan

    double sign = 1; // default '+'
    double decimal_part = 0;
    int decimal_cnt = 0;
    double exp_sign = 1; // default '+'
    int exp_part = 0;

    // FSM
    enum state st = S_BEGIN_BLANK;
    for (int i = 0; i < self->size; ++i)
    {
        enum event ev = get_event(self->data[i], 10);
        switch (st | ev)
        {
            case S_BEGIN_BLANK | E_BLANK:
                st = S_BEGIN_BLANK;
                break;

            case S_BEGIN_BLANK | E_SIGN:
                sign = (self->data[i] == '+') ? 1 : -1;
                st = S_SIGN;
                break;

            case S_BEGIN_BLANK | E_DEC_POINT:
            case S_SIGN | E_DEC_POINT:
                st = S_DEC_POINT_NOT_LEFT;
                break;

            case S_BEGIN_BLANK | E_NUMBER:
            case S_SIGN | E_NUMBER:
            case S_INT_PART | E_NUMBER:
                decimal_part = decimal_part * 10 + char_to_integer(self->data[i], 10);
                st = S_INT_PART;
                break;

            case S_INT_PART | E_DEC_POINT:
                st = S_DEC_POINT_HAS_LEFT;
                break;

            case S_DEC_POINT_NOT_LEFT | E_NUMBER:
            case S_DEC_PART | E_NUMBER:
            case S_DEC_POINT_HAS_LEFT | E_NUMBER:
                decimal_part = decimal_part * 10 + char_to_integer(self->data[i], 10);
                decimal_cnt++;
                st = S_DEC_PART;
                break;

            case S_INT_PART | E_EXP:
            case S_DEC_POINT_HAS_LEFT | E_EXP:
            case S_DEC_PART | E_EXP:
                st = S_EXP;
                break;

            case S_EXP | E_SIGN:
                exp_sign = (self->data[i] == '+') ? 1 : -1;
                st = S_EXP_SIGN;
                break;

            case S_EXP | E_NUMBER:
            case S_EXP_SIGN | E_NUMBER:
            case S_EXP_PART | E_NUMBER:
                exp_part = exp_part * 10 + char_to_integer(self->data[i], 10);
                st = S_EXP_PART;
                break;

            case S_INT_PART | E_BLANK:
            case S_DEC_POINT_HAS_LEFT | E_BLANK:
            case S_DEC_PART | E_BLANK:
            case S_EXP_PART | E_BLANK:
            case S_END_BLANK | E_BLANK:
                st = S_END_BLANK;
                break;

            default:
                st = S_OTHER;
                i = self->size; // exit for loop
                break;
        }
    }
    if (st != S_INT_PART && st != S_DEC_POINT_HAS_LEFT && st != S_DEC_PART && st != S_EXP_PART && st != S_END_BLANK)
    {
        fprintf(stderr, "ERROR: Invalid literal for String_ToDecimal(): '%s'\n", self->data);
        exit(EXIT_FAILURE);
    }

    return sign * ((decimal_part / pow(10, decimal_cnt)) * pow(10, exp_sign * exp_part));
}

long long String_ToInteger(const String* self, int base)
{
    // check base
    if (base < 2 || base > 36)
    {
        fprintf(stderr, "ERROR: Invalid base for String_ToInteger(): %d\n", base);
        exit(EXIT_FAILURE);
    }

    long long sign = 1; // default '+'
    long long integer_part = 0;

    // FSM
    enum state st = S_BEGIN_BLANK;
    for (int i = 0; i < self->size; ++i)
    {
        enum event ev = get_event(self->data[i], base);
        switch (st | ev)
        {
            case S_BEGIN_BLANK | E_BLANK:
                st = S_BEGIN_BLANK;
                break;

            case S_BEGIN_BLANK | E_SIGN:
                sign = (self->data[i] == '+') ? 1 : -1;
                st = S_SIGN;
                break;

            case S_BEGIN_BLANK | E_NUMBER:
            case S_SIGN | E_NUMBER:
            case S_INT_PART | E_NUMBER:
                integer_part = integer_part * base + char_to_integer(self->data[i], base);
                st = S_INT_PART;
                break;

            case S_INT_PART | E_BLANK:
            case S_END_BLANK | E_BLANK:
                st = S_END_BLANK;
                break;

            default:
                st = S_OTHER;
                i = self->size; // exit for loop
                break;
        }
    }
    if (st != S_INT_PART && st != S_END_BLANK)
    {
        fprintf(stderr, "ERROR: Invalid literal for String_ToInteger() with base %d: '%s'\n", base, self->data);
        exit(EXIT_FAILURE);
    }

    return sign * integer_part;
}

int String_Count(const String* self, char x)
{
    int cnt = 0;
    for (int i = 0; i < self->size; i++)
    {
        if (self->data[i] == x)
        {
            cnt++;
        }
    }
    return cnt;
}

/**
 * Manipulation (will change the object itself)
 */

void String_Lower(String* self)
{
    for (int i = 0; i < self->size; ++i)
    {
        self->data[i] = (self->data[i] >= 'A' && self->data[i] <= 'Z' ? self->data[i] + ('a' - 'A') : self->data[i]);
    }
}

void String_Upper(String* self)
{
    for (int i = 0; i < self->size; ++i)
    {
        self->data[i] = (self->data[i] >= 'a' && self->data[i] <= 'z' ? self->data[i] - ('a' - 'A') : self->data[i]);
    }
}

void String_Append(String* self, const String* str)
{
    int len = str->size; // save str->size, for valid when self == str
    for (int i = 0; i < len; i++)
    {
        append_char(self, str->data[i]);
    }
}

void String_Erase(String* self, int begin, int end)
{
    check_bounds(begin, 0, self->size);
    check_bounds(end, 0, self->size + 1);

    for (int i = end; i < self->size; i++)
    {
        self->data[i - (end - begin)] = self->data[i];
    }
    self->size -= (end - begin);
    self->data[self->size] = '\0';
}

void String_Reverse(String* self)
{
    for (int i = 0, j = self->size - 1; i < j; ++i, --j)
    {
        char tmp = self->data[i];
        self->data[i] = self->data[j];
        self->data[j] = tmp;
    }
}

void String_Replace(String* self, const String* old_str, const String* new_str)
{
    String* buffer = String_Create();

    int this_start = 0;
    for (int patt_start = 0; (patt_start = String_Find(self, old_str, this_start, self->size)) != -1; this_start = patt_start + old_str->size)
    {
        String* tmp = String_Slice(self, this_start, patt_start, 1);
        String_Append(buffer, tmp);
        String_Append(buffer, new_str);
        String_Destroy(tmp);
    }
    if (this_start != self->size)
    {
        String* tmp = String_Slice(self, this_start, self->size, 1);
        String_Append(buffer, tmp);
        String_Destroy(tmp);
    }

    String_MoveAssign(self, buffer);
    String_Destroy(buffer);
}

void String_Strip(String* self)
{
    int i = 0;
    while (i < self->size && self->data[i] <= 0x20)
    {
        ++i;
    }
    String_Erase(self, 0, i);
    i = self->size - 1;
    while (i >= 0 && self->data[i] <= 0x20)
    {
        --i;
    }
    String_Erase(self, i + 1, self->size);
}

void String_Swap(String* self, String* that)
{
    int tmp_size = self->size;
    self->size = that->size;
    that->size = tmp_size;

    int tmp_capa = self->capacity;
    self->capacity = that->capacity;
    that->capacity = tmp_capa;

    char* tmp_data = self->data;
    self->data = that->data;
    that->data = tmp_data;
}

void String_Clear(String* self)
{
    String_Set(self, "");
}

/**
 * Production (will produce new object)
 */

String** String_Split(const String* self, const String* sep)
{
    if (sep->size == 0)
    {
        fprintf(stderr, "ERROR: Empty separator.\n");
        exit(EXIT_FAILURE);
    }

    String** str_arr = (String**)malloc(sizeof(String*) * (self->size + 1));
    check_pointer(str_arr);
    int size = 0;

    int this_start = 0;
    for (int patt_start = 0; (patt_start = String_Find(self, sep, this_start, self->size)) != -1; this_start = patt_start + sep->size)
    {
        str_arr[size++] = String_Slice(self, this_start, patt_start, 1);
    }
    if (this_start != self->size)
    {
        str_arr[size++] = String_Slice(self, this_start, self->size, 1);
    }
    str_arr[size] = NULL;

    // shrink to fit
    str_arr = (String**)realloc(str_arr, sizeof(String*) * (size + 1)); // size + 1 <= self->size + 1, safe

    return str_arr;
}

String* String_Slice(const String* self, int start, int stop, int step)
{
    // check
    if (step == 0)
    {
        fprintf(stderr, "ERROR: Slice step cannot be zero.\n");
        exit(EXIT_FAILURE);
    }

    check_bounds(start, -self->size, self->size);
    check_bounds(stop, -self->size - 1, self->size + 1);

    // convert
    start = start < 0 ? start + self->size : start;
    stop = stop < 0 ? stop + self->size : stop;

    // copy
    String* str = String_Create();
    for (int i = start; (step > 0) ? (i < stop) : (i > stop); i += step)
    {
        append_char(str, self->data[i]);
    }

    return str;
}

/**
 * Auxiliary (helper functions)
 */

void String_DestroyArray(String** str_arr)
{
    if (str_arr)
    {
        for (int i = 0; str_arr[i] != NULL; ++i)
        {
            String_Destroy(str_arr[i]);
        }
        free(str_arr);
    }
}
