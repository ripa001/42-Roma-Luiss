#include "iterator.hpp"

namespace ft
{
	/**
	 * @brief reverse_iterator template from cppreference.com
	 * @link https://en.cppreference.com/w/cpp/iterator/reverse_iterator
	 * @link
	 */
	template <class T>
	class reverse_iterator
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

			reverse_iterator(){};
			reverse_iterator(T value) : _pointer(value) {};
			template <class PIPPO> reverse_iterator(const reverse_iterator<PIPPO>& u) : _pointer(u.base()) {}
			template <class PIPPO> reverse_iterator& operator=(const reverse_iterator<PIPPO>& u) { _pointer = u.base(); return *this; }
			reference			operator*() const {
				T tmp = _pointer; return *--tmp;
			};
			pointer					operator->() const {
				return &(operator*());
			};
			reverse_iterator		&operator++() { --_pointer; return *this; };
			reverse_iterator		operator++(int) {
				reverse_iterator tmp(*this);
				--_pointer;
				return tmp;
			};
			reverse_iterator		&operator--() { ++(this->_pointer); return *this; };
			reverse_iterator		operator--(int) {
				reverse_iterator tmp(*this);
				++(this->_pointer);
				return tmp;
			};
			reverse_iterator operator-( difference_type n ) const;
			reverse_iterator operator+( difference_type n ) const;
			reverse_iterator         operator-   (const reverse_iterator & x) const        { return (reverse_iterator(_pointer + x.base())); }
			reverse_iterator         operator+   (const reverse_iterator & x) const        { return (reverse_iterator(_pointer - x.base())); }
			reverse_iterator		operator+(difference_type n) { return (reverse_iterator(this->_pointer - n)); };
			reverse_iterator		&operator+=(difference_type n) { (this->_pointer -= n); return (*this); };
			reverse_iterator		operator-(difference_type n) {return (reverse_iterator(this->_pointer + n));};
			reverse_iterator		&operator-=(difference_type n) { (this->_pointer += n); return (*this); };
			reference				operator[](int n) { return  base()[ - n - 1 ]; };
			T						base() const { return (this->_pointer); };
	};

	template<class T1, class T2>
	bool operator==( const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs )
	{
		return (lhs.base() == rhs.base());
	};

	template<class T1, class T2>
	bool operator!=( const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs )
	{
		return (lhs.base() != rhs.base());
	};

	template<class T1, class T2>
	bool operator<( const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs )
	{
		return (lhs.base() > rhs.base());
	};

	template<class T1, class T2>
	bool operator<=( const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	};

	template<class T1, class T2>
	bool operator>( const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs )
	{
		return (lhs.base() < rhs.base());
	};

	template<class T1, class T2>
	bool operator>=( const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n,const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}
		template <class Iterator>
	reverse_iterator<Iterator> operator- (typename reverse_iterator<Iterator>::difference_type n,const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() + n);
	}

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator-(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y)
	{
		return y.base() - x.base();
	}
};