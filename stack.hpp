#ifndef STACK_HPP
#define STACK_HPP

#include "vector"

namespace ft {
    template <class T, class Container = std::vector<T> >
    class stack {
    public:
    stack();
    ~stack();

    int empty();
    int size();
    Container back();
    void push_back(Container);
    void pop_back();
    };
}

#endif
