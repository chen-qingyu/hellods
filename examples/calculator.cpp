/**
 * @file calculator.cpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief 中缀表达式求值，线性表和栈应用
 * @date 2024.09.22
 */

#include <iostream>
#include <regex>
#include <string>

#include "../sources/List/ArrayList.hpp"
#include "../sources/Stack/ArrayStack.hpp"

using hellods::ArrayList;
using hellods::ArrayStack;

// 检查括号是否匹配，O(N)
static bool check_parentheses(const std::string& expr)
{
    ArrayStack<char> stk;
    for (const auto& c : expr)
    {
        if (c == '(')
        {
            stk.push(c);
        }
        else if (c == ')')
        {
            if (stk.top() == '(')
            {
                stk.pop();
            }
            else // mismatch
            {
                return false;
            }
        }
    }
    return stk.is_empty();
}

// Token 定义
struct Token
{
    enum Type
    {
        NUM,
        OP
    } type;

    union Data
    {
        double num;
        char op;

        Data(double num)
            : num(num)
        {
        }

        Data(char op)
            : op(op)
        {
        }
    } data;

    Token()
        : type()
        , data(0.0)
    {
    }

    Token(Type type, const Data& data)
        : type(type)
        , data(data)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Token& token)
    {
        if (token.type == Token::NUM)
        {
            os << "NUM(" << token.data.num << ")";
        }
        else if (token.type == Token::OP)
        {
            os << "OP(" << token.data.op << ")";
        }

        return os;
    }
};

// 表达式字符串解析为 Token 序列，O(N)
static ArrayList<Token> tokenize(const std::string& expr)
{
    ArrayList<Token> tokens;

    std::string NUM = R"([-+]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][-+]?\d+)?)";
    std::string OP = R"([+\-*/()])";
    std::string WS = R"(\s+)";

    std::regex re("(" + NUM + ")|(" + OP + ")|(" + WS + ")");

    for (std::sregex_iterator it(expr.begin(), expr.end(), re), end; it != end; ++it)
    {
        if ((*it)[1].matched) // is number
        {
            double n = std::stod(it->str());
            tokens.append(Token(Token::NUM, Token::Data(n)));
        }
        else if ((*it)[2].matched) // is operator
        {
            std::string op = it->str();
            tokens.append(Token(Token::OP, Token::Data(op[0])));
        }
        else if ((*it)[3].matched) // ignore space
        {
        }
    }

    return tokens;
}

// 中缀表达式转后缀表达式，O(N)
static ArrayList<Token> to_postfix(const ArrayList<Token>& tokens)
{
    ArrayStack<Token> stk;
    ArrayList<Token> postfix;

    for (const auto& token : tokens)
    {
        switch (token.type)
        {
            case Token::NUM:
                postfix.append(token); // 数字直接加入后缀表达式
                break;

            case Token::OP:
                if (token.data.op == '(' ||
                    token.data.op == '*' ||
                    token.data.op == '/') // 若token优先级高于栈顶除左括号外的运算符（左括号可视作优先级无限大）
                {
                    stk.push(token); // 直接入栈
                }
                else if (token.data.op == ')' ||
                         token.data.op == '+' ||
                         token.data.op == '-') // 否则，token优先级小于等于栈顶运算符，则依次弹出栈顶运算符（右括号可视作优先级无限小）
                {
                    Token t;
                    while (!stk.is_empty() && (t = stk.pop()).data.op != '(') // 没匹配到对应的括号时
                    {
                        postfix.append(t); // 运算符均加入后缀表达式
                    }
                    if (token.data.op != ')') // 当前运算符入栈（括号排除）
                    {
                        stk.push(token);
                    }
                }
                break;

            default:
                break;
        }
    }

    while (!stk.is_empty()) // 栈中剩余运算符依次弹出加入后缀表达式
    {
        postfix.append(stk.pop());
    }

    return postfix;
}

// 后缀表达式求值，O(N)
static double eval_postfix(const ArrayList<Token>& tokens)
{
    ArrayStack<Token> stk;
    for (const auto& token : tokens)
    {
        if (token.type == Token::NUM)
        {
            stk.push(Token(Token::NUM, Token::Data(token.data.num)));
        }
        else if (token.type == Token::OP)
        {
            double y = stk.pop().data.num;
            double x = stk.pop().data.num;
            double z;

            switch (token.data.op)
            {
                case '+':
                    z = x + y;
                    break;

                case '-':
                    z = x - y;
                    break;

                case '*':
                    z = x * y;
                    break;

                case '/':
                    z = x / y;
                    break;

                default:
                    break;
            }

            stk.push(Token(Token::NUM, Token::Data(z)));
        }
    }

    if (stk.size() != 1)
    {
        throw std::runtime_error("Error: Invalid expression.");
    }

    return stk.pop().data.num;
}

// 表达式字符串求值，O(N)
double calculator(const std::string& expr)
{
    // 1. 检查括号
    if (!check_parentheses(expr))
    {
        throw std::runtime_error("Error: Parentheses mismatch.");
    }

    std::cout << "origin expr: " << expr << "\n";

    // 2. 分词
    auto infix_tokens = tokenize(expr);

    std::cout << "infix tokens: " << infix_tokens << "\n";

    // 3. 中缀表达式转后缀表达式
    auto postfix_tokens = to_postfix(infix_tokens);

    std::cout << "postfix tokens: " << postfix_tokens << "\n";

    // 4. 后缀表达式求值
    double result = eval_postfix(postfix_tokens);

    std::cout << "eval result: " << result << "\n";

    return result;
}
