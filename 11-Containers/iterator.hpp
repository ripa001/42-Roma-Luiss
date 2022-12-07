#pragma once

#include <cstddef>
#include "utility.hpp"

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

	// template <class T>
	// class bidirectional_operator(){
	// }
		

	template <class T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T> {
		public:
			typedef std::random_access_iterator_tag												iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::type				value_type;
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

	template <class InputIterator1, class InputIterator2>
	typename ft::iterator_traits<InputIterator1>::difference_type
	distance(InputIterator1 first, InputIterator2 last)
	{
		typename ft::iterator_traits<InputIterator1>::difference_type ret = 0;

		while (first++ != last)
			ret++;
		return (ret);
	}
}

