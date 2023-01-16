#pragma once

#include <algorithm>
#include "utils.hpp"
#include "vector.hpp"
#include "RBTree.hpp"
#include "iterator.hpp"

namespace ft {
	
	template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
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
			typedef Compare																key_compare;

			map(void) {};
			explicit map(const Compare& comp, const Allocator& alloc = Allocator())	{
				(void)comp;
				(void)alloc;
			};
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {
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

			iterator	find(const Key& key) {
				pointer					node = this->_root;
				ft::pair<key_type, mapped_type>		pair(key, mapped_type());

				if (!node || node == this->_sentinel)
					return (iterator(this->_sentinel, this->_sentinel));
				return (this->findPointer(key));
			};

			iterator	findPointer(pointer& start, ft::pair<const Key, T> const & val) const
			{
				if (!start || start->color == NIL)
					return (iterator(this->_sentinel, this->_sentinel));
				if (this->_comp(val.first_one, start->data.first_one) && start->data.first_one != val.first_one)
					return (findPointer(start->child[LEFT], val));
				else if (this->_comp(start->data.first_one, val.first_one) && start->data.first_one != val.first_one)
					return (findPointer(start->child[RIGHT], val));
				else
					return (iterator(start, this->_sentinel));
			}
			

			ft::pair<iterator, bool> insertNode(pointer &start, pointer &node, pointer& parent, int flag) {
				ft::pair<iterator, bool>	ret;
				
				if (!start || start == this->_sentinel)
				{
					node->parent = parent;
					if (this->_comp(node->data.first, parent->data.first))
						parent->child[LEFT] = node;
					else
						parent->child[RIGHT] = node;
					start = node;
					if (flag)
						this->_size++;
					this->balanceInsert(start);
					ret.first = iterator(node, this->_sentinel);
					ret.second = true;
					return (ret);
				}
				if (this->_comp(node->data.first, start->data.first))
					return (insertNode(start->child[LEFT], node, start, flag));
				else if (this->_comp(start->data.first, node->data.first))
					return (insertNode(start->child[RIGHT], node, start, flag));
				ret.first = find(node->data.first);
				delete node;
				ret.second = false;
				return (ret);
			}

			ft::pair<iterator, bool>	insert(ft::pair<const Key, T> const & val) {
				ft::pair<iterator, bool>	ret;
				pointer node = new Node<value_type>(val);

				node->color = RED;
				
				node->parent = this->_sentinel;
				node->child[LEFT] = this->_sentinel;
				node->child[RIGHT] = this->_sentinel;

				if (!this->_size)
				{
					this->_root = node;
					this->_sentinel->parent = node;
					node->color = BLACK;
					this->_size++;
					ret.first = iterator(node, this->_sentinel);
					ret.second = true;
					return (ret);
				}
				else
				{
					
				}
	
			};


			// void	erase(iterator pos)
			// {
			// 	this->erase_deep(*pos);
			// }

			// void	erase(iterator first, iterator last)
			// {
			// 	while (first != last)
			// 		this->erase_deep(*first++);
			// }

			// size_type	erase(const key_type& key)
			// {
			// 	ft::pair<key_type, mapped_type>	tmp(key, mapped_type());
				
			// 	if (erase_deep(tmp) != iterator(NULL, this->_sentinel))
			// 		return (1);
			// 	return (0);
			// }

			// void	clear()
			// {
			// 	while (this->size())
			// 		erase(this->min());
			// }

			~map() {};

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

		};


}