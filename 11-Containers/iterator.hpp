#pragma once

#include <cstddef>
#include "asserts.hpp"

namespace ft {

	// Iterator traits
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T *>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	// Iterator types
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class T>
	struct forward_iterator : ft::iterator<ft::forward_iterator_tag, T>
	{
		typedef typename std::forward_iterator_tag										iterator_category;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::value_type			value_type;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::pointer				pointer;
		typedef typename ft::iterator<ft::forward_iterator_tag, T>::reference			reference;
		typedef T																		iterator_type;
	};

	template <class T>
	class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename std::bidirectional_iterator_tag									iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
			typedef T																			iterator_type;
			bidirectional_iterator() : _pointed(NULL) {};
			bidirectional_iterator(pointer p) : _pointed(p) {};
			bidirectional_iterator(bidirectional_iterator const & src) : _pointed(src._pointed) {};
			bidirectional_iterator&	operator=(bidirectional_iterator const & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_pointed = rhs._pointed;
				return (*this);
			}
			virtual ~bidirectional_iterator() {};
			reference	operator*() const { return *(this->_pointed); }
			bool		operator==(bidirectional_iterator const & rhs) { return ((this->_pointed == rhs._pointed) ? true : false); }
			bool		operator!=(bidirectional_iterator const & rhs) { return ((this->_pointed != rhs._pointed) ? true : false); }
			bidirectional_iterator&	operator++() { this->_pointed++; return *this; };
			bidirectional_iterator	operator++(int) { bidirectional_iterator tmp(*this); this->_pointed++; return (tmp); };
			bidirectional_iterator&	operator--() { this->_pointed--; return *this; };
			bidirectional_iterator	operator--(int) { bidirectional_iterator tmp(*this); this->_pointed--; return (tmp); };
			template <class InputIt>
			friend size_t			operator-(InputIt const & lhs, InputIt const & rhs);

		private:
			pointer	_pointed;
	};

	template <class T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename std::random_access_iterator_tag									iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef size_t																		size_type;
			typedef T*																			iterator_type;
			random_access_iterator() : _pointed(NULL), _value(value_type()) {};
			random_access_iterator(pointer p) : _pointed(p), _value(value_type()) {};
			random_access_iterator(random_access_iterator const &src) : _value(src._value) { this->_pointed = src.pointed(); }
			random_access_iterator&	operator=(random_access_iterator const & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_pointed = rhs._pointed;
				// this->_value = value_type();
				return (*this);	
			}
			virtual	~random_access_iterator(){};
			reference				operator*() const { return (*_pointed); }
			pointer					operator->() { return &(this->operator*()); }
			random_access_iterator	operator+(difference_type n) const { return (_pointed + n); }
			random_access_iterator	operator-(difference_type n) const { return (_pointed - n); }
			
			random_access_iterator&	operator++()
			{
				_pointed++;
				return (*this);
			}
			random_access_iterator	operator++(int)
			{
				random_access_iterator ret(*this);
				_pointed++;
				return (ret);
			}
			random_access_iterator&	operator--()
			{
				_pointed--;
				return (*this);
			}
			random_access_iterator	operator--(int)
			{
				random_access_iterator ret(*this);
				_pointed--;
				return (ret);
			}
			random_access_iterator&	operator+=(difference_type n)
			{
				_pointed += n;
				return (*this);
			}
			random_access_iterator&	operator-=(difference_type n)
			{
				_pointed -= n;
				return (*this);
			}
			// bool					operator==(random_access_iterator const &rhs)
			// {
			// 	if (this->pointed() == rhs.pointed())
			// 		return true;
			// 	return false;
			// }
			bool					operator!=(random_access_iterator const &rhs)
			{
				if (this->pointed() == rhs.pointed())
					return false;
				return true;
			}
			operator 				random_access_iterator<const T>() const { return (random_access_iterator<const T>(this->_pointed)); }
			pointer 				pointed() const { return this->_pointed; }
			reference 				operator[](difference_type n) { return (*(_pointed + n)); }
			difference_type 		operator-(random_access_iterator const &rhs) const { return (this->pointed() - rhs.pointed()); }
			difference_type 		operator+(random_access_iterator const &rhs) const { return (this->pointed() + rhs.pointed()); }

		private:
			pointer _pointed;
			T		_value;
	};

	template <class T>
	struct contiguous_iterator : ft::iterator<ft::contiguous_iterator_tag, T>
	{
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::value_type			value_type;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::pointer				pointer;
		typedef typename ft::iterator<ft::contiguous_iterator_tag, T>::reference			reference;
		typedef T																			iterator_type;
	};

	template <class InputIterator>
	class reverse_iterator : ft::iterator<typename InputIterator::iterator_category, typename InputIterator::value_type>
	{
		public:
			typedef InputIterator													iterator_type;
			typedef typename ft::iterator_traits<InputIterator>::difference_type	difference_type;
			typedef typename ft::iterator_traits<InputIterator>::value_type			value_type;
			typedef typename ft::iterator_traits<InputIterator>::pointer			pointer;
			typedef typename ft::iterator_traits<InputIterator>::reference			reference;
			typedef typename ft::iterator_traits<InputIterator>::iterator_category	iterator_category;
			reverse_iterator() {};
			explicit reverse_iterator(iterator_type iter) : _base(iter) {};
			reverse_iterator&	operator=(reverse_iterator const & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_base = rhs.base();
				return (*this);
			}
			template <class ReverseIterator>
			reverse_iterator(reverse_iterator<ReverseIterator> const &rev_it) : _base(rev_it.base()){};
			virtual ~reverse_iterator() {};
			iterator_type base() const { return (_base); };
			reference			operator*() const { return (*(_base - 1)); };
			reverse_iterator	operator+(difference_type n) const
			{
				return reverse_iterator(_base - n);
			};
			reverse_iterator	operator-(difference_type n) const
			{
				return reverse_iterator(_base + n);
			};
			reverse_iterator&	operator++()
			{
				_base--;
				return (*this);
			};
			reverse_iterator	operator++(int)
			{
				reverse_iterator ret(*this);
				this->_base--;
				return (ret);
			};
			reverse_iterator&	operator--()
			{
				_base++;
				return (*this);
			};
			reverse_iterator	operator--(int)
			{
				reverse_iterator ret(*this);
				this->_base++;
				return (ret);
			};
			reverse_iterator&	operator+=(difference_type n)
			{
				_base -= n;
				return (*this);
			};
			reverse_iterator&	operator-=(difference_type n)
			{
				_base += n;
				return (*this);
			};
			pointer				operator->() const { return &(*(_base - 1)); };
			reference			operator[](difference_type n) const { return (*(_base - n - 1)); };
			difference_type 	operator+(reverse_iterator const &rhs) const { return (this->base() + rhs.base()); }
			difference_type 	operator-(reverse_iterator const &rhs) const { return (rhs.base() - this->base()); }
		private:
			iterator_type	_base;
	};

	enum	nodeColor { RED, BLACK };

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
	typename ft::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type ret = 0;

		while (first++ != last)
			ret++;
		return (ret);
	}

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
