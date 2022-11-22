#ifndef MAP_HPP
#define MAP_HPP

# include <functional>
# include <memory>
# include "required/pair.hpp"


namespace ft
{

    template< class Key, class T, class Compare = std::less<Key>,
            class Alloc = std::allocator<pair<const Key,T> > >
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type , mapped_type> value_type;
        typedef Compare key_compare;

        //typedef value_compare //Nested function class to compare elements	see value_comp
        //value_compare value_comp() const;

        typedef Alloc allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;

//        typedef iterator	//a bidirectional iterator to value_type	convertible to const_iterator
//        typedef const_iterator	//a bidirectional iterator to const value_type
//        typedef reverse_iterator	//reverse_iterator<iterator>
//        typedef const_reverse_iterator	//reverse_iterator<const_iterator>
//
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;



    };

}

#endif