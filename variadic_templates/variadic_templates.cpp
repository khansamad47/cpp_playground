#include <iostream>

template<class T>
T find_max(T val)
{
    return val;
}

template <class T, class... Args>
T find_max(T first, Args... rest)
{
    auto result = find_max(rest...);
    return (first > result) ? first : result;
}

int main()
{
    std::cout << find_max(1,2,3,4,5,6,7,8) << '\n';
    return 0;
}
