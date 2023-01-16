#pragma once

#include <memory>
#include <utility>
#include <iostream>
#include <limits>
#include "utils.hpp"

namespace ft {

	enum node_color
	{
		YELLOW,
		BLACK,
		NIL
	};

	enum branch
	{
		LEFT,
		RIGHT
	};

	template <class T>
	struct Node
	{
		node_color	color;
		Node		*child[2];
		Node		*parent;
		T			data; 

		template <class U, class V>
		Node(ft::pair<U, V> *data) : data(data) {}
	};

	template <class Pair>
	struct NodeRB2 {
		NodeRB2					*parent;
		NodeRB2 				*left;
		NodeRB2 				*right;
		Pair					data;
		int						color;
	};

	template <class Key, class NodeType, class Iterator, class ConstIterator, class Compare=std::less<Key>, class Alloc=std::allocator<Key>>
	class RBTree
	{
		public:
			typedef NodeRB2<Key>											originalNode;
			typedef Key														key_type;
			typedef Key														value_type;

			typedef NodeType												node_type;
			typedef Iterator												iterator;
			typedef ConstIterator											const_iterator;
			// typedef ReverseIterator<iterator>								reverse_iterator;
			// typedef ReverseIterator<ConstIterator>							const_reverse_iterator;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef typename Alloc::template rebind<node_type>::other		allocator_type;
			typedef typename Alloc::template rebind<originalNode>::other	allocator_type2;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer 						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;


			RBTree() :	_root(NULL), _size(0), _alloc(allocator_type()){
				_sentinel = _alloc.allocate(1);
				_sentinel->color = NIL;
				_root = _sentinel;
				_sentinel->parent = _root;
			};

			RBTree(const RBTree &x) : _root(NULL), _size(0), _alloc(allocator_type()){
				*this = x;
			};

			RBTree &operator=(RBTree const &x) {
				if (this != &x) {
					_key_type = x.getAllocator();
					_sentinel = _alloc.allocate(1);
					_sentinel->color = NIL;
					_root = _sentinel;
					_sentinel->parent = _root;
					_size = 0;
					this->insert(x.begin(), x.end());
				}
				return *this;
			};
			allocator_type getAllocator() const {return _alloc;};
			bool empty() const {return ((!this->_size) ? true : false);};
			size_type size() const {return this->_size;};
			size_type max_size() const {return _alloc2.maxSize();};

			iterator				begin(){iterator(min(), _sentinel);};
			const_iterator			begin() const {return const_iterator(min(), _sentinel);};
			iterator				end(){ return iterator(_sentinel, _sentinel);};
			const_iterator			end() const {return const_iterator(_sentinel, _sentinel);};
			// reverse_iterator		rbegin(){return reverse_iterator(end());};
			// reverse_iterator		rend(){return reverse_iterator(begin());};
			// const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());};
			// const_reverse_iterator	rend() const {return const_reverse_iterator(begin());};	

			virtual iterator					findPointer(pointer &start, Key const &val) const = 0;
			// virtual iterator					erase_deep(Key const &val) = 0;
			// virtual ft::pair<iterator, bool>	insert(Key const &val) = 0;
			// virtual ft::pair<iterator, bool>	insertNode(pointer &start, pointer &node, pointer &parent, int flag) = 0;
			// virtual void 						clear() = 0;

			
			pointer	min() const
			{
				const pointer*	node = &_root;

				if (!(*node) || (*node) == _sentinel)
					return (_sentinel);
				while ((*node)->child[LEFT] && (*node)->child[LEFT] != _sentinel)
					node = &(*node)->child[LEFT];
				return (*node);
			}

			pointer	min(pointer const & node) const
			{
				const pointer*	tmp = &node;

				if (!(*tmp) || (*tmp) == _sentinel)
					return (_sentinel);
				while ((*tmp)->child[LEFT] && (*tmp)->child[LEFT] != _sentinel)
					tmp = &(*tmp)->child[LEFT];
				return (*tmp);
			}

			pointer	max() const
			{
				pointer	node = _root;

				if (!node || node == _sentinel)
					return (_sentinel);
				while (node->child[RIGHT] && node->child[RIGHT] != _sentinel)
					node = node->child[RIGHT];
				return (node);
			}

			pointer	max(pointer const & node) const
			{
				pointer	tmp = node;

				if (!node || node == _sentinel)
					return (_sentinel);
				while (tmp->child[RIGHT] != _sentinel)
					tmp = tmp->child[RIGHT];
				return (tmp);
			}

			pointer	getSuccessor(pointer const & node) const
			{
				pointer	tmp = node;
				
				if (node == max())
					return (_sentinel);
				if (tmp->child[RIGHT] != _sentinel)
					return (min(tmp->child[RIGHT]));
				else
				{
					while (tmp->parent != _sentinel)
					{
						if (tmp->parent->child[LEFT] == tmp)
						{
							tmp = tmp->parent;
							break ;
						}
						tmp = tmp->parent;
					}
				}
			}

			pointer getPrecessor(pointer const & node) const
			{
				pointer	tmp = node;

				if (node == min())
					return (_sentinel);
				if (tmp->child[LEFT] != _sentinel)
					return (max(tmp->child[LEFT]));
				else
				{
					while (tmp->parent != _sentinel)
					{
						if (tmp->parent->child[RIGHT] == tmp)
						{
							tmp = tmp->parent;
							break ;
						}
						tmp = tmp->parent;
					}
				}
			}

