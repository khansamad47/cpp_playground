#include <iostream>
#include <vector>
#include <memory>

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
    std::vector< std::unique_ptr<TypeConcept> > d_data;

  public:
    template<class T>
    void insert(T* item) {
        d_data.emplace_back(new TypeModel<T>(item));    
    }
    void func() {
        for (auto& item: d_data)
        {
            item->func();
        }
    }
    ~TypeErasedContainer(){
        
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
    std::unique_ptr<Foo> pF (new Foo());
    std::unique_ptr<Bar> pB (new Bar());
    list.insert(pF.get());
    list.insert(pB.get());
    list.func();
    return 0;
}
