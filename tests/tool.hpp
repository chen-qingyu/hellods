#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

using Catch::Matchers::Message;

// Only overloaded == to test compatibility.
struct EqType
{
    bool operator==(const EqType& that) const
    {
        return true;
    }
};

// Only overloaded == and < to test compatibility.
struct EqLtType
{
    bool operator==(const EqLtType& that) const
    {
        return true;
    }
    bool operator<(const EqLtType& that) const
    {
        return true;
    }
};
