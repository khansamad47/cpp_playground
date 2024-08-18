#include <iostream>

// This is called type traits in C++. I am using templates
// here in a very different way where based on the type the 
// value of the static variable will be evaluated. For all
// types T e.g int is_pointer<int>::value will be false
// however anytime there is a pointer type passed as a template
// argument is_pointer<int*>::value will be true!

template<typename T>
struct is_pointer {
    constexpr static bool value = false;
};

template <typename T>
struct is_pointer<T*> {
    constexpr static bool value = true;
};

template<typename T>
void printp(T t)
{
    // This constexpr is a must to use otherwise 
    // this will not compile.
    if constexpr (std::is_pointer<T>::value == true)
    {
        std::cout << *t;
    }
    else {
        std::cout << t;
    }
}

// If I dont use constexpr in the if check this fails to compile !!
// Error: Indirection requires pointer operand ('int' invalid)
// This is so weird! but it does make sense, constexpr makes sure that at 
// compile time one of the if or else branch is droped 
// Q. What would one do in C++03?
// A. You would likely have to implement two verions of this, one of pointer 
//    and one for regular. 
//
//    template<typename T>
//    void printp(T t)
//    {
//         std::cout << t;
//    }
//
//    template<typename T>
//    void printp(T* t)
//    {
//         std::cout << *t;
//    }
//
//    Q. But is there a way to do this with typetraits in C++03?

//template<typename T, typename ... Args>
//void printp(const T& t, const Args& ... args)
//{
//    printp(t);
//    printp(" ");
//    printp(args...);
//}

int main() 
{
    int x = 5;
    printp(x);    
    printp(&x);    
    //printp(1,2,3,4,5,'\n');    
    return 0;
}
