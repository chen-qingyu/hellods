/**
 * @file main.cpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief 容器类应用例子 TUI 主菜单
 * @date 2025.10.12
 */

#include <iostream>
#include <limits>
#include <string>

void simulate_bank_queuing(int win_num, int serv_time);
double calculator(const std::string& expr);

// 从标准输入读取一个整数，支持验证。失败时返回默认值。
static int read_int(const std::string& prompt, bool require_positive = false)
{
    while (true)
    {
        std::cout << prompt;
        int value;
        if (std::cin >> value)
        {
            if (require_positive && value <= 0)
            {
                std::cout << "Please enter a positive number.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        // 非数字输入：清除错误状态并跳过无效输入
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number.\n";
    }
}

static void run_calculator()
{
    std::cout << "\n========== Calculator ==========\n";
    std::cout << "Enter an expression (or empty to go back): ";

    std::string expr;
    std::getline(std::cin, expr);

    if (expr.empty())
    {
        return;
    }

    try
    {
        double result = calculator(expr);
        std::cout << "Result: " << result << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
}

static void run_bank_queuing()
{
    std::cout << "\n========== Bank Queuing ==========\n";

    int win_num = read_int("Number of windows: ", true);
    int serv_time = read_int("Service time (time units): ", true);

    std::cout << "\n";
    simulate_bank_queuing(win_num, serv_time);
}

int main()
{
    std::cout << "=== HelloDS Examples ===\n";

    while (true)
    {
        std::cout << "\n1. Calculator (infix expression evaluation)\n";
        std::cout << "2. Bank Queuing (multi-window simulation)\n";
        std::cout << "0. Exit\n";

        int choice = read_int("Choose: ");

        switch (choice)
        {
            case 1:
                run_calculator();
                break;

            case 2:
                run_bank_queuing();
                break;

            case 0:
                std::cout << "Bye!\n";
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
