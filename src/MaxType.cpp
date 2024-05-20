#include <iostream>
template <typename... T>
struct MaxType
{
};
template <typename T>
struct MaxType<T>
{
public:
    using type = std::remove_cv_t<T>;
};
template <typename T1, typename T2>
struct MaxType<T1, T2>
{
    typedef std::remove_cv_t<T1> T1Ref;
    typedef std::remove_cv_t<T2> T2Ref;
public:
    using type = std::conditional_t<(sizeof(T1Ref) > sizeof(T2Ref)), T1Ref, T2Ref>;
};
template <typename T, typename... Rest>
struct MaxType<T, Rest...>
{
public:
    using type = typename MaxType<T, typename MaxType<Rest...>::type>::type;
};
int main(int argc, char const *argv[])
{
    auto f = []()
    {
        static auto &os = std::cout;

        MaxType<unsigned int, int, void *>::type s;
        os << s;
    };
    f();
    return 0;
}