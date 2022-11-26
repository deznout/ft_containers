#ifndef SET_HPP
#define SET_HPP

# include <memory>
# include "required/set_tree.hpp"
# include "required/compares.hpp"

namespace ft
{
    template<class T, class Compare = std::less<T>,
            class Alloc = std::allocator<T> >
    class set {
    public:
        typedef T   key_type;
        typedef T   value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Alloc   allocator_type;
        typedef value_type& reference;
        typedef const value_type&   const_reference;
        typedef value_type* pointer;
        typedef const value_type*   const_pointer;
        typedef typename ft::red_black_tree<value_type, key_compare, allocator_type> tree_type;

        typedef typename tree_type::iterator    iterator;
        typedef typename tree_type::iterator  const_iterator;
        typedef typename tree_type::reverse_iterator    reverse_iterator;
        typedef typename tree_type::reverse_iterator  const_reverse_iterator;

        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;

    private:
        tree_type _tree;

    public:
        explicit set (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) : _tree(comp, allocator_type(alloc)) {}

        template<class InputIterator>
        set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            : _tree(comp, allocator_type(alloc)) { _tree.insert(first, last); }

        set (const set& x) : _tree(x._tree) {}

        ~set() {
            clear();
        }

        set& operator=(const set& other) {
            _tree = other._tree;
            return *this;
        }

        iterator begin() const {
            return _tree.begin();
        }

        iterator end() const {
            return _tree.end();
        }

        reverse_iterator rbegin() const {
            return _tree.rbegin();
        }

        reverse_iterator rend() const {
            return _tree.rend();
        }

        bool empty() const {
            return _tree.empty();
        }

        size_type size() const {
            return _tree.size();
        }

        size_type max_size() const {
            return _tree.max_size();
        }

        ft::pair<iterator, bool> insert(const value_type& value) {
            return _tree.insert(value);
        }

        iterator insert(iterator hint, const value_type& value) {
            return _tree.insert(hint, value);
        }

        template<class InputIt>
        void insert(InputIt first, InputIt last) {
            _tree.insert(first, last);
        }

        void erase(iterator pos) {
            _tree.erase(pos);
        }

        void erase(iterator first, iterator last) {
            _tree.erase(first, last);
        }

        size_type erase(const key_type& key) {
            return _tree.erase(key);
        }

        void swap(set &other) {
            set tmp = *this;
            *this = other;
            other = tmp;
        }

        void clear() {
            _tree.clear();
        }

        key_compare key_comp() const {
            return _tree.key_comp();
        }

        value_compare value_comp() const {
            return value_compare(key_comp());
        }

        iterator find(const key_type& key) const {
            return _tree.find(key);
        }

        size_type count(const key_type& key) {
            return _tree.count(key);
        }

        iterator lower_bound(const key_type& key) const {
            return _tree.lower_bound(key);
        }

        iterator upper_bound(const key_type& key) const {
            return _tree.upper_bound(key);
        }

        ft::pair<iterator, iterator> equal_range(const key_type& key) const {
            return _tree.equal_range(key);
        }

        allocator_type get_allocator() const {
            return allocator_type(_tree.get_allocator());
        }
    };

    template<class T, class Compare, class Alloc>
    bool operator==(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin()) and lhs.size() == rhs.size();
    }

    template<class T, class Compare, class Alloc>
    bool operator!=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template<class T, class Compare, class Alloc>
    bool operator<(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class T, class Compare, class Alloc>
    bool operator<=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
        return lhs < rhs or lhs == rhs;
    }

    template<class T, class Compare, class Alloc>
    bool operator>(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
        return rhs < lhs;
    }

    template<class T, class Compare, class Alloc>
    bool operator>=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
        return rhs <= lhs;
    }

    template<class T, class Compare, class Alloc>
    void swap(set<T, Compare, Alloc>& lhs, set<T, Compare, Alloc>& rhs) {
        lhs.swap(rhs);
    }

}

#endif