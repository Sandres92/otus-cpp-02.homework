#define BOOST_TEST_MODULE test_ip_filter

#include "lib.h"
#include "lib_ip_filter.h"
#include "custom_tie.h"

#include <vector>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_ip_filter)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(2 > 0);
}

BOOST_AUTO_TEST_CASE(test_valid_sum)
{
    BOOST_CHECK(1 + 1 == 2);
}

BOOST_AUTO_TEST_CASE(test_split_to_tuple_1)
{
    std::string ip = "100.200.255.200";
    auto ipAddres = otus::split_to_ip(ip);

    BOOST_CHECK(std::get<0>(ipAddres) == 100 && std::get<1>(ipAddres) == 200 &&
                std::get<2>(ipAddres) == 255 && std::get<3>(ipAddres) == 200);
}

BOOST_AUTO_TEST_CASE(test_split_to_tuple_2)
{
    std::string ip = ".200.255.200";
    auto ipTuple = otus::split_to_ip(ip);

    BOOST_CHECK(std::get<0>(ipTuple) == 0 && std::get<1>(ipTuple) == 200 &&
                std::get<2>(ipTuple) == 255 && std::get<3>(ipTuple) == 200);
}

BOOST_AUTO_TEST_CASE(test_split_to_tuple_3)
{
    std::string ip = "100.200.255.";
    auto ipTuple = otus::split_to_ip(ip);

    BOOST_CHECK(std::get<0>(ipTuple) == 100 && std::get<1>(ipTuple) == 200 &&
                std::get<2>(ipTuple) == 255 && std::get<3>(ipTuple) == 0);
}

BOOST_AUTO_TEST_CASE(test_split_to_tuple_4)
{
    std::string ip = "...";
    auto ipTuple = otus::split_to_ip(ip);

    BOOST_CHECK(std::get<0>(ipTuple) == 0 && std::get<1>(ipTuple) == 0 &&
                std::get<2>(ipTuple) == 0 && std::get<3>(ipTuple) == 0);
}

BOOST_AUTO_TEST_CASE(test_split_to_tuple_5)
{
    std::string ip = "001.002.003.004";
    auto ipTuple = otus::split_to_ip(ip);

    BOOST_CHECK(std::get<0>(ipTuple) == 1 && std::get<1>(ipTuple) == 2 &&
                std::get<2>(ipTuple) == 3 && std::get<3>(ipTuple) == 4);
}

BOOST_AUTO_TEST_CASE(test_split_to_tuple_6)
{
    bool result = false;

    try
    {
        std::string ip = "100.200";
        auto ipTuple = otus::split_to_ip(ip);
        std::get<0>(ipTuple);
    }
    catch (const std::exception &e)
    {
        result = true;
    }
    catch (...)
    {
        result = false;
    }
    BOOST_CHECK(result);
}

BOOST_AUTO_TEST_CASE(test_sort_1)
{
    std::vector<otus::IpType> v{
        {100u, 0u, 0u, 0u},
        {200u, 0u, 0u, 0u},
        {255u, 0u, 0u, 0u}};

    otus::sort(v.rbegin(), v.rend());

    BOOST_CHECK(std::get<0>(v[0]) == 255 && std::get<0>(v[1]) == 200 && std::get<0>(v[2]) == 100);
}

BOOST_AUTO_TEST_CASE(test_sort_2)
{
    std::vector<otus::IpType> v{
        {200u, 100u, 0u, 0u},
        {200u, 200u, 0u, 0u},
        {200u, 0u, 0u, 0u}};

    otus::sort(v.rbegin(), v.rend());

    BOOST_CHECK(std::get<0>(v[0]) == 200 && std::get<0>(v[1]) == 200 && std::get<0>(v[2]) == 200 &&
                std::get<1>(v[0]) == 200 && std::get<1>(v[1]) == 100 && std::get<1>(v[2]) == 0);
}

BOOST_AUTO_TEST_CASE(test_filter_one_arg_1)
{
    std::vector<otus::IpType> v{
        {1u, 100u, 0u, 0u},
        {200u, 200u, 200u, 200u},
        {1u, 200u, 0u, 0u}};

    auto result = otus::filter(v.begin(), v.end(), 1);

    BOOST_CHECK(result.size() == 2 &&
                std::get<0>(result[0]) == 1 && std::get<1>(result[0]) == 100 &&
                std::get<0>(result[1]) == 1 && std::get<1>(result[1]) == 200);
}

BOOST_AUTO_TEST_CASE(test_filter_one_arg_2)
{
    std::vector<otus::IpType> v{
        {0u, 100u, 0u, 0u},
        {0u, 200u, 0u, 0u},
        {0u, 0u, 0u, 0u}};

    auto result = otus::filter(v.begin(), v.end(), 1);

    BOOST_CHECK(result.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_filter_two_arg_1)
{
    std::vector<otus::IpType> v{
        {46u, 70u, 100u, 0u},
        {0u, 200u, 0u, 0u},
        {0u, 0u, 0u, 0u}};

    auto result = otus::filter(v.begin(), v.end(), 46, 70);

    BOOST_CHECK(result.size() == 1 && std::get<0>(result[0]) == 46 && std::get<1>(result[0]) == 70 && std::get<2>(result[0]) == 100);
}

BOOST_AUTO_TEST_CASE(test_filter_two_arg_2)
{
    std::vector<otus::IpType> v{
        {45u, 71u, 100u, 0u},
        {46u, 71u, 0u, 0u},
        {0u, 0u, 0u, 0u}};

    auto result = otus::filter(v.begin(), v.end(), 46, 70);

    BOOST_CHECK(result.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_filter_any_1)
{
    std::vector<otus::IpType> v{
        {0u, 0u, 0u, 0u},
        {46u, 70u, 80u, 90u},
        {0u, 0u, 0u, 46u}};

    auto result = otus::filter_any(v.begin(), v.end(), 46);

    BOOST_CHECK(result.size() == 2 &&
                std::get<0>(result[0]) == 46 && std::get<1>(result[0]) == 70 && std::get<2>(result[0]) == 80 && std::get<3>(result[0]) == 90 &&
                std::get<0>(result[1]) == 0 && std::get<1>(result[1]) == 0 && std::get<2>(result[1]) == 0 && std::get<3>(result[1]) == 46);
}

BOOST_AUTO_TEST_CASE(test_custom_tie)
{
    auto getPerson = []()
    {
        const std::string name = "Petia";
        const std::string secondName = "Ivanoff";
        const std::size_t age = 23;
        const std::string department = "Sale";
        return std::make_tuple(name, secondName, age, department);
    };

    std::string name = "";
    std::string secondName = "";
    std::size_t age;
    std::string department = "";

    otus::custom_tie(name, secondName, age, department) = getPerson();
    std::cout << name << " " << secondName << " " << age << " " << department << "\n";

    BOOST_CHECK(name == "Petia" && secondName == "Ivanoff" && age == 23 && department == "Sale");
}

BOOST_AUTO_TEST_SUITE_END()