#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include "utils.hpp"
#include "iterator.hpp"
#include "RBTree.hpp"

namespace	ft {
	template <class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set {
		public:

			class 															value_compare;
			typedef Key                                         			key_type;
			typedef Key														value_type;
			typedef Compare                                     			key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference          			reference;
			typedef typename allocator_type::const_reference   				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef size_t													size_type;
			typedef node< value_type >										treeNode;

		private:
			typedef RBTree<value_type, value_compare, allocator_type>		rbtree;
			rbtree															_tree;
			key_compare														_compare;
			allocator_type													_alloc;
			
		public:
			typedef typename rbtree::iterator								iterator;
			typedef typename rbtree::const_iterator							const_iterator;
			typedef ft::reverse_iterator< iterator >						reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >					const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			// treeRBIterator<const int> const_iterator;
			// treeRBIterator<int> iterator(const_iterator.begin(), const_iterator.end());
			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _compare(comp), _alloc(alloc) {};
			
			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _compare(comp) {
				insert(first, last);
			};
			// explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _compare(comp), _alloc(alloc) {};

			// template <class InputIterator>
			// set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _compare(comp), _alloc(alloc) {
			// 	_tree.insert(first, last);
			// };

			set (const set& x) : _tree(x._tree), _compare(x._compare), _alloc(x._alloc) {};

			set &operator=(const set &x) {
				if (this == &x)
					return (*this);
				_compare = x._compare;
				_tree = x._tree;
				_alloc = x._alloc;
				return (*this);
			};
			~set() {};

			class value_compare
			{
				friend class set;
				protected:
					key_compare		comp;
					value_compare 	(key_compare c) : comp(c) {}  // constructed with set's comparison object
					
				public:
					typedef bool 			result_type;
					typedef value_type 		first_argument_type;
					typedef value_type 		second_argument_type;
					bool 	operator() ( const value_type& x, const value_type& y ) const { return comp(x, y); };
			};

			iterator begin() { return _tree.begin(); };
			const_iterator begin() const { return _tree.begin(); };
			iterator end() { return _tree.end(); };
			const_iterator end() const { return _tree.end(); };
			reverse_iterator rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
			reverse_iterator rend() { return reverse_iterator(begin()); };
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };


			ft::pair<iterator, bool>	insert (const value_type& val) { return _tree.insert(val); };
			iterator					insert (iterator position, const value_type& val) { return _tree.insert(position, val); };
			template <class InputIterator>
			void						insert (InputIterator first, InputIterator last) { _tree.insert(first, last); };

			void		erase(iterator position) { _tree.erase(position.base()); };
			size_type	erase(const key_type& k) { return _tree.erase(k); };
			void		erase(iterator first, iterator last) { _tree.erase(first, last); };
			
			iterator		find (const key_type& k) { return _tree.find(k); };
			const_iterator	find (const key_type& k) const { return _tree.find(k); };

			iterator		lower_bound (const key_type& k) { return _tree.lower_bound(k); };
			const_iterator	lower_bound (const key_type& k) const { return _tree.lower_bound(k); };

			iterator	upper_bound(key_type const & k) { return _tree.upper_bound(k); };
			iterator	upper_bound(key_type const & k) const { return _tree.upper_bound(k); };

			size_type	count(key_type const & k) const	{	return _tree.search(_tree.get_root(), k) ? 1 : 0;	};

			ft::pair< iterator, iterator >				equal_range (const key_type& k) { return (ft::make_pair(lower_bound(k), upper_bound(k))); };
			ft::pair< const_iterator, const_iterator >	equal_range (const key_type& k) const { return (ft::make_pair(lower_bound(k), upper_bound(k))); };
			
			key_compare		key_comp( void ) const { return this->_compare; };
			value_compare	value_comp( void ) const { return value_compare(this->_compare); };

			void		clear( void ) { _tree.clear(_tree.get_root()); };
			void		swap (set& x) { _tree.swap(x._tree); };
			bool		empty( void ) const { return _tree.empty(); };
			size_type	size() const { return _tree.size(); };
			size_type	max_size() const { return _tree.max_size(); };
	};
	template <class T>
	bool	operator == ( const set<T>& l, const set<T>& r ) 
	{
		if (l.size() != r.size())	return false;
		return ft::equal(l.begin(), l.end(), r.begin());
	};

	template <class T>
	bool	operator!=( const set<T>& l, const set<T>& r ) { return !(l == r); }

	template <class T>
	bool	operator<( const set<T>& l, const set<T>& r ) { return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end()); }

	template <class T>
	bool	operator<=( const set<T>& l, const set<T>& r ) { return !(r < l); }

	template <class T>
	bool	operator>( const set<T>& l, const set<T>& r ) { return r < l;	 }

	template <class T>
	bool	operator>=( const set<T>& l, const set<T>& r ) { return !(l < r); }

	template <class T>
	void	swap( set<T>& x, set<T>& y ) { x.swap(y); }
}