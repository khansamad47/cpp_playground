#include <vector>
#include <string>
#include <map>
#include <memory>
#include <typeinfo>
#include <iostream>

// sturct approch maybe it has a variant interface function which must be provided by the user`


class Column{
  public:
    virtual const std::type_info& getType() const = 0;
    virtual size_t size() const = 0;
};

template<class T>
class TypedColumn: public Column {
  public:
    using vector_type = std::vector<T>;
  private:
    vector_type d_data;
  public:
    TypedColumn(vector_type&& data): d_data(data) {}
    const vector_type& data() const { return d_data; };
    virtual size_t size() const override  { return d_data.size(); }
    virtual const std::type_info& getType() const override { return typeid(T); }
  private:
     
};

class DataFrame {
    private:
        std::map<std::string, std::unique_ptr<Column>> d_columns;
    public:
        template<class T>
        void addColumn(std::string name, std::vector<T>&& column) {
            d_columns[name] = std::make_unique<TypedColumn<T>>(std::move(column));
        }

        const Column& getColumn(std::string name) const {
            return *d_columns.at(name).get();
        }

        template<class T>
        const TypedColumn<T>& getTypedColumn(std::string name) const {
            return *(static_cast<TypedColumn<T>*>(d_columns.at(name).get()));
        }

        void print(std::ostream& os) {
            for (auto& [name, col] 
        }
};
