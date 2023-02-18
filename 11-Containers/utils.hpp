#pragma once

namespace ft {


	template <class first, class second, class res>
	struct binary_function
	{
		typedef first first_argument_type;
		typedef second second_argument_type;
		typedef res result_type;
	};

	template <class T>
	struct less : binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return (x < y);
		}
	};

	template <class K, class V>
	class pair{
		public:
			typedef K first_type;
			typedef V second_type;

			first_type first;
			second_type second;

			pair(void) {}
			pair(const first_type x, const second_type y) : first(x), second(y) {}

			template <class U, class W>
			pair(const pair<U, W>& pr) : first(pr.first), second(pr.second) {}

			pair& operator=(const pair& pr)
			{
				if (this != &pr)
				{
					first = pr.first;
					second = pr.second;
				}
				return (*this);
			}
	};

	template < typename T1, typename T2 >
	pair< T1, T2 > make_pair ( T1 x, T2 y )										{	return pair< T1, T2 >( x, y );	}

	template < typename T1, typename T2 >
	bool	operator == ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return l.first == r.first && l.second == r.second; }

	template < typename T1, typename T2 >
	bool	operator != ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return !(l == r); }

	template < typename T1, typename T2 >
	bool	operator < ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return l.first < r.first || (!(r.first < l.first) && l.second < r.second); }

	template < typename T1, typename T2 >
	bool	operator <= ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return !(r < l); }

	template < typename T1, typename T2 >
	bool	operator > ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return r < l; }

	template < typename T1, typename T2 >
	bool	operator >= ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return !(l < r); }

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	template <class InputIterator1, class InputIterator2, class Compare>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1)) return false;
			else if (comp(*first1, *first2)) return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	};

	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return false;
			}
		}
		return true;
	};

	template <typename T>
	void	swap(T& a, T& b) {
		T	tmp = a;
		a = b;
		b = tmp;
	}
}