			~RBTree() {_alloc.deallocate(_sentinel, 1);};

		
		protected:
			key_type		_key_type;
			value_type		_value_type;
			key_compare		_key_compare;
			value_compare	_value_compare;
			pointer			_root;
			pointer			_sentinel;
			size_type		_size;
			allocator_type	_alloc;
			allocator_type2	_alloc2;
			Compare			_comp;

			pointer*	rotateRight(pointer & node)
			{
				pointer		toHandle;
				pointer*	tmp = &node;
				pointer*	ret;

				if ((*tmp) && (*tmp)->child[LEFT] != _sentinel && (*tmp)->child[LEFT]->child[RIGHT] != _sentinel)
					toHandle = (*tmp)->child[LEFT]->child[RIGHT];
				else
					toHandle = NULL;
				if ((*tmp) == _root)
				{
					_root = (*tmp)->child[LEFT];
					_sentinel->parent = _root;
					(*tmp)->child[LEFT]->parent = _sentinel;
				}
				else
				{
					(*tmp)->child[LEFT]->parent = (*tmp)->parent;
					if ((*tmp)->parent->child[RIGHT] == *tmp)
						(*tmp)->parent->child[RIGHT] = (*tmp)->child[LEFT];
					else
						(*tmp)->parent->child[LEFT] = (*tmp)->child[LEFT];
				}
				(*tmp)->parent = (*tmp)->child[LEFT];
				(*tmp)->child[LEFT]->child[RIGHT] = (*tmp);
				(*tmp)->child[LEFT] = _sentinel;
				if (toHandle)
					insertNode((*tmp), toHandle, (*tmp), 0);
				ret = &(*tmp)->child[RIGHT];
				return (ret);
			}

			void	balanceInsert(pointer & node)
			{
				pointer*	tmp = &node;
				pointer		parent = node->parent;
				pointer		grandParent;
				pointer		uncle;

				while (1 && *tmp && *tmp != _sentinel)
				{
					parent = (*tmp)->parent;
					getRelatives(parent, grandParent, uncle);
					if (!parent || parent == _sentinel)
					{
						(*tmp)->color = BLACK;
						break ;
					}
					else if (parent->color == BLACK)
						break ;
					else if (uncle && (*tmp)->color == RED && parent->color == RED && uncle->color == RED)
					{
						parent->color = BLACK;
						uncle->color = BLACK;
						grandParent->color = RED;
						tmp = &(*tmp)->parent->parent;
					}
					else if ((*tmp)->color == RED && parent->color == RED)
					{
						if (parent->child[RIGHT] == (*tmp) && grandParent->child[LEFT] == parent)
							tmp = rotateLeft(parent);
						else if (parent->child[LEFT] == (*tmp) && grandParent->child[RIGHT] == parent)
							tmp = rotateRight(parent);
						else if (parent->child[LEFT] == (*tmp) && grandParent->child[LEFT] == parent)
						{
							parent->color = BLACK;
							grandParent->color = RED;
							rotateRight(grandParent);
							break ;
						}
						else if (parent->child[RIGHT] == (*tmp) && grandParent->child[RIGHT] == parent)
						{
							parent->color = BLACK;
							grandParent->color = RED;
							rotateLeft(grandParent);
							break ;
						}
					}
					else
						break ;
				}
			}

			void	getRelatives2(pointer & node, pointer & sibling, pointer & leftNephew, pointer & rightNephew)
			{
				if (node->parent->child[LEFT] != _sentinel && node->parent->color != SENTINEL && node->parent->child[LEFT] == node && node->parent->child[RIGHT] && node->parent->child[RIGHT] != _sentinel)
					sibling = node->parent->child[RIGHT];
				else if (node->parent->child[RIGHT] != _sentinel && node->parent->color != SENTINEL && node->parent->child[LEFT] && node->parent->child[LEFT] != _sentinel)
					sibling = node->parent->child[LEFT];
				else
				{
					sibling = NULL;
					leftNephew = NULL;
					rightNephew = NULL;
					return ;
				}
				if (sibling && sibling->child[LEFT] && sibling->child[LEFT] != _sentinel)
					leftNephew = sibling->child[LEFT];
				else
					leftNephew = NULL;
				if (sibling && sibling->child[RIGHT] && sibling->child[RIGHT] != _sentinel)
					rightNephew = sibling->child[RIGHT];
				else
					rightNephew = NULL;
			}

			void	getRelatives(pointer & parent, pointer & grandParent, pointer & uncle)
			{
				if (parent != _sentinel)
					grandParent = parent->parent;
				else
					grandParent = NULL;
				if (grandParent != _sentinel && grandParent)
				{
					if (grandParent->child[LEFT] == parent && grandParent->child[RIGHT] != _sentinel)
						uncle = grandParent->child[RIGHT];
					else if (grandParent->child[RIGHT] == parent && grandParent->child[LEFT] != _sentinel)
						uncle = grandParent->child[LEFT];
					else
						uncle = NULL;
				}
				else
					uncle = NULL;
			}

			pointer	getSibling(pointer & node)
			{
				if (node->parent == _sentinel)
					return (NULL);
				if (node->parent->child[LEFT] != _sentinel && node->parent->child[LEFT] == node)
					return (node->parent->child[RIGHT]);
				else if (node->parent->child[RIGHT] != _sentinel && node->parent->child[RIGHT] == node)
					return (node->parent->child[LEFT]);
				return (NULL);
			}
	};
}