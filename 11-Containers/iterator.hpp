#pragma once

#include <cstddef>
#include "asserts.hpp"

namespace ft {
	enum        nodeColor {        RED, BLACK      };

	template < typename T >
	struct node {
	    typedef T           value_type;
	    value_type          value;
		node                *parent, *left, *right;
		bool                color;
	    int                 leaf;

	    node( void )    :   value(0), parent (0), left(0), 
	                        right(0), color( RED )                                              {};
	    node( T const& value, node *parent, int leaf )   :      value(value),
	                                                            parent (parent), left(0), right(0),
	                                                            color( RED ), leaf(leaf)        {};
	    node( node const& t )   :   value(t.value),
	                                parent (t.parent), left(t.left), right(t.right),
	                                color( t.color ), leaf(t.leaf)                              {};
	    node&     operator = ( node const& t )
	    {
	        this->value = t.value;
	        this->parent = t.parent;
	        this->left = t.left;
	        this->right = t.right;
	        this->color = t.color;
	        this->leaf = t.leaf;
	        return *this;
	    }
	    ~node () {};
	};

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

	template< typename U >
	class treeRBIterator {
		public:
			typedef U								value_type;
			typedef U*								pointer;
			typedef const U*						const_pointer;
			typedef U&								reference;
			typedef const U&						const_reference;
			typedef std::ptrdiff_t					difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef node< value_type >				treeNode;
			typedef node< const value_type >		const_treeNode;
			typedef treeRBIterator< U >				iterator;
			typedef treeRBIterator< const U >		const_iterator;

			treeRBIterator( void ) :  _node(NULL) {};
			treeRBIterator( treeNode * current ) : _node(current) {};
			treeRBIterator( treeRBIterator const& t ) : _node(t.base()) {};
			treeRBIterator& 	operator = ( treeRBIterator const& t ) { _node = t.base(); return *this; };
			
			operator		const_iterator() const { return const_iterator(reinterpret_cast<const_treeNode *>(_node)); }
			treeNode		*base( void ) const {	return _node; };
			reference		operator*() { return _node->value; };
			const_reference	operator*() const { return _node->value; };
			pointer			operator->() { return &_node->value; };
			const_pointer	operator->() const {return &_node->value;};

			treeRBIterator&	operator++() {
				if (!_node->leaf)
					return *this;
				if (_node && _node->right && _node->right->leaf)
					for (_node = _node->right; _node->left && _node->left->leaf; _node = _node->left);
				else {
					treeNode *tmp = _node;
					for (_node = _node->parent; _node && _node->right == tmp && _node->leaf; tmp = _node, _node = _node->parent);
				}
				return *this;
			}

			treeRBIterator&	operator--() {
				if (!_node->leaf)
				{
					while (_node->parent->leaf)
						_node = _node->parent;
					while (_node->right->leaf)
						_node = _node->right;
					return *this;
				}
				else if (_node->left && _node->left->leaf)
					for (_node = _node->left; _node->right && _node->right->leaf; _node = _node->right);
				else {
					treeNode *tmp = _node;
					for (_node = _node->parent; _node && _node->left == tmp && _node->leaf; tmp = _node, _node = _node->parent);
				}
			}

			treeRBIterator	operator++(int) {
				treeRBIterator tmp(*this);
				operator++();
				return tmp;
			}

			treeRBIterator	operator--(int) {
				treeRBIterator tmp(*this);
				operator--();
				return tmp;
			}

			bool			operator==(const treeRBIterator &other) const { return this->_node == other._node; }
			bool			operator!=(const treeRBIterator &other) const { return this->_node != other._node; }
			bool 			operator<(const treeRBIterator &other) const { return this->_node < other._node; }
			bool			operator<=(const treeRBIterator &other) const { return this->_node <= other._node; }
			bool			operator>(const treeRBIterator &other) const { return this->_node > other._node; }
			bool			operator>=(const treeRBIterator &other) const { return this->_node >= other._node; }
			
			virtual	~treeRBIterator() {}
			
		private:
			treeNode	*_node;
	};


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
