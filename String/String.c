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

#include <math.h>   // pow
#include <stdio.h>  // fprintf
#include <stdlib.h> // malloc realloc free exit

/*******************************
 * Type definition.
 *******************************/

// String structure definition.
struct string
{
    // Number of chars.
    int count;

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
 * Helper function declaration.
 *******************************/

// Check whether the index is valid (begin <= pos < end).
static inline void check_bounds(int pos, int begin, int end);

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void* pointer);

// Use the KMP algorithm to find the position of the pattern.
static inline int find_pattern(const char* str, const char* pattern, int n, int m);

// Calculate the length of null-terminated byte string (exclude '\0').
static inline int length(const char* chars);

// Copy a string range.
static inline void copy_range(String* dst, const String* src, int begin, int end);

// Check if the string represents infinity or nan. Return [+-]INFINITY or NAN if the string represents infinity or nan, zero otherwise.
static inline double check_infinity_nan(const String* str);

// Try to transform a character to an integer based on 2-36 base.
static inline int char_to_integer(char digit, int base);

// Try to transform a character to an event.
static inline enum event get_event(char ch, int base);

/*******************************
 * Interface functions definition.
 *******************************/

String* String_Create(void)
{
    String* str = (String*)malloc(sizeof(String));
    check_pointer(str);
    str->count = 0;
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
    str->count = length(chars);
    str->capacity = str->count + 1; // '\0'
    str->data = (char*)malloc(sizeof(char) * str->capacity);
    check_pointer(str->data);
    for (int i = 0; i < str->count; ++i)
    {
        str->data[i] = chars[i];
    }
    str->data[str->count] = '\0';

    return str;
}

String* String_Copy(const String* str)
{
    String* copy = (String*)malloc(sizeof(String));
    check_pointer(copy);
    copy->count = str->count;
    copy->capacity = str->capacity;
    copy->data = (char*)malloc(sizeof(char) * copy->capacity);
    check_pointer(copy->data);
    for (int i = 0; i < copy->count; i++)
    {
        copy->data[i] = str->data[i];
    }
    copy->data[copy->count] = '\0';

    return copy;
}

String* String_Move(String* str)
{
    String* move = (String*)malloc(sizeof(String));
    check_pointer(move);
    move->count = str->count;
    move->capacity = str->capacity;
    move->data = str->data;

    str->count = 0;
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

void String_CopyAssign(String* self, const String* that)
{
    free(self->data);

    self->count = that->count;
    self->capacity = that->capacity;
    self->data = (char*)malloc(sizeof(char) * self->capacity);
    check_pointer(self->data);
    for (int i = 0; i < self->count; i++)
    {
        self->data[i] = that->data[i];
    }
    self->data[self->count] = '\0';
}

void String_MoveAssign(String* self, String* that)
{
    free(self->data);

    self->count = that->count;
    self->capacity = that->capacity;
    self->data = that->data;

    that->count = 0;
    that->capacity = INIT_CAPACITY;
    that->data = (char*)malloc(sizeof(char) * that->capacity);
    check_pointer(that->data);
    that->data[0] = '\0';
}

char* String_Get(const String* self)
{
    char* chars = (char*)malloc(sizeof(self->count) + 1);
    check_pointer(chars);
    for (int i = 0; i < self->count; ++i)
    {
        chars[i] = self->data[i];
    }
    chars[self->count] = '\0';
    return chars;
}

void String_Set(String* self, const char* chars)
{
    free(self->data);

    self->count = length(chars);
    self->capacity = self->count + 1; // '\0'
    self->data = (char*)malloc(sizeof(char) * self->capacity);
    check_pointer(self->data);
    for (int i = 0; i < self->count; ++i)
    {
        self->data[i] = chars[i];
    }
    self->data[self->count] = '\0';
}

const char* String_Buffer(const String* self)
{
    return self->data;
}

void String_Print(const String* self)
{
    printf("%s\n", self->data);
}

int String_Size(const String* self)
{
    return self->count;
}

bool String_IsEmpty(const String* self)
{
    return self->count == 0;
}

char String_At(const String* self, int i)
{
    check_bounds(i, -self->count, self->count);

    return i >= 0 ? self->data[i] : self->data[i + self->count];
}

bool String_Equal(const String* self, const String* that)
{
    if (self->count != that->count)
    {
        return false;
    }

    for (int i = 0; i < self->count; ++i)
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
    for (int i = 0; i < self->count && i < that->count && diff == 0; i++)
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
        if (self->count > that->count)
        {
            return GT;
        }
        else if (self->count < that->count)
        {
            return LT;
        }
        else // self->count == that->count
        {
            return EQ;
        }
    }
}

