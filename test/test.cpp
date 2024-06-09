#include <iostream>
#include <vector>
#include <algorithm>
int main(int argc, char const *argv[])
{
    std::vector<int> v{1, 2, 3, 4, 5};
    std::sort(v.begin(), v.end(), [](int lhs, int rhs)
              { return lhs > rhs; });
    std::for_each(v.begin(), v.end(), [](int i)
                  { std::cout << i << ' '; });
    return 0;
}
