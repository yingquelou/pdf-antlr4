#pragma once
namespace utils
{
#include <stddef.h>
#include <iostream>
    // 元组的定义
    template <typename... Types>
    struct Tuple
    {
    };

    // 元组的特化实现
    template <typename Head, typename... Tail>
    struct Tuple<Head, Tail...>
    {
        Head head;
        Tuple<Tail...> tail;
    };

    // 元组的构造函数
    template <typename... Args>
    Tuple<Args...> MakeTuple(Args... args)
    {
        return Tuple<Args...>{args...};
    }

    // 元组的访问函数
    template <size_t Index, typename Head, typename... Tail>
    struct TupleElement
    {
        using type = typename TupleElement<Index - 1, Tail...>::type;
    };

    template <typename Head, typename... Tail>
    struct TupleElement<0, Head, Tail...>
    {
        using type = Head;
    };

    template <size_t Index, typename... Args>
    typename std::enable_if<Index == 0, typename TupleElement<0, Args...>::type &>::type
    Get(Tuple<Args...> &tuple)
    {
        return tuple.head;
    }

    template <size_t Index, typename Head, typename... Tail>
    typename std::enable_if<Index != 0, typename TupleElement<Index, Head, Tail...>::type &>::type
    Get(Tuple<Head, Tail...> &tuple)
    {
        return Get<Index - 1>(tuple.tail);
    }
} // namespace utils
