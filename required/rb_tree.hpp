#ifndef RB_TREE_HPP
#define RB_TREE_HPP

# include <functional>
# include "reverse_iterator.hpp"
# include "bidirect_iterator.hpp"

namespace ft
{

    enum color { RED, BLACK };

    template<class T>
    struct tree_node {
        typedef T value_type;
        value_type data;
        tree_node* parent;
        tree_node* left;
        tree_node* right;
        color   color;

        tree_node(value_type data) : data(data), parent(0), left(0), right(0), color(BLACK) {}
    };

    template<class T, class Compare = std::less<typename T::first_type>,
            class Alloc = std::allocator<T> >
    class red_black_tree {
    public:
        typedef T   value_type;
        typedef typename T::first_type  key_type;
        typedef typename T::second_type mapped_type;
        typedef Compare key_compare;
        typedef	tree_node<value_type>   type_node;

        typedef	type_node*  pointer;
        typedef	const type_node*    const_pointer;
        typedef	type_node&	reference;
        typedef	const type_node&    const_reference;
        typedef typename Alloc::template rebind<type_node>::other   allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t  difference_type;

        typedef ft::bidirect_iterator<type_node>   iterator;
        typedef ft::bidirect_iterator<const type_node> const_iterator;
        typedef ft::reverse_iterator<iterator>  reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    };

}

#endif