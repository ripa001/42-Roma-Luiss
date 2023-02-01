#pragma once

#include <algorithm>
#include "utils.hpp"
#include "vector.hpp"
#include "RBTree.hpp"
#include "iterator.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map {
		public:
			class 												value_compare; // defined on line 71

			typedef Key                                         			key_type;
			typedef	T			 											mapped_type;
            typedef ft::pair< const Key, T >     							value_type;
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
			typedef typename rbtree::iterator					iterator;
			typedef typename rbtree::const_iterator				const_iterator;
			typedef ft::reverse_iterator< iterator >						reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >					const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			class value_compare
			{
				friend class map;
				protected:
					key_compare		comp;
					value_compare 	(key_compare c) : comp(c) {}  // constructed with map's comparison object
					
				public:
					typedef bool 			result_type;
					typedef value_type 		first_argument_type;
					typedef value_type 		second_argument_type;
					bool 	operator() ( const value_type& x, const value_type& y ) const 				{ 		return comp(x.first, y.first);			};
			};

			// Constructors
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _compare(comp), _alloc(alloc) {};
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _compare(comp), _alloc(alloc) {
				insert(first, last);
			};
			
			map (const map& x) : _tree(x._tree), _compare(x._compare), _alloc(x._alloc) {};
			~map() {};
			
			iterator 			begin()									{	return	_tree.begin();		};
			const_iterator		begin() const							{	return	_tree.begin();		};
			iterator 			end()									{	return	_tree.end();		};
			const_iterator 		end() const								{	return	_tree.end();		};
			reverse_iterator		rbegin()							{	return	_tree.rbegin();		};
			const_reverse_iterator 	rbegin() const						{	return	_tree.rbegin();		};
			reverse_iterator 		rend()								{	return	_tree.rend();		};
			const_reverse_iterator 	rend() const						{	return	_tree.rend();		};

			size_type 		size( void ) const							{	return	_tree.size();		};
			size_type 		max_size() const							{	return	_tree.max_size();	};

			void clear() { _tree.clear(); };
			void swap(map& x) { _tree.swap(x._tree); };
			map& operator=(const map& x) { _tree = x._tree; return *this; };

			void insert (iterator position, const value_type& val) { _tree.insert(position, val); };

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) { _tree.insert(first, last); };

			ft::pair<iterator,bool> insert (const value_type& val) { return _tree.insert(val); };

			// class value_compare : public std::binary_function<value_type, value_type, bool> {
			// 	friend class map;
			// 	protected:
			// 		Compare comp;
			// 		value_compare(Compare c) : comp(c) {}
			// 	public:
			// 		typedef bool result_type;
			// 		typedef value_type first_argument_type;
			// 		typedef value_type second_argument_type;
			// 		bool operator()(const value_type& x, const value_type& y) const {
			// 			return comp(x.first, y.first);
			// 		}
			// };


	};
	template <class T, class Alloc>
	bool	operator !=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{	return !(l == r);	}

	template <class T, class Alloc>
	bool	operator >   ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{	return r < l;		}

	template <class T, class Alloc>
	bool	operator <=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{	return !(l > r);	}


};