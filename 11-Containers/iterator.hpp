#pragma once

#include <cstddef>
#include "asserts.hpp"

namespace ft {

	template <class iterator>
	struct iterator_traits {
		typedef typename iterator::iterator_category	iterator_category;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::pointer				pointer;
		typedef typename iterator::reference			reference;
	};

	template <class T>
	struct iterator_traits<T *> {
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T *								pointer;
		typedef T &								reference;
	};


	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class T>
	struct forward_iterator : ft::iterator<ft::forward_iterator_tag, T>{
		typedef typename std::forward_iterator_tag										iterator_category;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::value_type			value_type;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::pointer				pointer;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::reference			reference;
		typedef T																		iterator_type;
	};		

	template <class T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T> {
		public:
			typedef std::random_access_iterator_tag												iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef std::ptrdiff_t																difference_type;
			typedef size_t																		size_type;

			random_access_iterator() : _pointed(NULL), _value(value_type()) {}
			random_access_iterator(pointer p) : _pointed(p), _value(value_type()) {}
			random_access_iterator(const random_access_iterator &other) : _value(value_type()) { this->_pointed = other.pointed(); }
			random_access_iterator &operator=(const random_access_iterator &other) {
				if (this != &other)
					this->_pointed = other.pointed();
				return *this;
			}
			pointer 				pointed() const { return this->_pointed; }
			pointer					operator->() const { return this->_pointed; }
			reference				operator*() const { return *this->_pointed; }
			random_access_iterator	operator+(difference_type n) const { return random_access_iterator(this->_pointed + n); }
			random_access_iterator	operator-(difference_type n) const { return random_access_iterator(this->_pointed - n); }
			random_access_iterator	&operator++() { this->_pointed++; return *this; }
			random_access_iterator	&operator--() { this->_pointed--; return *this; }
			random_access_iterator	operator++(int) { random_access_iterator tmp(*this); this->_pointed++; return tmp; }
			random_access_iterator	operator--(int) { random_access_iterator tmp(*this); this->_pointed--; return tmp; }
			random_access_iterator	&operator+=(difference_type n) { this->_pointed += n; return *this; }
			random_access_iterator	&operator-=(difference_type n) { this->_pointed -= n; return *this; }
			reference				operator[](difference_type n) const { return this->_pointed[n]; }
			bool					operator==(const random_access_iterator &other) const { return this->_pointed == other.pointed(); }
			bool					operator!=(const random_access_iterator &other) const { return this->_pointed != other.pointed(); }
			bool					operator<(const random_access_iterator &other) const { return this->_pointed < other.pointed(); }
			bool					operator<=(const random_access_iterator &other) const { return this->_pointed <= other.pointed(); }
			bool					operator>(const random_access_iterator &other) const { return this->_pointed > other.pointed(); }
			bool					operator>=(const random_access_iterator &other) const { return this->_pointed >= other.pointed(); }
			difference_type			operator-(const random_access_iterator &other) const { return this->_pointed - other.pointed(); }
			difference_type			operator+(const random_access_iterator &other) const { return this->_pointed + other.pointed(); }
			virtual	~random_access_iterator() {}
		private:
			pointer _pointed;
			T		_value;
	};


	template <typename T, class Compare, class NodeType>
	class RBIterator {
		public:
			typedef T								value_type;
			typedef T								&reference;
			typedef T								*pointer;
			typedef std::ptrdiff_t					difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef NodeType*						node_type;

			node_type	_node;
			node_type	_sentinel;
			node_type	_root;
			node_type	_begin;
			node_type	_end;
			Compare		_comp;

			RBIterator() : _node(NULL), _sentinel(NULL), _comp(Compare()) {};

			RBIterator(NodeType* start) : 
				_node(start),
				_sentinel(findSentinel()),
				_root(findRoot()),
				_begin(min(_root)),
				_end(max(_root)),
				_comp(Compare()) {};
			RBIterator(node_type node, node_type _sentinel, node_type root, node_type begin, node_type end, Compare comp) : _node(node), _sentinel(_sentinel), _root(root), _begin(begin), _end(end), _comp(comp) {};
		private:

			node_type	min(){
				node_type*	node = &_root;

				if (!(*node) || (*node) == _sentinel)
					return (_sentinel);

				while ((*node)->child[0] && (*node)->child[0] != _sentinel)
					node = &(*node)->child[0];
				return (*node);
			}
			
