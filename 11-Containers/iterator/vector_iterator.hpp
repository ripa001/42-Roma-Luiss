#pragma once

#include "iterator.hpp"

namespace ft
{
	template <class T>
	class vector_iterator
		: public ft::iterator<typename ft::iterator_traits<T>::iterator_category,
						typename ft::iterator_traits<T>::value_type,
						typename ft::iterator_traits<T>::difference_type,
						typename ft::iterator_traits<T>::pointer,
						typename ft::iterator_traits<T>::reference>
	{
		protected:
			T	_pointer;
		public:
			typedef T                                            		iterator_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T>::reference			reference;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::value_type			value_type;

			vector_iterator() : _pointer(0) {};
			vector_iterator(T value) : _pointer(value) {};
			template <class PIPPO> vector_iterator(const vector_iterator<PIPPO>& u) : _pointer(u.base()) {}
			template <class PIPPO> vector_iterator& operator=(const vector_iterator<PIPPO>& u) { _pointer = u.base(); return *this; }
			reference			operator*() const {
				return *_pointer;
			};
			pointer				operator->() const { return &(operator*()); };
			vector_iterator		&operator++() { ++_pointer; return *this; };
			vector_iterator		operator++(int) {
				vector_iterator tmp(*this);
				++_pointer;
				return tmp;
			};
			vector_iterator		&operator--() { --(this->_pointer); return *this; };
			vector_iterator		operator--(int) {
				vector_iterator tmp(*this);
				--(this->_pointer);
				return tmp;
			};
			vector_iterator		operator+(difference_type n) const { return (vector_iterator(this->_pointer + n)); };
			vector_iterator		&operator+=(difference_type n) { (this->_pointer += n); return (*this); };
			vector_iterator		operator-(difference_type n) const {return (vector_iterator(this->_pointer - n));};
			vector_iterator		&operator-=(difference_type n) { (this->_pointer -= n); return (*this); };
			reference			operator[](int n) { return this->_pointer[n]; };
			T					base() const { return (this->_pointer); };
	};

	template<class T1, class T2>
	bool operator==( const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs )
	{
		return (lhs.base() == rhs.base());
	};

	template<class T1, class T2>
	bool operator!=( const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs )
	{
		return (lhs.base() != rhs.base());
	};

	template<class T1, class T2>
	bool operator<( const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs )
	{
		return (lhs.base() < rhs.base());
	};

	template<class T1, class T2>
	bool operator<=( const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	};

	template<class T1, class T2>
	bool operator>( const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs )
	{
		return (lhs.base() > rhs.base());
	};

	template<class T1, class T2>
	bool operator>=( const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	};

	template <class Iterator>
	vector_iterator<Iterator> operator+ (typename vector_iterator<Iterator>::difference_type n,const vector_iterator<Iterator>& rev_it)
	{
		return vector_iterator<Iterator>(rev_it.base() + n);
	}

		template <class Iterator>
	vector_iterator<Iterator> operator- (typename vector_iterator<Iterator>::difference_type n,const vector_iterator<Iterator>& rev_it)
	{
		return vector_iterator<Iterator>(rev_it.base() + n);
	}
	
	template <class Iterator1, class Iterator2>
	typename vector_iterator<Iterator1>::difference_type
	operator-(const vector_iterator<Iterator1>& x, const vector_iterator<Iterator2>& y)
	{
		return x.base() - y.base();
	}

};