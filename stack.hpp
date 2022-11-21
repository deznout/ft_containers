#ifndef STACK_HPP
#define STACK_HPP

# include "vector.hpp"

namespace ft
{

    template <class T, class Container = ft::vector<T> >
    class stack {
    public:
        typedef T   value_type;
        typedef Container   container_type;
        typedef size_t  size_type;

    protected:
        container_type _ctnr;

    public:
        explicit stack (const container_type& ctnr = container_type()) : _ctnr(ctnr) {}

        virtual ~stack() {}

        container_type get_ctnr() const { return _ctnr; }

        bool empty() const { return _ctnr.empty(); }

        size_type size() const { return _ctnr.size(); }

        value_type& top() { return _ctnr.back(); }

        const value_type& top() const { return _ctnr.back(); }

        void push (const value_type& val) { _ctnr.push_back(val); }

        void pop() { _ctnr.pop_back(); }
    };

    template<class T, class Container>
    bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs.get_ctnr() == rhs.get_ctnr();
    }

    template<class T, class Container>
    bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs.get_ctnr() != rhs.get_ctnr();
    }

    template<class T, class Container>
    bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs.get_ctnr() < rhs.get_ctnr();
    }

    template<class T, class Container>
    bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs.get_ctnr() <= rhs.get_ctnr();
    }

    template<class T, class Container>
    bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs.get_ctnr() > rhs.get_ctnr();
    }

    template<class T, class Container>
    bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return lhs.get_ctnr() >= rhs.get_ctnr();
    }

}

#endif