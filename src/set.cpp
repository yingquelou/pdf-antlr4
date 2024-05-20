#include <tuple>

template <typename T, typename... Ts>
struct contains : std::false_type {};

template <typename T, typename... Ts>
struct contains<T, T, Ts...> : std::true_type {};

template <typename T, typename U, typename... Ts>
struct contains<T, U, Ts...> : contains<T, Ts...> {};

template <typename... Ts>
struct intersectionSet;

template <
    template <typename...> typename Tv1,
    template <typename...> typename Tv2,
    typename... Ts1,
    typename... Ts2>
struct intersectionSet<Tv1<Ts1...>, Tv2<Ts2...>>
{
    using type = typename intersectionSetImpl<Ts1..., Ts2...>::type;
};

template <typename... Ts>
struct intersectionSetImpl;

template <>
struct intersectionSetImpl<>
{
    using type = std::tuple<>;
};

template <typename T, typename... Ts>
struct intersectionSetImpl<T, Ts...>
{
private:
    using RestIntersection = typename intersectionSetImpl<Ts...>::type;

public:
    using type = std::conditional_t<contains<T, Ts...>::value,
                                     std::tuple<T, RestIntersection>,
                                     RestIntersection>;
};

// Ê¹ÓÃÊ¾Àý
using Result = intersectionSet<std::tuple<int, double, char>, std::tuple<double, float>>::type;
