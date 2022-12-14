#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

    template <class Iterator>
    class reverse_iterator
    {
    protected:
        Iterator current;

    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;


        reverse_iterator() : current() {}

        explicit reverse_iterator(iterator_type iter) : current(iter) {}

        template <class U>
        reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}
        virtual ~reverse_iterator() {}

        iterator_type base() const { return current; }

        reverse_iterator& operator=(const reverse_iterator& other) {
            if (this != &other)
                current = other.current;
            return *this;
        }

        reference operator*() const {
            iterator_type tmp = current;
            tmp--;
            return *tmp;
        }

        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(current - n);
        }

        reverse_iterator& operator++() {
            --current;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator temp = *this;
            current--;
            return temp;
        }

        reverse_iterator& operator+=(difference_type n) {
            current -= n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(current + n);
        }

        reverse_iterator& operator--() {
            ++current;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator temp = *this;
            current++;
            return temp;
        }

        reverse_iterator& operator-=(difference_type n) {
            current += n;
            return *this;
        }

        pointer operator->() const { return &operator*(); }

        reference operator[](difference_type n) const { return *(current - n - 1); }

        bool operator==(const reverse_iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const reverse_iterator& other) const {
            return current != other.current;
        }

        bool operator>=(const reverse_iterator& other) const {
            return current <= other.current;
        }

        bool operator<=(const reverse_iterator& other) const {
            return current >= other.current;
        }

        bool operator>(const reverse_iterator& other) const {
            return current < other.current;
        }

        bool operator<(const reverse_iterator& other) const {
            return current > other.current;
        }
    };

    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs) {
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs) {
        return lhs.base() != rhs.base();
    }

    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
        return lhs.base() > rhs.base();
    }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs) {
        return lhs.base() >= rhs.base();
    }

    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
        return lhs.base() < rhs.base();
    }

    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs) {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                         const reverse_iterator<Iterator>& rev_it) {
        return rev_it + n;
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n,
                                         const reverse_iterator<Iterator>& rev_it) {
        return n - rev_it;
    }

    template<class IteratorL, class IteratorR>
    typename reverse_iterator<IteratorL>::difference_type operator-(reverse_iterator<IteratorL>& lhs,
                                                                    reverse_iterator<IteratorR>& rhs) {
        return rhs.base() - lhs.base();
    }

//    template <class Iterator1, class Iterator2>
//    bool operator==(const reverse_iterator<Iterator1>& lhs,
//            const reverse_iterator<Iterator2>& rhs) {
//        return lhs.base() == rhs.base();
//    }
//
//    template <class Iterator1, class Iterator2>
//    bool operator!=(const reverse_iterator<Iterator1>& lhs,
//            const reverse_iterator<Iterator2>& rhs) {
//        return lhs.base() != rhs.base();
//    }
//
//    template <class Iterator1, class Iterator2>
//    bool operator<(const reverse_iterator<Iterator1>& lhs,
//            const reverse_iterator<Iterator2>& rhs) {
//        return lhs.base() > rhs.base();
//    }
//
//    template <class Iterator1, class Iterator2>
//    bool operator<=(const reverse_iterator<Iterator1>& lhs,
//            const reverse_iterator<Iterator2>& rhs) {
//        return lhs.base() >= rhs.base();
//    }
//
//    template <class Iterator1, class Iterator2>
//    bool operator>(const reverse_iterator<Iterator1>& lhs,
//                   const reverse_iterator<Iterator2>& rhs) {
//        return lhs.base() < rhs.base();
//    }
//
//    template <class Iterator1, class Iterator2>
//    bool operator>=(const reverse_iterator<Iterator1>& lhs,
//            const reverse_iterator<Iterator2>& rhs) {
//        return lhs.base() <= rhs.base();
//    }


}

#endif