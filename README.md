# C++11 Walk #

C++11 introduced the so called range-based for loops, which allow iterating over whole container using nice and short syntax:

```c++
std::vector<int> vec = {1, 2, 3, 4};
for (auto & v : vec)
{
    v *= 3;
}
```

The range-based for loop is great, but is only usable in the most simple forward iteration. Should you require anything that is less trivial (like for example reverse iteration, or assessing whether visited element is the last one), you are forced to roll on your own solution.

This little header-only library rectifies this.

## Walk ##

The main utility is the `walk` template function. It accepts a reference to a container and returns a proxy object called `walker`, which is intended to be used in place of the original container in the range-based loop. To facilitate this, this proxy object has `begin` and `end` functions that return a proxy iterator. Upon dereferencing, this proxy iterator returns another proxy object that allows accessing the underlying value and querying some information.

This may sound complicated, but the usage is quite simple. The loop from first paragraph can be rewritten as:

```c++
std::vector<int> vec = {1, 2, 3, 4};
for (auto i : iter::walk(vec))  // notice call to iter::walk
{
    *i *= 3;  // notice the extra asterisk in front
}
```

Above, `i` represents the proxy object that has the following interface:
```c++
class walk_proxy
{
    public:
        typename Iterator::reference operator*() const  // access to the underlying value
        typename Iterator::reference get() const  // access to the underlying value
        bool is_first() const  // returns true for first iterated-over value
        bool is_last() const  // returns true for last iterated-over value
        Size get_index() const  // returns index of iterated-over value
        Iterator get_iterator() const  // returns underlying iterator
}
```

A simple example showcasing the abilities of this library:

```c++
#include "iterWalk.h"

#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> svec = {"one", "two", "three", "four", "five"};

    for (auto i : iter::walk(svec))
    {
        std::cout << i.get_index() << ": " << *i;
        if (i.is_first())
        {
            std::cout << " [first]";
        }
        if (i.is_last())
        {
            std::cout << " [last]";
        }
        std::cout << '\n';
    }
}
```

This produces:
```
0: one [first]
1: two
2: three
3: four
4: five [last]
```

## License ##

This project is released under **MIT/X11** license, so feel free to do anything you like with it.
