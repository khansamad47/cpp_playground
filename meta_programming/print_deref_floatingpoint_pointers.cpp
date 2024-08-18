#include <iostream>

// Type Traits
template<typename T>
struct is_pointer {
    constexpr static bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    constexpr static bool value = true;
};

template<typename T>
struct remove_pointer {
    using type_name = T;
};

template<typename T>
struct remove_pointer<T*> {
    using type_name = T;
};

template<typename T>
void printp(T t)
{
    // typename is required here. It tells the compiler that 
    // type_name is a 'typename' before hand so that the compiler 
    // knows that if a type X is passed to printp it should not generate
    // a function template and throw error if remove_pointer<T>::type_name 
    // is not a typename but something else (function or variable)
    // There could be a specialization of remove_pointer where type_name
    // is a variable for example?
    using BaseType = typename remove_pointer<T>::type_name;
    if constexpr (is_pointer<T>::value == true && std::is_floating_point< BaseType >::value)
    {
        // T is pointer
        std::cout << *t;
    }
    else {
        std::cout << t;
    }
}

int main()
{
    remove_pointer<int*>::type_name y = 2;
    float x = 42;
    printp(x);
    printp('\n');
    printp(&x);
    printp('\n');
}
