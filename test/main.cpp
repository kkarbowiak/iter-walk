#include <vector>
#include <string>
#include <list>
#include <set>
#include <iostream>

#include "iterWalk.h"


template<class C>
void do_walk(C const & c)
{
    for (auto i : iter::walk(c))
    {
        std::cout << "first: " << i.is_first() << ", last: " << i.is_last() << ", index: " << i.get_index() << ", value: " << *i << '\n';
    }
}

template<class C>
void do_walk(C & c)
{
    for (auto i : iter::walk(c))
    {
        std::cout << "first: " << i.is_first() << ", last: " << i.is_last() << ", index: " << i.get_index() << ", value: " << *i << '\n';
    }
}

int main()
{
    std::vector<int> ivec = {3, 5, 7, 8, 9};
    std::vector<float> fvec = {.3, .5, .7, .8, .9};
    std::vector<std::string> svec = {"one", "two", "three", "four", "five"};
    std::list<int> ilis = {8, 7, 6, 5, 4};
    std::set<int> iset = {2, 4, 6, 8, 9};

    do_walk(ivec);
    do_walk(fvec);
    do_walk(svec);
    do_walk(ilis);
    do_walk(iset);
}
