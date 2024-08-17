/**
 * @file examples_main.cpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief 容器类应用例子 主函数
 * @date 2023.01.12
 */

void simulate_bank_queuing(int win_num, int serv_time);

int main(void)
{
    simulate_bank_queuing(4, 50); // 模拟4个窗口，50个时间单位

    return 0;
}
