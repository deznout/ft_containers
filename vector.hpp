#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <iostream>
# include <stdexcept>
# include <algorithm>
# include "required/reverse_iterator.hpp"
# include "required/random_iterator.hpp"
# include "required/enable_and_integral.hpp"

namespace ft
{

    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
    public:
        typedef T           value_type;
        typedef Allocator   allocator_type;

        typedef T   &reference;
        typedef const T &const_reference;
        typedef T   *pointer;
        typedef const T *const_pointer;

        typedef ft::random_iterator<value_type>									iterator;
        typedef ft::random_iterator<const value_type>							const_iterator;
        typedef ft::reverse_iterator<iterator>											reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;

        typedef long int    difference_type;
        typedef size_t  size_type;

    private:
        size_type _size;
        size_type _capacity;
        allocator_type _allocator;
        pointer _arr;

    public:
        explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc), _arr(0) {}

        explicit vector (size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc), _arr(0) {
            try { this->arr_ = _allocator.allocate(this->_capacity); }
            catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl;
                this->_capacity = 0; this->_size = 0; throw ;}
            try
            {
                for (size_t i = 0; i < this->_size; ++i)
                    _allocator.construct(&_arr[i], val);
            }
            catch(...)
            {
                std::cerr << "construct threw exp.\n";
                for (size_t i = 0; i < this->_size; ++i)
                    _allocator.destroy(&_arr[i]);
                this->_size = 0;
            }
        }

//        template <class InputIterator>
//        vector (InputIterator first, InputIterator last,
//                const allocator_type& alloc = allocator_type(),
//                typename ft::enable_if<!ft::is_integral<InputIterator>::>) {
//
//        }

        vector (const vector& x);

    };

}

#endif