			node_type	min(node_type& node) {
				node_type*	tmp = &node;

				if (!(*tmp) || !tmp)
					return (NULL);

				while (*tmp != _sentinel && (*tmp)->child[0] != _sentinel)
					tmp = &((*tmp)->child[0]);
				return (*tmp);
			}
			
			node_type	max() {
				node_type*	node = &_root;

				if (!node || !(*node) || (*node) == _sentinel)
					return (_sentinel);

				while ((*node)->child[1] && (*node)->child[1] != _sentinel)
					node = &(*node)->child[1];
				return (*node);
			}
			
			node_type	max(node_type& node) {
				node_type*	tmp = &node;

				if (!tmp || !(*tmp))
					return (NULL);

				while (*tmp != _sentinel && (*tmp)->child[1] != _sentinel)
					tmp = &((*tmp)->child[1]);
				return (*tmp);
			}

			node_type	findSentinel() {
				node_type tmp = _node;
				if (!tmp)
					return NULL;
				while (tmp->color != 2)
					tmp = tmp->CHILD[1];
				return tmp;
			}

			node_type	findRoot() {
				node_type tmp = _node;
				if (!tmp)
					return NULL;
				while (tmp != _sentinel && tmp->parent != _sentinel)
					tmp = tmp->parent;
				return tmp;
			}
			
			node_type	getSuccessor(node_type & node) {
				node_type*	tmp = &node;

				if (node == _sentinel || \
					node == max(_sentinel->parent) || \
					(node->parent == _sentinel && node->child[0] == _sentinel && node->child[1] == _sentinel))
					return (_sentinel);
				else if ((*tmp)->child[1] != _sentinel)
					return (min((*tmp)->child[1]));
				else
				{
					while ((*tmp)->parent != _sentinel)
					{
						if ((*tmp)->parent->child[0] == *tmp)
						{
							tmp = &(*tmp)->parent;
							break ;
						}
						tmp = &(*tmp)->parent;
					}
					return (*tmp);
				}
			}
	};

	template <typename T, class Compare, class NodeType>
	class RBIteratorConst
	{
		public:
			typedef T							value_type;
			typedef const T&					reference;
			typedef const T*					pointer;
			typedef NodeType*					node_type;
			typedef std::ptrdiff_t				difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;

			node_type	_node;
			node_type	_sentinel;
			node_type	_root;
			node_type	_begin;
			node_type	_end;
			Compare		_comp;

			RBIteratorConst()
			{
				_node = NULL;
				_sentinel = NULL;
				_comp = Compare();
			};
			
			RBIteratorConst(NodeType* start) : 
				_node(start),
				_sentinel(findSentinel()),
				_root(findRoot()),
				_begin(min(_root)),
				_end(max(_root)),
				_comp(Compare())
			{};
			
			RBIteratorConst(NodeType* start, NodeType* endPtr) :
				_node(start),
				_sentinel(endPtr),
				_root(findRoot()),
				_begin(min(_root)),
				_end(max(_root)),
				_comp(Compare())
			{};
			
			RBIteratorConst(RBIteratorConst const & src) :
				_node(src._node),
				_sentinel(src._sentinel),
				_root(src._root),
				_begin(src._begin),
				_end(src._end)
			{};
			
			template <class InputIt>
			RBIteratorConst(InputIt const & src)
			{
				if (src._node == NULL)
					return ;
				_node = src._node;
				_sentinel = src._sentinel;
				_root = src.root;
				_begin = src._begin;
				_end = src._end;
			};
			
			RBIteratorConst&	operator=(RBIteratorConst const & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_node = rhs._node;
				this->_sentinel = rhs._sentinel;
				this->_root = rhs._root;
				this->_begin = rhs._begin;
				this->_end = rhs._end;
				return (*this);
			}
			
			template <class InputIt>
			RBIteratorConst&	operator=(InputIt const & rhs)
			{
				this->_node = rhs._node;
				this->_sentinel = rhs._sentinel;
				this->_root = rhs._root;
				this->_begin = rhs._begin;
				this->_end = rhs._end;
				return (*this);
			}
			
			~RBIteratorConst() {};

			
			// Overloads

			reference			operator*() const { return (this->_node->data); }
			pointer				operator->() const { return &(this->_node->data); }
			bool				operator==(RBIteratorConst const & rhs) { return ((this->_node == rhs._node) ? true : false); }
			
