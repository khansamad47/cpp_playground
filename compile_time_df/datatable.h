#include <unordered_map>
#include <tuple>


template <class ROW_KEY, class ...TTypes>
class DataTable {
  public:
    using row_type = std::tuple<TTypes...>;
    using const_iterator = typename std::unordered_map<ROW_KEY, row_type>::const_iterator;

  private:
    std::unordered_map<ROW_KEY, row_type> d_data;

  public:
    DataTable() {}

    bool createRow(ROW_KEY key) {
        return d_data.insert({ key, {}}).second;
    }

    template<std::size_t COLUMN_INDEX>
    decltype(auto) cell(ROW_KEY key) {
        return std::get<COLUMN_INDEX>(d_data[key]);
    }

    const_iterator begin() const {
        return d_data.begin();
    }

    const_iterator end() const{
        return d_data.end();
    }
};

template <std::size_t COLUMN_INDEX, class ROW_KEY, class ...TTypes>
auto sum(const DataTable<ROW_KEY, TTypes...>& d)
{
    using ElementType = typename DataTable<ROW_KEY, TTypes...>::row_type;
    typename std::tuple_element<COLUMN_INDEX, ElementType>::type total = 0;
    for (auto it = d.begin(); it != d.end(); ++it)
    {
        total += std::get<COLUMN_INDEX>(*it); 
    }
    return total;
}
