# Alias Templates
Since C++11 now we can create type alias using the `using` keyword with templates.

```cpp

template<typename... T>
using TupleVector = std::tuple<T...>;
```

[Godbolt Link](https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:34,endLineNumber:5,positionColumn:34,positionLineNumber:5,selectionStartColumn:34,selectionStartLineNumber:5,startColumn:34,startLineNumber:5),source:'%23include+%3Cstring%3E%0A%23include+%3Ctuple%3E%0A%0Atemplate%3Ctypename...+T%3E%0Ausing+TupleVector+%3D+std::tuple%3CT...%3E%3B%0A%0Aint+main()+%7B%0A++++TupleVector%3Cint,+bool,+std::string%3E+x%7B1,+true,+%22Test%22%7D%3B%0A%7D'),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:g142,filters:(b:'0',binary:'1',binaryObject:'1',commentOnly:'0',debugCalls:'1',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'0',trim:'1',verboseDemangling:'0'),flagsViewOpen:'1',fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!(),options:'--std%3Dc%2B%2B11',overrides:!(),selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),source:1),l:'5',n:'0',o:'+x86-64+gcc+14.2+(Editor+%231)',t:'0')),k:50,l:'4',n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4)

Before C++11, this was done via
```cpp
template<typename... T>
struct TupleVector {
    using type = std::tuple<T...>;
}
```

In C++14 the standard used this features and provided a lot short hands for types in `type_traits` header

```cpp
template<typename T>
using remove_reference_t = typename remove_reference<T>::type;
```
