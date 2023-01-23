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
	struct pair{
		public:
			typedef K first_type;
			typedef V second_type;
			first_type first;
			second_type second;
			pair() : first(), second() {}
			pair(const first_type& a, const second_type& b) : first(a), second(b) {}
			
			// template <class U, class V>
			// pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

			template <class U1, class U2>
			pair(pair<U1, U2> const & p) : first(p.first), second(p.second) {}

			template <class U1, class U2>
			pair<U1, U2>&	operator=(pair<U1, U2> const & rhs)
			{
				if (this == &rhs)
					return (*this);
				first = rhs.first;
				second = rhs.second;
				return (*this);
			}
			~pair() {};
	};

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
}
