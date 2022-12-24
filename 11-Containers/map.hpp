#pragma once

#include "vector.hpp"
#include "utils.hpp"

namespace ft {
		template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
		class map {
			public:
				typedef key Key;
				typedef T mapped_type;
				typedef value_type ft::pair<const Key, T>;
				typedef key_compare Compare;
				typedef allocator_type Alloc;
				// typedef reference value_type&;
				// typedef const_reference const value_type&;
				// typedef pointer value_type*;
				// typedef const_pointer const value_type*;
				// typedef iterator map_iterator;
				// typedef const_iterator const_map_iterator;
				// typedef reverse_iterator reverse_map_iterator;
				// typedef const_reverse_iterator const_reverse_map_iterator;

				explicit map(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
					: _comp(comp), _alloc(alloc) {};

				// template <class InputIterator>
				// map(InputIterator first, InputIterator last,
				// 	const key_compare& comp = key_compare(),
				// 	const allocator_type& alloc = allocator_type())
				// 	: _comp(comp), _alloc(alloc) {
				// 		assign(first, last);
				// 	};
				
				// map(const map& x) : _comp(x._comp), _alloc(x._alloc) {
				// 	assign(x.begin(), x.end());
				// };

		private:
			allocator_type	_alloc;
			rb_tree			_tree;
			key_compare	_comp;
		};


}