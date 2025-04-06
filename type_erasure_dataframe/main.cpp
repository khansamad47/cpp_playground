#include "dataframe.h"


int main() {
    DataFrame df;
    std::vector<std::string> tickers = {"IBM", "FB", "GOOGLE"};
    std::vector<double> prices = {10.0, 15.5, 30.0};

    df.addColumn("Tickers", std::move(tickers));
    df.addColumn("Prices", std::move(prices));

    auto& col = df.getColumn("Tickers");
    std::cout << "Size of Tickers = " << col.size() << std::endl;
    auto& col2 = df.getColumn("Prices");
    std::cout << "Size of Positions = " << col.size() << std::endl;

    const auto& col3 = df.getTypedColumn<double>("Prices");
    std::vector<double> values = col3.data();
    std::cout << "values = " << "[";
    for (auto& item: values)
    {
        std::cout << item << " ";
    }
    std::cout << "]" << '\n';
    return 0;
}
