/**
 * @file examples_main.cpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief 容器类应用例子 主函数
 * @date 2023.01.12
 */

#include <cassert>
#include <string>

void simulate_bank_queuing(int win_num, int serv_time);
double calculator(const std::string& expr);

int main(void)
{
    // simulate_bank_queuing(4, 50); // 模拟4个窗口，50个时间单位

    calculator("1.1 * (2.2 + 3.3)"); // 6.05
    calculator("1*2*3*4*5");         // 120

    return 0;
}