int String_Find(const String* self, const String* pattern)
{
    const char* _str = self->data;
    const char* _pattern = pattern->data;
    int n = String_Size(self);
    int m = String_Size(pattern);

    return find_pattern(_str, _pattern, n, m);
}

String** String_Split(const String* self, const String* sep)
{
    if (sep->count == 0)
    {
        fprintf(stderr, "ERROR: Empty separator.\n");
        exit(EXIT_FAILURE);
    }

    String** str_arr = (String**)malloc(sizeof(String*) * (self->count + 1));
    check_pointer(str_arr);
    int count = 0;

    int pos_begin = 0;
    int pos_sep = 0;
    while ((pos_sep = find_pattern(self->data + pos_begin, sep->data, self->count - pos_begin, sep->count)) != STRING_NOT_FOUND)
    {
        String* tmp = String_Create();
        copy_range(tmp, self, pos_begin, pos_begin + pos_sep);
        str_arr[count++] = tmp;
        pos_begin += pos_sep + sep->count;
    }
    if (pos_begin != self->count)
    {
        String* tmp = String_Create();
        copy_range(tmp, self, pos_begin, self->count);
        str_arr[count++] = tmp;
    }
    str_arr[count] = NULL;

    // shrink to fit
    str_arr = (String**)realloc(str_arr, sizeof(String*) * (count + 1)); // count + 1 <= self->count + 1, safe

    return str_arr;
}

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

double String_ToDecimal(const String* self)
{
    // check infinity or nan
    double inf_nan = check_infinity_nan(self);
    if (inf_nan != 0)
    {
        return inf_nan;
    }

    double sign = 1; // default '+'
    double decimal_part = 0;
    int decimal_cnt = 0;
    double exp_sign = 1; // default '+'
    int exp_part = 0;

    // FSM
    enum state st = S_BEGIN_BLANK;
    for (int i = 0; i < self->count; ++i)
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
                i = self->count; // exit for loop
                break;
        }
    }
    if (st != S_INT_PART && st != S_DEC_POINT_HAS_LEFT && st != S_DEC_PART && st != S_EXP_PART && st != S_END_BLANK)
    {
        fprintf(stderr, "ERROR: Invalid literal for str_to_decimal(): '%s'\n", self->data);
        exit(EXIT_FAILURE);
    }

    return sign * ((decimal_part / pow(10, decimal_cnt)) * pow(10, exp_sign * exp_part));
}

long long String_ToInteger(const String* self, int base)
{
    // check base
    if (base < 2 || base > 36)
    {
        fprintf(stderr, "ERROR: Invalid base for str_to_integer(): %d\n", base);
        exit(EXIT_FAILURE);
    }

    long long sign = 1; // default '+'
    long long integer_part = 0;

    // FSM
    enum state st = S_BEGIN_BLANK;
    for (int i = 0; i < self->count; ++i)
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
                i = self->count; // exit for loop
                break;
        }
    }
    if (st != S_INT_PART && st != S_END_BLANK)
    {
        fprintf(stderr, "ERROR: Invalid literal for str_to_integer() with base %d: '%s'\n", base, self->data);
        exit(EXIT_FAILURE);
    }

    return sign * integer_part;
}

int String_Count(const String* self, char x)
{
    int cnt = 0;
    for (int i = 0; i < self->count; i++)
    {
        if (self->data[i] == x)
        {
            cnt++;
        }
    }
    return cnt;
}

void String_Lower(String* self)
{
    for (int i = 0; i < self->count; ++i)
    {
        self->data[i] = (self->data[i] >= 'A' && self->data[i] <= 'Z' ? self->data[i] + ('a' - 'A') : self->data[i]);
    }
}

void String_Upper(String* self)
{
    for (int i = 0; i < self->count; ++i)
    {
        self->data[i] = (self->data[i] >= 'a' && self->data[i] <= 'z' ? self->data[i] - ('a' - 'A') : self->data[i]);
    }
}

void String_Append(String* self, const String* str)
{
    if (self->count + str->count >= self->capacity) // need to expand capacity
    {
        while (self->count + str->count >= self->capacity)
        {
            self->capacity *= 2;
        }
        char* tmp = (char*)malloc(sizeof(char) * self->capacity);
        check_pointer(tmp);
        for (int i = 0; i < self->count; i++)
        {
            tmp[i] = self->data[i];
        }
        free(self->data);
        self->data = tmp;
    }

    for (int i = 0; i < str->count; i++)
    {
        self->data[self->count + i] = str->data[i];
    }
    self->count += str->count;
    self->data[self->count] = '\0';
}

