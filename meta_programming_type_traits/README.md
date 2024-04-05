# Type Traits
This example was given BitsOfQ lectures on templae meta programming in C++

Q1. Write a print function which accepts N arguments and prints data
to cout but if a pointer is passed it will deference it and then print.

Q2. The deference should only happen for floats

Something interesting I found while doing this example was that constexpr is a 
must in the if condition because if I dont have it then the compiler cannot generate
the template function.

```
template <typename T>
void printp(T t)
{   
    // without the constexpr this will fail to compile
    if constexpr (std::is_pointer<T>::value == true)
    {
        std::cout << *t
    }
    else {
        std::cout << t
    }
}
```

The `constexpr` that one of the branch is thrown out during compilation. `nm`
confirms this that the compiler generates two template functions.

```
nm a.out | c++filt 
34 000000000000126b W void printp<int>(int)
35 0000000000001291 W void printp<int*>(int*)
```
