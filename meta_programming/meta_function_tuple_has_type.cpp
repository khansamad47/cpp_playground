#include <vector>
#include <iostream>
#include <string>
#include <tuple>

template<bool, typename THEN, typename ELSE>
struct if_;

template<typename THEN, typename ELSE>
struct if_<true,THEN,ELSE> {
    using type = THEN;
};

template<typename THEN, typename ELSE>
struct if_<false,THEN,ELSE> {
    using type = ELSE;
};

template<typename TYPE, typename TUPLE, size_t INDEX = 0>
struct contains:
    if_<
        std::is_same<TYPE, std::tuple_element_t<INDEX, TUPLE>>::value,
        std::true_type, 
        if_<
            std::tuple_size_v<typename Tp> - 1 == INDEX,
            std::false_type, 
            contains<TYPE, TUPLE, INDEX +1>
        >
{}

bool contains( std::string type, const std::vector<std::string>& list, size_t index)
{
    // Check if it's a match
    if (list[index] == type)
    {
        return true;
    }
    // It did not match
    // Check if last index, nothing more to check
    if (list.size() - 1 == index)
    {
        return false;
    }
    return contains(type, list, ++index);
}

int main()
{
    std::vector<std::string> types { "double","bool","int"};
    std::cout << "Contains double = " << contains("double",types, 0) << '\n';
    std::cout << "Contains bool   = " << contains("bool",  types, 0) << '\n';
    std::cout << "Contains int    = " << contains("int",   types, 0) << '\n';
    std::cout << "Contains float  = " << contains("float", types, 0) << '\n';

    std::cout << if_<(10>5),std::true_type,std::false_type>::type::value << '\n';
    std::cout << if_<(10<5),std::true_type,std::false_type>::type::value << '\n';
}
