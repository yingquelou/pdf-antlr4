#include <iostream>
#include <type_traits>
#include <tuple>
template <typename... Ts>
struct type_cat
{
};
template <
    template <typename... Ts> typename Tv,
    typename... Ts1,
    typename... Ts2>
struct type_cat<std::tuple<Ts1...>, Tv<Ts2...>>
{
    using type = std::tuple<std::remove_cvref_t<Ts1>..., std::remove_cvref_t<Ts2>...>;
};
// 辅助结构体，用于存储类型和对应的sizeof值
template <typename T, std::size_t Size>
struct TypeSizePair
{
    using type = T;
    static constexpr std::size_t size = Size;
};

// 比较模板，用于比较TypeSizePair的大小
template <typename T1, typename T2>
struct CompareSize
{
    static constexpr bool value = (T1::size < T2::size);
};

// 快速排序算法
template <typename... Ts>
struct QuickSort
{
    using type = std::tuple<Ts...>;

    template <typename... Elements>
    struct SortImpl;

    template <typename Pivot, typename... Rest>
    struct SortImpl<Pivot, Rest...>
    {
        using smaller = typename SortImpl<typename std::conditional_t<CompareSize<TypeSizePair<Rest, sizeof(Rest)>, TypeSizePair<Pivot, sizeof(Pivot)>>::value, Rest, Pivot>...>;
        using larger = typename SortImpl<typename std::conditional_t<CompareSize<TypeSizePair<Rest, sizeof(Rest)>, TypeSizePair<Pivot, sizeof(Pivot)>>::value, Pivot, Rest>...>;
        // using type = std::tuple<typename smaller::type, Pivot, typename larger::type>;
        using type = typename type_cat<typename type_cat<typename smaller::type, std::tuple<Pivot>>::type, typename larger::type>::type;
    };

    template <>
    struct SortImpl<>
    {
        using type = std::tuple<>;
    };

    using sorted = typename SortImpl<Ts...>::type;
};

int main()
{
    using SortedTypes = QuickSort<int, char, double, long, short>::sorted;
    std::cout << typeid(SortedTypes).name() << std::endl;

    return 0;
}
