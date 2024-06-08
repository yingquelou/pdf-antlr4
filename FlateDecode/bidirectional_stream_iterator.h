#pragma once
#include <fstream>
#include <iterator>
#include <concepts>
template <typename T>
concept bidirectional_iterator_concept = requires(T t) {
    { ++t } -> std::same_as<T>;
    { t++ } -> std::same_as<T>;
    { --t } -> std::same_as<T>;
    { t-- } -> std::same_as<T>;
    { *t } -> std::same_as<typename T::value_type>;
};

/**
 * @brief 双向流迭代器类，继承自std::istream_iterator<T>
 *
 * 该类用于在流中进行双向迭代，支持前向和后向遍历。
 *
 * @tparam T 迭代器的值类型
 */
template <typename T>
class Bidirectional_Stream_iterator
    : public std::istream_iterator<T>
{
    std::basic_istream<T> &is;

public:
    /**
     * @brief 构造一个新的 Bidirectional_Stream_iterator 对象
     *
     * @param is 输入流
     */
    Bidirectional_Stream_iterator(std::basic_istream<T> &is) : std::istream_iterator<T>(is), is(is) {}

    /**
     * @brief 后向迭代
     *
     * @return Bidirectional_Stream_iterator& 返回自身引用
     */
    Bidirectional_Stream_iterator &operator--()
    {
        is.seekg(-1, std::ios::cur);
        return *this;
    }

    /**
     * @brief 后向迭代
     *
     * @return Bidirectional_Stream_iterator 返回自身的拷贝
     */
    Bidirectional_Stream_iterator operator--(int)
    {
        Bidirectional_Stream_iterator tmp = *this;
        --(*this);
        return tmp;
    }
    T operator*() const
    {
        auto t = is.peek();
        return t;
    }
};