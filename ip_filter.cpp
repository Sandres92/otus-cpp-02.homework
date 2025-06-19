
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>

#include "lib.h"
#include "lib_ip_filter.h"
#include "custom_tie.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    try
    {
        std::ifstream in("ip_filter.tsv");
        if (!in.is_open())
        {
            throw std::runtime_error("Could not open ip_filter.tsv file");
        }

        std::vector<otus::IpType> ip_pool;
        for (std::string line; std::getline(in, line);)
        {
            std::vector<std::string> v = otus::split(line, '\t');
            ip_pool.push_back(otus::split_to_ip(v.at(0)));
        }

        otus::sort(ip_pool.rbegin(), ip_pool.rend());
        otus::printIp(ip_pool.cbegin(), ip_pool.cend());

        auto filter_1 = otus::filter(ip_pool.begin(), ip_pool.end(), 1);
        otus::printIp(filter_1.cbegin(), filter_1.cend());

        auto filter_46_70 = otus::filter(ip_pool.begin(), ip_pool.end(), 46, 70);
        otus::printIp(filter_46_70.cbegin(), filter_46_70.cend());

        auto filter_any_46 = otus::filter_any(ip_pool.begin(), ip_pool.end(), 46);
        otus::printIp(filter_any_46.cbegin(), filter_any_46.cend());

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231

        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
