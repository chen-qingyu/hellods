#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

using Catch::Matchers::Message;

// Only overloaded == to test compatibility.
struct EqType
{
    bool operator==(const EqType& that) const = default;
    bool operator<(const EqType& that) const = delete;
    bool operator>(const EqType& that) const = delete;
};

// Only overloaded == and < to test compatibility.
struct EqLtType
{
    bool operator==(const EqLtType& that) const = default;
    bool operator<(const EqLtType& that) const
    {
        return true;
    }
    bool operator>(const EqLtType& that) const = delete;
};

template <>
struct std::hash<EqType> // explicit specialization
{
    std::size_t operator()(const EqType&) const
    {
        static std::size_t id = 0;
        return id++;
    }
};
