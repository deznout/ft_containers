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

    template<class T, class Allocator = std::allocator<T> >
    class vector {
    public:
        typedef T value_type;
        typedef Allocator allocator_type;

        typedef T &reference;
        typedef const T &const_reference;
        typedef T *pointer;
        typedef const T *const_pointer;

        typedef ft::random_iterator<value_type> iterator;
        typedef ft::random_iterator<const value_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef long int difference_type;
        typedef size_t size_type;

    private:
        size_type _size;
        size_type _capacity;
        allocator_type _allocator;
        pointer _arr;

    public:
        explicit vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc),
                                                                          _arr(0) {}

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc),
                                                                          _arr(0) {
            try { this->arr_ = _allocator.allocate(this->_capacity); }
            catch (std::bad_alloc &ex) {
                std::cerr << "bad_alloc caught: " << ex.what() << std::endl;
                _capacity = 0;
                _size = 0;
                throw;
            }
            try {
                for (size_t i = 0; i < _size; ++i)
                    _allocator.construct(&_arr[i], val);
            }
            catch (...) {
                std::cerr << "construct threw exp.\n";
                for (size_t i = 0; i < _size; ++i)
                    _allocator.destroy(&_arr[i]);
                _size = 0;
            }
        }

        template<class InputIterator>
        vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                InputIterator>::type first, InputIterator last, const allocator_type &alloc = allocator_type())
                : _size(0), _capacity(0), _allocator(alloc), _arr(NULL) {
            InputIterator tmp(first);
            while (tmp++ != last)
                _size++;
            _capacity = _size;
            _arr = _allocator.allocate(_size);
            for (int i = 0; first != last; ++first, ++i)
                _allocator.construct(&_arr[i], *first);
        }

        vector(const vector &x) : _size(), _capacity() {
            *this = x;
        }

        ~vector() {
            if (_arr) {
                for (size_type i = 0; i < _size; i++)
                    _allocator.destroy(&_arr[i]);
            }
            _arr = NULL;
            if (_capacity) {
                _allocator.deallocate(_arr, _capacity);
            }
        }

        vector &operator=(const vector &other)
        {
            if (this != &other)
            {
                this->~vector();
                _allocator = other._allocator;
                _capacity = other._capacity;
                _size = other._size;
                try {_arr = _allocator.allocate(_capacity);}
                catch(std::bad_alloc &ex) {std::cerr << "bad_alloc caught: " << ex.what() << std::endl;
                    _size = 0 ; _capacity = 0; throw; }
                try {
                    for (size_t i = 0; i < _size; ++i)
                        _allocator.construct(_arr + i, *(other._arr + i));
                }
                catch(...)
                {
                    std::cerr << "construct threw exp.\n";
                    for (size_t i = 0; i < _size; ++i)
                        _allocator.destroy(_arr + i);
                    _size = 0;
                    throw;
                }
            }
            return (*this);
        }

        iterator begin() { return iterator(_arr); }

        const_iterator begin() const { return const_iterator(_arr); }

        iterator end() { return iterator(_arr + _size); }

        const_iterator end() const { return iterator(_arr + _size); }

        reverse_iterator rbegin() { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

        reverse_iterator rend() { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const { return reverse_iterator(begin()); }

        size_type size() const { return _size; }

        size_type max_size() const { return _allocator.max_size(); }

        void resize(size_type n, value_type val = value_type()) {

        }

        size_type capacity() const { return _capacity; }

        bool empty() const { return _size == 0; }
//        reserve


    };




}

#endif