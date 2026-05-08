/**
 * @file metro_planner.cpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief 成都地铁换乘导航，图的应用（Dijkstra 最短路径）
 * @date 2026.05.08
 */

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

#include <iostream>
#include <string>

#include "../sources/Graph/MatrixGraph.hpp"
#include "../sources/List/ArrayList.hpp"

using hellods::ArrayList;
using hellods::MatrixGraph;

struct Line
{
    const std::string name;
    const ArrayList<std::string> stations;
};

const Line LINES[] = {
    {"1号线", {"韦家碾", "火车北站", "骡马市", "天府广场", "省体育馆", "火车南站", "世纪城", "四河", "科学城"}},
    {"2号线", {"犀浦", "一品天下", "中医大省医院", "天府广场", "春熙路", "成都东客站", "龙泉驿"}},
    {"3号线", {"成都医学院", "驷马桥", "春熙路", "省体育馆", "高升桥", "太平园", "双流西站"}},
    {"5号线", {"北站西二路", "中医大省医院", "高升桥", "神仙树"}},
    {"7号线", {"火车北站", "北站西二路", "一品天下", "太平园", "神仙树", "火车南站", "成都东客站", "驷马桥"}},
    {"10号线", {"骡马市", "人民公园", "高升桥", "太平园", "双流机场T2", "双流西站", "新平"}},
};

std::string line_of(const std::string& from, const std::string& to)
{
    for (const auto& line : LINES)
    {
        for (int i = 1; i < line.stations.size(); ++i)
        {
            if ((from == line.stations[i - 1] && to == line.stations[i]) || (from == line.stations[i] && to == line.stations[i - 1]))
            {
                return line.name;
            }
        }
    }
    throw std::runtime_error("站点 " + from + " 和 " + to + " 不连通");
}

void metro_planner()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "\n========== 地铁换乘导航 ==========\n";

    // 使用无向图表示地铁线路，顶点是站点，边是相邻站点之间的连接，权重为 1（表示一站）
    MatrixGraph<std::string, int, false> metro;
    for (const auto& line : LINES)
    {
        for (int i = 1; i < line.stations.size(); ++i)
        {
            metro.add_vertex(line.stations[i - 1]);
            metro.add_vertex(line.stations[i]);
            metro.link(line.stations[i - 1], line.stations[i], 1);
        }
    }

    std::cout << "\n=== 站点（" << metro.size() << " 个）===\n";
    for (const auto& line : LINES)
    {
        std::cout << "  " << line.name << ":";
        for (int i = 0; i < line.stations.size(); ++i)
        {
            std::cout << ' ' << line.stations[i];
        }
        std::cout << "\n";
    }

    std::cout << "\n起点站: ";
    std::string from;
    std::getline(std::cin, from);

    std::cout << "终点站: ";
    std::string to;
    std::getline(std::cin, to);

    try
    {
        auto sp = metro.dijkstra(from); // 计算从起点站到所有站点的最短路径
        (void)metro.distance(from, to); // 检查终点站是否存在，否则抛出异常

        ArrayList<std::string> route;
        for (std::string cur = to;; cur = sp.prev(cur).value())
        {
            route.insert(0, cur);
            if (cur == from)
            {
                break;
            }
        }

        std::cout << "\n路线：\n";
        if (route.size() == 1)
        {
            std::cout << "  无需乘车: " << route[0] << "\n";
            return;
        }

        int start = 0;
        std::string line = line_of(route[0], route[1]);
        for (int i = 1; i < route.size(); ++i)
        {
            std::string next = i + 1 < route.size() ? line_of(route[i], route[i + 1]) : line;
            if (i + 1 == route.size() || line != next)
            {
                std::cout << "  " << line << ": ";
                for (int j = start; j <= i; ++j)
                {
                    if (j > start)
                    {
                        std::cout << " -> ";
                    }
                    std::cout << route[j];
                }
                std::cout << "\n";
                start = i;
                line = next;
            }
        }
        std::cout << "站点数: " << route.size() << " 站\n";
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << "\n";
    }
}
