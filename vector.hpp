#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <iostream>
# include <stdexcept>
# include <algorithm>
# include "required/reverse_iterator.hpp"
# include "required/random_iterator.hpp"
# include "required/enable_and_integral.hpp"
# include "required/compares.hpp"

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

        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::size_type size_type;

    private:
        size_type _size;
        size_type _capacity;
        allocator_type _allocator;
        pointer _arr;

    public:
        explicit vector(const allocator_type &alloc = allocator_type())
        : _size(0), _capacity(0), _allocator(alloc), _arr(0) {}

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc),
                                                                          _arr(0) {
            try { _arr = _allocator.allocate(_capacity); }
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

        vector(const vector &x) : _size(0), _capacity(0), _arr(0), _allocator(x._allocator) {
            clear();
            reserve(x._capacity);
            for (size_t i = 0; i < x._size; ++i) {
                _allocator.construct(_arr + i, x._arr[i]);
            }
            _size = x._size;
//            *this = x;
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
                catch(std::bad_alloc &ex) {
                    std::cerr << "bad_alloc caught: " << ex.what() << std::endl;
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
            if (n < _size) {
                while (n < _size)
                    pop_back();
            } else if (n > _size) {
                while (n > _size)
                    push_back(val);
            }
        }

        size_type capacity() const { return _capacity; }

        bool empty() const { return _size == 0; }

        void reserve(size_type n) {
            if (n > _capacity) {
                pointer new_v = _allocator.allocate(n);
                for (size_type i = 0; i < _size; i++) {
                    _allocator.construct(&new_v[i], _arr[i]);
                    _allocator.destroy(&_arr[i]);
                }
                _allocator.deallocate(_arr, _capacity);
                _arr = new_v;
                _capacity = n;
            }
        }

        reference operator[](size_type n) { return _arr[n]; }

        const_reference operator[](size_type n) const { return _arr[n]; }

        reference at(size_type n) {
            if (n >= _size)
                throw std::out_of_range("Out of range");
            return _arr[n];
        }

        const_reference at(size_type n) const {
            if (n >= _size)
                throw std::out_of_range("Out of range");
            return _arr[n];
        }

        reference front() { return *_arr; }

        const_reference front() const { return *_arr; }

        reference back() { return _arr[_size - 1]; }

        const_reference back() const { return _arr[_size - 1]; }

        pointer data() { return _arr; }

        const pointer data() const { return _arr; }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                    InputIterator>::type* = 0) {
            clear();
            reserve(std::distance(first, last));
            for (; first != last; ++first)
                push_back(*first);
        }

        void assign(size_type n, const value_type& val) {
            if (n > 0) {
                clear();
                reserve(n);
                for (size_t i = 0; i < n; i++)
                    push_back(val);
            }
        }

        void push_back(const value_type& val) {
            if (_capacity == _size && _capacity)
                reserve(2 * _size);
            else
                reserve(1);
            _allocator.construct(_arr + _size, val);
            ++_size;
        }

        void pop_back() {
            if (!_size)
                return ;
            _allocator.destroy(&_arr[_size - 1]);
            _size--;
        }

        iterator insert(iterator position, const value_type& val) {
            difference_type start = std::distance(begin(), position);
            size_type i;
            if (_capacity == _size && _capacity)
                reserve(2 * _capacity);
            else
                reserve(1);
            for (i = _size; i > static_cast<size_type>(start); --i)
                _arr[i] = _arr[i - 1];
            _allocator.construct(_arr + i, val);
            ++_size;
            return iterator(_arr + start);
        }

        void insert(iterator position, size_type n, const value_type& val) {
            difference_type start = std::distance(begin(), position);
            if (n == 0)
                return;
            size_type i;
            if (_size + n > _capacity) {
                if (n > _size)
                    reserve(_size + n);
                else
                    reserve(2 * _capacity);
            }
            for (i = _size; i > static_cast<size_type>(start); --i)
                _arr[i + n - 1] = _arr[i - 1];
            for (i = 0; i < n; ++i)
                _allocator.construct(_arr + start + i, val);
            _size += n;
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                    InputIterator>::type* = 0) {
            if (first == last)
                return;
            difference_type start = std::distance(begin(), position);
            difference_type count = std::distance(first, last);
            if (_size + static_cast<size_type>(count) > _capacity) {
                if (static_cast<size_type>(count) > _size)
                    reserve(_size + static_cast<size_type>(count));
                else
                    reserve(2 * _capacity);
            }
            size_type i;
            for (i = _size; i > static_cast<size_type>(start); --i)
                _arr[i + static_cast<size_type>(count) - 1] = _arr[i - 1];
            for (i = 0; i < static_cast<size_type>(count); ++i, ++first)
                _allocator.construct(_arr + start + i, *first);
            _size += count;
        }

        iterator erase(iterator position) {
            difference_type start = std::distance(begin(), position);
            _allocator.destroy(_arr + start);
            for (size_type i = static_cast<size_type>(start); i < _size - 1; ++i)
                _arr[i] = _arr[i + 1];
            --_size;
            return position;
        }

        iterator erase(iterator first, iterator last) {
            difference_type start = std::distance(begin(), first);
            if (first == last)
                return iterator(_arr + start);
            difference_type count = std::distance(first, last);
            for (iterator it = first; it != last; ++it)
                _allocator.destroy(&(*it));
            for (size_type i = static_cast<size_type>(start); i < _size - count; ++i)
                _arr[i] = _arr[i + count];
            _size -= count;
            return first;
        }

        void swap(vector& x) {
            std::swap(_arr, x._arr);
            std::swap(_size, x._size);
            std::swap(_capacity, x._capacity);
            std::swap(_allocator, x._allocator);
        }

        void clear() {
            if (_arr) {
                for (size_t i = 0; i < _size; ++i)
                    _allocator.destroy(_arr + i);
            }
            _size = 0;
        }

        allocator_type get_allocator() const { return _allocator; }
    };

    template<class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template<class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs == rhs); }

    template<class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(rhs < lhs); }

    template<class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return rhs < lhs; }

    template<class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs < rhs); }

    template<class T, class Alloc>
    void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

}

#endif