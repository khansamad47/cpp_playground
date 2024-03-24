#include <iostream>
#include <vector>

class TypeErasedContainer {
  private:
    class TypeConcept {
      public:
        virtual void func() = 0; 
    };
    
    template<class T>
    class TypeModel: public TypeConcept {
      private:
        T* p_obj;
      public:
        TypeModel(T* obj): p_obj(obj) {}
        void func() override
        {
            p_obj->func();
        }
    };
    std::vector<TypeConcept*> d_data;

  public:
    template<class T>
    void insert(T* item) {
        d_data.push_back(new TypeModel<T>(item));    
    }
    void func() {
        for (auto& item: d_data)
        {
            item->func();
        }
    }
};
class Foo {
  public:
    void func()
    {
        std::cout << "Foo" << '\n';
    }
};

class Bar {
  public:
    void func()
    {
        std::cout << "Bar" << '\n';
    }
};

int main()
{
    TypeErasedContainer list;
    list.insert(new Foo());
    list.insert(new Bar());
    list.func();
    return 0;
}
