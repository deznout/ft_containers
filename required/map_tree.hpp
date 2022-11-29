#ifndef RB_TREE_HPP
#define RB_TREE_HPP

# include <functional>
# include "reverse_iterator.hpp"
# include "bidirect_iterator.hpp"
# include "enable_and_integral.hpp"

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
        typedef	type_node&	reference;
        typedef	const type_node&    const_reference;
        typedef typename Alloc::template rebind<type_node>::other   allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t  difference_type;

        typedef ft::bidirect_iterator<type_node>   iterator;
        typedef ft::reverse_iterator<iterator>  reverse_iterator;

    private:
        pointer _root;
        pointer _nil;
        key_compare _comp;
        size_type _size;
        allocator_type _alloc;

    public:
        explicit red_black_tree(const key_compare& comp = key_compare(),
                                const allocator_type& alloc = allocator_type())
                : _root(0), _nil(0), _comp(comp), _size(0), _alloc(alloc) {
            _nil = _alloc.allocate(1);
            _alloc.construct(_nil, type_node(value_type()));
            _nil->color = BLACK;
            _root = _nil;
        }

        template<class InputIterator>
        red_black_tree(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                       const allocator_type& alloc = allocator_type())
                : _nil(0), _alloc(alloc), _root(0), _size(0), _comp(comp) {
            _nil = _alloc.allocate(1);
            _alloc.construct(_nil, type_node(value_type()));
            _nil->color = BLACK;
            _root = _nil;
            insert(first, last);
        }

        red_black_tree(const red_black_tree& other)
                : _root(0), _nil(0), _comp(other._comp), _size(0), _alloc(other._alloc) {
            _nil = _alloc.allocate(1);
            _alloc.construct(_nil, type_node(value_type()));
            _nil->color = BLACK;
            _root = _nil;
            insert(other.begin(), other.end());
        }

        virtual ~red_black_tree() {
            clear();
            _delete_node(_nil);
        }

        red_black_tree& operator=(const red_black_tree& other) {
            if (this != &other) {
                clear();
                _alloc = other._alloc;
                _comp = other._comp;
                insert(other.begin(), other.end());
            }
            return *this;
        }

        iterator begin() const {
            pointer tmp = _root;
            while (tmp->left != _nil and tmp != _nil)
                tmp = tmp->left;
            return iterator(tmp, _root, _nil);
        }

        iterator end() const {
            return iterator(_nil, _root, _nil);
        }

        reverse_iterator rbegin() const {
            return reverse_iterator(end());
        }

        reverse_iterator rend() const {
            return reverse_iterator(begin());
        }

        size_type size() const { return _size; }

        size_type max_size() const { return _alloc.max_size(); }

        mapped_type& operator[](key_type& key) {
            pointer pos = _search_key(key, _root);
            if (!pos) {
                insert(ft::make_pair<key_type, mapped_type>(key, mapped_type()));
                pos = _search_key(key, _root);
            }
            return pos->data.second;
        }

        bool empty() const { return _size == 0; }

        mapped_type& at(key_type& key) const {
            pointer pos = _search_key(key, _root);
            if (pos) {
                return pos->data.second;
            } else
                throw std::out_of_range("Out of range");
        }

        ft::pair<iterator, bool> insert(const value_type& value) {
            iterator it = find(value.first);
            if (it != end())
                return ft::make_pair(it, false);
            pointer new_node = _create_node(type_node(value));
            if (_root == _nil) {
                new_node->color = BLACK;
                _root = new_node;
            } else
                _insert_helper(new_node, _root);
            it = iterator(new_node, _root, _nil);
            _size++;
            return ft::make_pair(it, true);
        }

        iterator insert(iterator hint, const value_type& value) {
            (void)hint;
            return insert(value).first;
        }

        template<class InputIt>
        void insert(InputIt first, InputIt last,
                    typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0) {
            while (first != last) {
                insert(*first);
                first++;
            }
        }

        void erase(iterator pos) {
            if (pos != end()) {
                _erase_helper(pos._ptr);
                _size--;
            }
        }

        void erase(iterator first, iterator last) {
            while (first != last) {
                erase(first);
                first++;
            }
        }

        size_type erase(const key_type& key) {
            iterator it = find(key);
            if (it == end())
                return 0;
            erase(it);
            return 1;
        }

        iterator find(const key_type& key) const {
            pointer node = _search_key(key, _root);
            if (!node)
                return end();
            return iterator(node, _root, _nil);
        }

        size_type count(const key_type& key) {
            if (find(key) != end())
                return 1;
            return 0;
        }

        ft::pair<iterator, iterator> equal_range(const key_type& key) const {
            return ft::make_pair<iterator, iterator> (lower_bound(key), upper_bound(key));
        }

        iterator lower_bound(const key_type& key) const {
            for (iterator it = begin(); it != end(); ++it) {
                if (!_comp(it._ptr->data.first, key))
                    return it;
            }
            return end();
        }

        iterator upper_bound(const key_type& key) const {
            for (iterator it = begin(); it != end(); ++it) {
                if (_comp(key, it._ptr->data.first))
                    return it;
            }
            return end();
        }

        key_compare key_comp() const { return key_compare(); }

        void clear() {
            _clear_help(_root);
            _root = _nil;
        }

        allocator_type get_allocator() const { return _alloc; }

    private:
        void _clear_help(pointer node) {
            if (node == _nil)
                return ;
            _clear_help(node->left);
            _clear_help(node->right);
            _delete_node(node);
            _size--;
        }

        void _delete_node(pointer node) {
            _alloc.destroy(node);
            _alloc.deallocate(node, 1);
        }

        pointer _search_key(const key_type& key, const pointer& node) const {
            if (node == _nil) {
                return 0;
            } else if (node->data.first == key)
                return node;
            if (_comp(key, node->data.first)) {
                return _search_key(key, node->left);
            } else
                return _search_key(key, node->right);
        }

        pointer _create_node(const_reference value) {
            pointer node = _alloc.allocate(1);
            _alloc.construct(node, value);
            node->parent = _nil;
            node->left = _nil;
            node->right = _nil;
            node->color = RED;
            return node;
        }

        void _rotate_left(pointer x) {
            pointer y = x->right;
            x->right = y->left;
            if (y->left != _nil)
                y->left->parent = x;
            if (y != _nil)
                y->parent = x->parent;
            if (x->parent != _nil) {
                if (x == x->parent->left) {
                    x->parent->left = y;
                } else
                    x->parent->right = y;
            } else
                _root = y;
            y->left = x;
            if (x != _nil)
                x->parent = y;
        }

        void _rotate_right(pointer x) {
            pointer y = x->left;
            x->left = y->right;
            if (y->right != _nil)
                y->right->parent = x;
            if (y != _nil)
                y->parent = x->parent;
            if (x->parent != _nil) {
                if (x == x->parent->right) {
                    x->parent->right = y;
                } else
                    x->parent->left = y;
            } else
                _root = y;
            y->right = x;
            if (x != _nil)
                x->parent = y;
        }

        void _insert_helper(pointer new_node, pointer node) {
            pointer current = node;
            pointer parent = 0;
            while (current != _nil) {
                parent = current;
                if (_comp(new_node->data.first, current->data.first)) {
                    current = current->left;
                } else
                    current = current->right;
            }
            new_node->parent = parent;
            if (_comp(new_node->data.first, parent->data.first)) {
                parent->left = new_node;
            } else
                parent->right = new_node;
            if (new_node->parent != _root)
                _insert_fix_up(new_node);
        }

        void insert_color(pointer node, pointer parent, pointer grandparent, pointer uncle) {
            grandparent->color = RED;
            parent->color = BLACK;
            uncle->color = BLACK;
            node = grandparent;
        }

        void _insert_fix_up(pointer node) {
            pointer uncle = 0;
            pointer parent = node->parent;
            pointer grandparent = node->parent->parent;
            while (node != _root and parent->color == RED) {
                if (parent == grandparent->left) {
                    uncle = grandparent->right;
                    if (uncle->color == BLACK) {
                        if (node == parent->right) {
                            node = parent;
                            _rotate_left(node);
                        }
                        grandparent->color = RED;
                        parent->color = BLACK;
                        _rotate_right(grandparent);
                    } else
                        insert_color(node, parent, grandparent, uncle);
                } else {
                    uncle = grandparent->left;
                    if (uncle->color == BLACK) {
                        if (node == parent->left) {
                            node = parent;
                            _rotate_right(node);
                        }
                        grandparent->color = RED;
                        parent->color = BLACK;
                        _rotate_left(grandparent);
                    } else
                        insert_color(node, parent, grandparent, uncle);
                }
            }
            _root->color = BLACK;
        }

        void color_node(pointer tmp, pointer node, int side) {
            // 0 for left side, 1 for right side
            if (tmp->color == RED) {
                tmp->color = BLACK;
                node->parent->color = RED;
                if (side == 1) {
                    _rotate_left(node->parent);
                    tmp = node->parent->right;
                } else {
                    _rotate_right(node->parent);
                    tmp = node->parent->left;
                }
            }
        }

        void rotate_color(pointer tmp, pointer node, int side) {
            // 0 for left side, 1 for right side
            tmp->color = node->parent->color;
            node->parent->color = BLACK;
            if (side == 1) {
                tmp->right->color = BLACK;
                _rotate_left(node->parent);
            } else {
                tmp->left->color = BLACK;
                _rotate_right(node->parent);
            }
            node = _root;
        }

        void _delete_fix_up(pointer node) {
            while (node != _root and node->color == BLACK) {
                if (node == node->parent->left) {
                    pointer tmp = node->parent->right;
                    color_node(tmp, node, 1);
                    if (tmp->left and tmp->right) {
                        if (tmp->left->color == BLACK and tmp->right->color == BLACK) {
                            tmp->color = RED;
                            node = node->parent;
                        } else {
                            if (tmp->right and tmp->right->color == BLACK) {
                                tmp->left->color = BLACK;
                                tmp->color = RED;
                                _rotate_right(tmp);
                                tmp = node->parent->right;
                            }
                            rotate_color(tmp, node, 1);
                        }
                    }
                } else {
                    pointer tmp = node->parent->left;
                    color_node(tmp, node, 0);
                    if (tmp->right->color == BLACK and tmp->left->color == BLACK) {
                        tmp->color = RED;
                        node = node->parent;
                    } else {
                        if (tmp->left->color == BLACK) {
                            tmp->right->color = BLACK;
                            tmp->color = RED;
                            _rotate_left(tmp);
                            tmp = node->parent->left;
                        }
                        rotate_color(tmp, node, 0);
                    }
                }
            }
            node->color = BLACK;
        }

        void _erase_helper(pointer node) {
            pointer x;
            pointer y;
            if (!node or node == _nil)
                return;
            if (node->left == _nil or node->right == _nil) {
                y = node;
            } else {
                y = node->right;
                while (y->left != _nil)
                    y = y->left;
            }
            if (y->left != _nil) {
                x = y->left;
            } else
                x = y->right;
            x->parent = y->parent;
            if (y->parent) {
                if (y == y->parent->left) {
                    y->parent->left = x;
                } else
                    y->parent->right = x;
            } else
                _root = x;
            if (y != node) {
                _delete_node(node);
                pointer p = _create_node(type_node(y->data));
                node = p;
            }
            if (y->color == BLACK)
                _delete_fix_up(x);
            _delete_node(y);
        }
    };

}

#endif