		private:
			node_type	min()
			{
				node_type*	node = &_root;

				if (!(*node) || (*node) == _sentinel)
					return (_sentinel);

				while ((*node)->child[0] && (*node)->child[0] != _sentinel)
					node = &(*node)->child[0];
				return (*node);
			}
			
			node_type	min(node_type& _node)
			{
				node_type*	tmp = &_node;

				if (!(*tmp) || !tmp)
					return (NULL);

				while (*tmp != _sentinel && (*tmp)->child[0] != _sentinel)
					tmp = &((*tmp)->child[0]);
				return (*tmp);
			}
			
			node_type	max()
			{
				node_type*	node = &_root;

				if (!node || !(*node) || (*node) == _sentinel)
					return (_sentinel);

				while ((*node)->child[1] && (*node)->child[1] != _sentinel)
					node = &(*node)->child[1];
				return (*node);
			}
			
			node_type	max(node_type& _node)
			{
				node_type*	tmp = &_node;

				if (!tmp || !(*tmp))
					return (NULL);

				while (*tmp != _sentinel && (*tmp)->child[1] != _sentinel)
					tmp = &((*tmp)->child[1]);
				return (*tmp);
			}
			
			node_type	findSentinel()
			{
				node_type*	tmp = &this->_node;
				
				if (!(*tmp) || !tmp)
					return (NULL);

				while (tmp && (*tmp)->color != 2)
					tmp = &((*tmp)->child[0]);
				return (*tmp);
			}
			
			node_type	findRoot()
			{
				node_type*	tmp = &this->_node;
				while (tmp && *tmp && *tmp != _sentinel && (*tmp)->parent != _sentinel)
					tmp = &((*tmp)->parent);
				return (*tmp);
			}

			node_type	getSuccessor(node_type & _node)
			{
				node_type*	tmp = &_node;
			
				if (_node == _sentinel)
					return (_sentinel);
				if (_node == max(_sentinel->parent))
					return (_sentinel);
				if (_node->parent == _sentinel && _node->child[0] == _sentinel && _node->child[1] == _sentinel)
					return (_sentinel);
				if ((*tmp)->child[1] != _sentinel)
					return (min((*tmp)->child[1]));
				else
				{
					while ((*tmp)->parent != _sentinel)
					{
						if ((*tmp)->parent->child[0] == *tmp)
						{
							tmp = &(*tmp)->parent;
							break ;
						}
						tmp = &(*tmp)->parent;
					}
					return (*tmp);
				}
			}

			node_type	getPredecessor(node_type & _node)
			{
				node_type*	tmp = &_node;
				
				if (_node == _sentinel)
					return (max(_node->parent));
				if (_node == min(_sentinel->parent))
					return (_sentinel);
				if ((*tmp)->child[0] != _sentinel)
					return (max((*tmp)->child[0]));
				else
				{
					while ((*tmp)->parent != _sentinel)
					{
						if ((*tmp)->parent->child[1] == *tmp)
						{
							tmp = &(*tmp)->parent;
							break ;
						}
						tmp = &(*tmp)->parent;
					}
					return (*tmp);
				}
			}
	};
			// create RBIteratorConst class RBIterator class making reference and pointer const types and copy constructor and assignment operator

	// template <class T, class Compare, class NodeType>
	// class RBIteratorConst : public RBIterator<T, Compare, NodeType> {
	// 	public:
	// 		typedef const T&	reference;
	// 		typedef const T*	pointer;
	// 		typedef NodeType*	node_type;


	// 		RBIteratorConst() : RBIterator() {};
	// 		// RBIteratorConst(NodeType* start) : RBIterator(start) {};
	// 		// RBIteratorConst(node_type _node, node_type _sentinel, node_type root, node_type begin, node_type end, Compare comp) : RBIterator(_node, _sentinel, root, begin, end, comp) {};
	// 		// RBIteratorConst(const RBIterator& other) : RBIterator(other) {};
	// 		RBIteratorConst&	operator=(const RBIterator& other) {
	// 			if (this != &other)
	// 			{
	// 				_node = other._node;
	// 				_sentinel = other._sentinel;
	// 				_root = other._root;
	// 				_begin = other._begin;
	// 				_end = other._end;
	// 				_comp = other._comp;
	// 			}
	// 			return (*this);
	// 		};
	// 		~RBIteratorConst() {};

	// 		reference	operator*() const {
	// 			return (_node->data);
	// 		};
	// 		pointer		operator->() const {
	// 			return (&(_node->data));
	// 		};
	// };




