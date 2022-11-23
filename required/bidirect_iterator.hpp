#ifndef BIDIRECT_ITERATOR_HPP
#define BIDIRECT_ITERATOR_HPP

# include <cstddef>
# include <iterator>
//# include "reverse_iterator.hpp" //???

namespace ft
{

    template<class Node>
    class bidirect_iterator {
    public:
        typedef Node    value_type;
        typedef value_type* node_ptr;
        typedef std::ptrdiff_t  difference_type;
        typedef typename Node::value_type const data_type;

        typedef data_type*  pointer;
        typedef data_type& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        node_ptr    _ptr;

    private:
        node_ptr    _root;
        node_ptr    _nil;

    public:
        bidirect_iterator() : _nil(0), _ptr(0), _root(0) {}

        bidirect_iterator(node_ptr ptr, node_ptr root, node_ptr nil)
        : _ptr(ptr), _root(root), _nil(nil) {}

        bidirect_iterator(const bidirect_iterator &other)
        : _nil(other._nil), _root(other._root), _ptr(other._ptr) {}

        virtual ~bidirect_iterator() {}

        bidirect_iterator& operator=(const bidirect_iterator &other) {
            if (this != &other) {
                _ptr = other._ptr;
                _root = other._root;
                _nil = other._nil;
            }
            return *this;
        }

        operator bidirect_iterator<const value_type>() const {
            return bidirect_iterator<const value_type>(_ptr, _root, _nil);
        }

        reference operator*() const {
            return _ptr->data;
        }

        bidirect_iterator& operator++() {
            if (_ptr != _nil)
                _ptr = _next_node(_ptr);
            return *this;
        }

        bidirect_iterator operator++(int) {
            bidirect_iterator copy = *this;
            _ptr = _next_node(_ptr);
            return copy;
        }

        bidirect_iterator& operator--() {
            if (_ptr == _nil) {
                _ptr = _root;
                while (_ptr->right != _nil && _ptr != _nil)
                    _ptr = _ptr->right;
            } else
                _ptr = _prev_node(_ptr);
            return *this;
        }

        bidirect_iterator operator--(int) {
            bidirect_iterator copy = *this;
            operator--();
            return copy;
        }

        pointer operator->() const {
            return &(operator*());
        }

        bool operator==(const bidirect_iterator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const bidirect_iterator& other) const {
            return _ptr != other._ptr;
        }

    private:
        node_ptr _prev_node(node_ptr node) {
            node_ptr tmp = node;

            if (tmp->left != _nil) {
                tmp = tmp->left;
                while (tmp->right != _nil)
                    tmp = tmp->right;
                return tmp;
            } else {
                node_ptr prev_tmp = tmp->parent;
                while (prev_tmp && tmp == prev_tmp->left) {
                    tmp = prev_tmp;
                    prev_tmp = prev_tmp->parent;
                }
                if (!prev_tmp) {
                    return _nil;
                } else
                    return prev_tmp;
            }
        }

        node_ptr _next_node(node_ptr node) {
            node_ptr tmp = node;

            if (tmp == _nil)
                return _nil;
            if (tmp->right != _nil) {
                tmp = tmp->right;
                while (tmp->left != _nil && tmp != _nil)
                    tmp = tmp->left;
                return tmp;
            } else {
                node_ptr next_tmp = tmp->parent;
                while (next_tmp != _nil && tmp == next_tmp->right) {
                    tmp = next_tmp;
                    next_tmp = next_tmp->parent;
                }
                if (!next_tmp) {
                    return _nil;
                } else
                    return next_tmp;
            }
        }

    };

}

#endif