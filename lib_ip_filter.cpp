#include "lib_ip_filter.h"

#include <stdexcept>
namespace otus
{
    std::vector<std::string> split(const std::string &str, char d)
    {
        std::vector<std::string> r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while (stop != std::string::npos)
        {
            r.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }

        r.push_back(str.substr(start));

        return r;
    }

    IpType split_to_ip(const std::string &ipStr)
    {
        std::vector<std::string> ipSplit = split(ipStr, '.');
        if (ipSplit.size() != 4)
        {
            throw std::runtime_error("Wrong format ip " + ipStr);
        }
        auto convertToInt = [](const std::string &numStr)
        {
            return numStr.empty() ? 0 : std::stoi(numStr);
        };

        int value[4] = {convertToInt(ipSplit[0]), convertToInt(ipSplit[1]), convertToInt(ipSplit[2]), convertToInt(ipSplit[3])};

        auto checkIp = [](int ipNumber)
        {
            return ipNumber >= 0 && ipNumber < 256;
        };

        if (!checkIp(value[0]) ||
            !checkIp(value[1]) ||
            !checkIp(value[2]) ||
            !checkIp(value[3]))
        {
            throw std::runtime_error("Wrong format ip, too big numbers " + ipStr);
        }

        return {
            static_cast<uint8_t>(value[0]),
            static_cast<uint8_t>(value[1]),
            static_cast<uint8_t>(value[2]),
            static_cast<uint8_t>(value[3])};
    }
}