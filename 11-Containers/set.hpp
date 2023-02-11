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

			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _compare(comp), _alloc(alloc) {};

			template <class InputIterator>
			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _compare(comp), _alloc(alloc) {
				_tree.insert(first, last);
			};

			set (const set& x) : _tree(x._tree), _compare(x._compare), _alloc(x._alloc) {};

			set &operator=(const set &x) {
				_tree = x._tree;
				return *this;
			};
			~set() {};

			class value_compare
			{
				friend class set;
				protected:
					key_compare		comp;
					value_compare 	(key_compare c) : comp(c) {}  // constructed with map's comparison object
					
				public:
					typedef bool 			result_type;
					typedef value_type 		first_argument_type;
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

			ft::pair<iterator, bool> insert (const value_type& val) { return _tree.insert(val); };
			iterator insert (iterator position, const value_type& val) { return _tree.insert(position, val); };

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) { _tree.insert(first, last); };

			iterator erase (iterator position) { return _tree.erase(position); };
			size_type erase (const key_type& k) { return _tree.erase(k); };
			void  erase (iterator first, iterator last) { _tree.erase(first, last); };
			
			void swap (set& x) { _tree.swap(x._tree); };
			size_type size() const { return _tree.size(); };
			size_type max_size() const { return _tree.max_size(); };
	};
}