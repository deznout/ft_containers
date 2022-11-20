#ifndef MINE_RANDOM_ITERATOR_HPP
#define MINE_RANDOM_ITERATOR_HPP

# include <cstddef>
# include <iterator>

namespace ft
{

    template <class T>
    class random_iterator
    {
    public:
        typedef T         value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type*  pointer;
        typedef value_type& reference;
        typedef std::random_access_iterator_tag  iterator_category;

    protected:
        pointer _ptr;

    public:
        random_iterator() : _ptr(0) {}
        explicit random_iterator(pointer ptr) : _ptr(ptr) {}
        random_iterator(const random_iterator& other) : _ptr(other._ptr) {}
        virtual ~random_iterator() {}

        pointer base() const { return _ptr; }

        random_iterator& operator=(const random_iterator& other) {
            if (this != &other)
                _ptr = other._ptr;
            return *this;
        }

        operator random_iterator<const value_type>() const {
            return random_iterator<const value_type>(_ptr);
        }

        reference operator*() const { return *_ptr; }

        random_iterator operator+(difference_type n) const {
            return random_iterator(_ptr + n);
        }

        random_iterator& operator++() {
            _ptr++;
            return *this;
        }

        random_iterator operator++(int) {
            random_iterator temp = *this;
            _ptr++;
            return temp;
        }

        random_iterator& operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }

        difference_type operator+(const random_iterator& other) const {
            return base() + other.base();
        }

        random_iterator operator-(difference_type n) const {
            return random_iterator(_ptr - n);
        }

        random_iterator& operator--() {
            _ptr--;
            return *this;
        }

        random_iterator operator--(int) {
            random_iterator temp = *this;
            _ptr--;
            return temp;
        }

        random_iterator& operator-=(difference_type n) {
            _ptr -= n;
            return *this;
        }

        difference_type operator-(const random_iterator& other) const {
            return base() - other.base();
        }

        pointer operator->() const { return _ptr; }

        reference operator[](difference_type n) const { return *(_ptr + n); }

        bool operator==(const random_iterator& other) const {
            return this->_ptr == other._ptr;
        }

        bool operator!=(const random_iterator& other) const {
            return this->_ptr != other._ptr;
        }

        bool operator>=(const random_iterator& other) const {
            return this->_ptr >= other._ptr;
        }

        bool operator<=(const random_iterator& other) const {
            return this->_ptr <= other._ptr;
        }

        bool operator>(const random_iterator& other) const {
            return this->_ptr > other._ptr;
        }

        bool operator<(const random_iterator& other) const {
            return this->_ptr < other._ptr;
        }
    };

//    template <class Iterator>
//    bool operator==(const random_iterator<Iterator>& lhs,
//                    const random_iterator<Iterator>& rhs) {
//        return lhs.base() == rhs.base();
//    }
//
//    template <class Iterator>
//    bool operator!=(const random_iterator<Iterator>& lhs,
//                    const random_iterator<Iterator>& rhs) {
//        return lhs.base() != rhs.base();
//    }
//
//    template <class Iterator>
//    bool operator<(const random_iterator<Iterator>& lhs,
//                   const random_iterator<Iterator>& rhs) {
//        return lhs.base() < rhs.base();
//    }
//
//    template <class Iterator>
//    bool operator<=(const random_iterator<Iterator>& lhs,
//                    const random_iterator<Iterator>& rhs) {
//        return lhs.base() <= rhs.base();
//    }
//
//    template <class Iterator>
//    bool operator>(const random_iterator<Iterator>& lhs,
//                   const random_iterator<Iterator>& rhs) {
//        return lhs.base() > rhs.base();
//    }
//
//    template <class Iterator>
//    bool operator>=(const random_iterator<Iterator>& lhs,
//                    const random_iterator<Iterator>& rhs) {
//        return lhs.base() >= rhs.base();
//    }
//

    template <class Iterator1, class Iterator2>
    bool operator==(const random_iterator<Iterator1>& lhs,
                    const random_iterator<Iterator2>& rhs) {
        return lhs.base() == rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator!=(const random_iterator<Iterator1>& lhs,
                    const random_iterator<Iterator2>& rhs) {
        return lhs.base() != rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator<(const random_iterator<Iterator1>& lhs,
                   const random_iterator<Iterator2>& rhs) {
        return lhs.base() < rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator<=(const random_iterator<Iterator1>& lhs,
                    const random_iterator<Iterator2>& rhs) {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator>(const random_iterator<Iterator1>& lhs,
                   const random_iterator<Iterator2>& rhs) {
        return lhs.base() > rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator>=(const random_iterator<Iterator1>& lhs,
                    const random_iterator<Iterator2>& rhs) {
        return lhs.base() >= rhs.base();
    }

    template <class Iterator>
    random_iterator<Iterator> operator+(typename random_iterator<Iterator>::difference_type n,
                                        const random_iterator<Iterator>& rev_it) {
        return n + rev_it;
    }

    template <class Iterator>
    random_iterator<Iterator> operator-(typename random_iterator<Iterator>::difference_type n,
                                        const random_iterator<Iterator>& rev_it) {
        return n - rev_it;
    }

}

#endif