	// template <class T, class Compare>
	// class RBIteratorConst : public RBIterator {
	// 	public:
	// 		typedef const T&	reference;
	// 		typedef const T*	pointer;

	// 		RBIteratorConst() : RBIterator() {};
	// 		RBIteratorConst(NodeType* start) : RBIterator(start) {};
	// 		RBIteratorConst(node_type node, node_type _sentinel, node_type root, node_type begin, node_type end, Compare comp) : RBIterator(node, _sentinel, root, begin, end, comp) {};
	// 		RBIteratorConst(const RBIterator& other) : RBIterator(other) {};
	// 		RBIteratorConst&	operator=(const RBIterator& other) {
	// 			if (this != &other)
	// 			{
	// 				_node = other._node;
	// 				_sentinel = other._sentinel;
	// 				_root = other._root;
	// 				_begin = other._begin;
	// 				_end = other._end;
	// 				_comp = other._comp;
	// 			}
	// 			return (*this);
	// 		};
	// 		~RBIteratorConst() {};

	// 		reference	operator*() const { return (_node->data); };
	// 		pointer		operator->() const { return (&(_node->data)); };
	// };


	template <class InputIterator>
	class reverse_iterator : ft::iterator<typename InputIterator::iterator_category, typename InputIterator::value_type> {
		public:
			typedef typename InputIterator::iterator_category	iterator_category;
			typedef typename InputIterator::value_type			value_type;
			typedef typename InputIterator::difference_type		difference_type;
			typedef typename InputIterator::pointer				pointer;
			typedef typename InputIterator::reference			reference;
			typedef InputIterator								iterator_type;
			typedef reverse_iterator<iterator_type>				iterator;

			reverse_iterator() : _pointed(NULL), _value(value_type()) {}
			reverse_iterator(pointer p) : _pointed(p), _value(value_type()) {}
			reverse_iterator(const reverse_iterator &other) : _value(value_type()) { this->_pointed = other.pointed(); }
			reverse_iterator &operator=(const reverse_iterator &other) {
				if (this != &other)
					this->_pointed = other.pointed();
				return *this;
			}
			pointer 				pointed() const { return this->_pointed; }
			pointer					operator->() const { return this->_pointed; }
			reference				operator*() const { return *this->_pointed; }
			reverse_iterator		operator+(difference_type n) const { return reverse_iterator(this->_pointed + n); }
			reverse_iterator		operator-(difference_type n) const { return reverse_iterator(this->_pointed - n); }
			reverse_iterator		&operator++() { this->_pointed++; return *this; }
			reverse_iterator		&operator--() { this->_pointed--; return *this; }
			reverse_iterator		operator++(int) { reverse_iterator tmp(*this); this->_pointed++; return tmp; }
			reverse_iterator		operator--(int) { reverse_iterator tmp(*this); this->_pointed--; return tmp; }
			reverse_iterator		&operator+=(difference_type n) { this->_pointed += n; return *this; }
			reverse_iterator		&operator-=(difference_type n) { this->_pointed -= n; return *this; }
			reference				operator[](difference_type n) const { return this->_pointed[n]; }
			bool					operator==(const reverse_iterator &other) const { return this->_pointed == other.pointed(); }
			bool					operator!=(const reverse_iterator &other) const { return this->_pointed != other.pointed(); }
			bool					operator<(const reverse_iterator &other) const { return this->_pointed < other.pointed(); }		
			bool					operator<=(const reverse_iterator &other) const { return this->_pointed <= other.pointed(); }
			bool					operator>(const reverse_iterator &other) const { return this->_pointed > other.pointed(); }
			bool					operator>=(const reverse_iterator &other) const { return this->_pointed >= other.pointed(); }
			difference_type			operator-(const reverse_iterator &other) const { return this->_pointed - other.pointed(); }
			difference_type			operator+(const reverse_iterator &other) const { return this->_pointed + other.pointed(); }
			virtual	~reverse_iterator() {}
		private:
			pointer			_pointed;
			InputIterator	_value;
	};

	template <class InputIterator1, class InputIterator2>
	typename ft::iterator_traits<InputIterator1>::difference_type
	distance(InputIterator1 first, InputIterator2 last)
	{
		typename ft::iterator_traits<InputIterator1>::difference_type ret = 0;

		while (first++ != last)
			ret++;
		return (ret);
	}
};
