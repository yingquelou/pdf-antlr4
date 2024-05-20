#include <list>
#include "demo.h"
template <typename T>
std::list<size_t> *printer(const T &v)
{
    return new std::list<size_t>;
}
template <typename T, size_t N>
std::list<size_t> *printer(const T (&arr)[N])
{
    auto &&p = printer(arr[0]);
    p->push_front(N);
    return p;
}
template <typename T>
std::vector<size_t> print(T &&t)
{
    auto &&p = printer(std::forward<T>(t));
    std::vector<size_t> vec(p->cbegin(), p->cend());
    delete p;
    return std::move(vec);
}