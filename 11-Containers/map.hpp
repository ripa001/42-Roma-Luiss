#pragma once

#include "vector.hpp"
#include "utils.hpp"
#include "RBTree.hpp"

namespace ft {
	
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map : public RBTree<ft::pair<const Key, T>, Node<ft::pair<const Key, T> >,  RBIterator<ft::pair<const Key, T>, Compare, Node<ft::pair<const Key, T> > >, RBIteratorConst<ft::pair<const Key, T>, Compare, Node<ft::pair<const Key, T> > >, Compare, Allocator> {
		public:
			typedef Key																	key_type;
			typedef	T																	mapped_type;
			typedef ft::pair<const Key, T>												value_type;
			typedef typename ft::pair<const Key, T>										Pair;
			typedef typename ft::NodeRB2<Pair>											originalNode;
			typedef typename Allocator::template rebind<Node<value_type> >::other		allocator_type;
			typedef typename allocator_type::reference									reference;
			typedef typename allocator_type::const_reference							const_reference;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;
			typedef typename allocator_type::size_type									size_type;
			typedef RBIterator<value_type, Compare, Node<value_type> >					iterator;
			typedef RBIteratorConst<value_type, Compare, Node<value_type> >				const_iterator;
			typedef Compare						

			map(void) {};
			explicit map(const Compare& comp, const Allocator& alloc = Allocator())	{
				(void)comp;
				(void)alloc;
			};
			map(inputIterator first, inputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {
				this->insert(first, last);
				(void)comp;
				(void)alloc;
			};
			map(const map& x) {
				this->insert(x.begin(), x.end());
			};
			map& operator=(const map& x) {
				if (this == &x)
					return (*this);
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			};

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