void String_Erase(String* self, int begin, int end)
{
    begin = (begin < 0 ? 0 : begin);
    end = (end > self->count ? self->count : end);

    for (int i = end; i < self->count; i++)
    {
        self->data[i - (end - begin)] = self->data[i];
    }
    self->count -= (end - begin);
    self->data[self->count] = '\0';
}

void String_Reverse(String* self)
{
    for (int i = 0, j = self->count - 1; i < j; ++i, --j)
    {
        char tmp = self->data[i];
        self->data[i] = self->data[j];
        self->data[j] = tmp;
    }
}

void String_ReplaceChar(String* self, const char old_char, const char new_char)
{
    for (int i = 0; i < self->count; ++i)
    {
        if (self->data[i] == old_char)
        {
            self->data[i] = new_char;
        }
    }
}

void String_Replace(String* self, const String* old_str, const String* new_str)
{
    String* buffer = String_Create();
    String* tmp = String_Create();

    int offset = 0;
    int index = 0;
    while ((index = find_pattern(self->data + offset, old_str->data, self->count - offset, old_str->count)) != STRING_NOT_FOUND)
    {
        index += offset;
        copy_range(tmp, self, offset, index);
        String_Append(buffer, tmp);
        String_Append(buffer, new_str);
        offset = index + old_str->count;
    }
    if (offset != self->count)
    {
        copy_range(tmp, self, offset, self->count);
        String_Append(buffer, tmp);
    }
    String_Destroy(tmp);

    free(self->data);
    self->data = buffer->data;
    self->count = buffer->count;
    self->capacity = buffer->capacity;
    free(buffer);
}

void String_Strip(String* self)
{
    int i = 0;
    while (i < self->count && self->data[i] <= 0x20)
    {
        ++i;
    }
    String_Erase(self, 0, i);
    i = self->count - 1;
    while (i >= 0 && self->data[i] <= 0x20)
    {
        --i;
    }
    String_Erase(self, i + 1, self->count);
}

void String_Swap(String* self, String* that)
{
    int tmp_size = self->count;
    self->count = that->count;
    that->count = tmp_size;

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

/*******************************
 * Helper function definition.
 *******************************/

static inline void check_bounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        fprintf(stderr, "ERROR: Out of range: %d not in [%d, %d)\n", pos, begin, end);
        exit(EXIT_FAILURE);
    }
}

static inline void check_pointer(const void* pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

static inline int find_pattern(const char* str, const char* pattern, int n, int m)
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
        if (pattern[i + 1] == pattern[j])
        {
            match[j] = i + 1;
        }
        else
        {
            match[j] = STRING_NOT_FOUND;
        }
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

static inline void copy_range(String* dst, const String* src, int begin, int end)
{
    check_bounds(begin, 0, src->count);
    check_bounds(end, 0, src->count + 1);

    free(dst->data);

    dst->count = end - begin;
    dst->capacity = dst->count + 1; // '\0'
    dst->data = (char*)malloc(sizeof(char) * dst->capacity);
    check_pointer(dst->data);
    for (int i = 0; i < dst->count; i++)
    {
        dst->data[i] = src->data[begin + i];
    }
    dst->data[dst->count] = '\0';
}

static inline double check_infinity_nan(const String* str)
{
    String* inf_nan = String_Create();
    static const char* pos_infs[12] = {"inf", "INF", "Inf", "+inf", "+INF", "+Inf", "infinity", "INFINITY", "Infinity", "+infinity", "+INFINITY", "+Infinity"};
    static const char* neg_infs[6] = {"-inf", "-INF", "-Inf", "-infinity", "-INFINITY", "-Infinity"};
    static const char* nans[9] = {"nan", "NaN", "NAN", "+nan", "+NaN", "+NAN", "-nan", "-NaN", "-NAN"};
    for (int i = 0; i < 12; ++i)
    {
        String_Set(inf_nan, pos_infs[i]);
        if (String_Equal(str, inf_nan))
        {
            String_Destroy(inf_nan);
            return INFINITY;
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        String_Set(inf_nan, neg_infs[i]);
        if (String_Equal(str, inf_nan))
        {
            String_Destroy(inf_nan);
            return -INFINITY;
        }
    }
    for (int i = 0; i < 9; ++i)
    {
        String_Set(inf_nan, nans[i]);
        if (String_Equal(str, inf_nan))
        {
            String_Destroy(inf_nan);
            return NAN;
        }
    }
    String_Destroy(inf_nan);
    return 0; // not infinity or nan
}

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
