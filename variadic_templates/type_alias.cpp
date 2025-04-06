#include <iostream>
#include <vector>
#include <string>
#include <tuple>

// Type Alias with templates
template<typename... T>
using TupleVector = std::vector<std::tuple<T...>>;

// Before C++11
template<typename T, typename U>
struct PairVector {
    typedef std::vector<std::pair<T,U>> type; 
};

int main () {
    TupleVector<std::string, double> myData;
    myData.emplace_back("Samad", 100.0);
    myData.emplace_back("Khan",   99.0);

    for (auto& item: myData) {
        std::cout << std::get<0>(item) << "-" << std::get<1>(item) << '\n';
    }

    PairVector<std::string, double>::type x;
    return 0;
}
