#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <iostream>
#include <cstdint>

using IpType = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;

namespace otus
{
    std::vector<std::string> split(const std::string &str, char d);
    IpType split_to_ip(const std::string &ipStr);

    template <typename Iterator>
    void sort(Iterator first, Iterator last)
    {
        std::sort(first, last);
    }

    template <typename Iterator>
    auto filter(Iterator first, Iterator last, int filter)
    {
        std::vector<IpType> filtered;
        std::copy_if(first, last, std::back_inserter(filtered),
                     [filter](const IpType &ip)
                     { return std::get<0>(ip) == filter; });
        return filtered;
    }

    template <typename Iterator>
    auto filter(Iterator first, Iterator last, int filter0, int filter1)
    {
        std::vector<IpType> filtered;
        std::copy_if(first, last, std::back_inserter(filtered),
                     [filter0, filter1](const IpType &ip)
                     { return std::get<0>(ip) == filter0 && std::get<1>(ip) == filter1; });
        return filtered;
    }

    template <typename Iterator>
    auto filter_any(Iterator first, Iterator last, int filter)
    {
        std::vector<IpType> filtered;
        std::copy_if(first, last, std::back_inserter(filtered),
                     [filter](const IpType &ip)
                     { return std::get<0>(ip) == filter || std::get<1>(ip) == filter ||
                              std::get<2>(ip) == filter || std::get<3>(ip) == filter; });
        return filtered;
    }

    template <typename Iterator>
    void printIp(Iterator first, Iterator last)
    {
        for (auto ip = first; ip != last; ++ip)
        {
            std::cout << static_cast<int>(std::get<0>(*ip)) << "." << static_cast<int>(std::get<1>(*ip)) << "." << static_cast<int>(std::get<2>(*ip)) << "." << static_cast<int>(std::get<3>(*ip)) << "\n";
        }
    }
}