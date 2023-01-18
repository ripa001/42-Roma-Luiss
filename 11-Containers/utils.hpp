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

	template <class first, class second>
	struct pair{
		public:
			typedef first first_type;
			typedef second second_type;
			first_type first_one;
			second_type second_one;
			pair() : first_one(), second_one() {}
			pair(const first& a, const second& b) : first_one(a), second_one(b) {}
			
			template <class U, class V>
			pair(const pair<U, V>& pr) : first_one(pr.first_one), second_one(pr.second_one) {}
			pair& operator=(const pair& pr)
			{
				if (this == &pr)
					return (*this);
				first_one = pr.first;
				second_one = pr.second;
				return (*this);
			}
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
