#pragma once

#include <tuple>

namespace otus
{
    template <typename T>
    std::tuple<T &> custom_tie(T &t)
    {
        return std::tuple<T &>(t);
    }

    template <typename T1, typename T2>
    std::tuple<T1 &, T2 &> custom_tie(T1 &t1, T2 &t2)
    {
        return std::tuple<T1 &, T2 &>(t1, t2);
    }

    template <typename T1, typename T2, typename T3>
    std::tuple<T1 &, T2 &, T3 &> custom_tie(T1 &t1, T2 &t2, T3 &t3)
    {
        return std::tuple<T1 &, T2 &, T3 &>(t1, t2, t3);
    }

    template <typename T1, typename T2, typename T3, typename T4>
    std::tuple<T1 &, T2 &, T3 &, T4 &> custom_tie(T1 &t1, T2 &t2, T3 &t3, T4 &t4)
    {
        return std::tuple<T1 &, T2 &, T3 &, T4 &>(t1, t2, t3, t4);
    }
}
