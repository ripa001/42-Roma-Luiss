#pragma once

#include "vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
	class stack
	{
		protected:
			Container c;
		public:
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;
			typedef Container						container_type;

			/**
			 * @brief Construct a new stack object
			 * @link https://cplusplus.com/reference/stack/stack/stack/#:~:text=explicit%20stack%20(const%20container_type%26%20ctnr%20%3D%20container_type())%3B
			 * @param ctnr
			 */
			explicit stack (const container_type& ctnr = container_type())  : c(ctnr) {};

			stack (const stack& other){*this = other;};
			~stack(){};
			stack& operator=(const stack& other){c = other.c;return *this;}
			/**
			 * @brief Member functions
			 * @link https://cplusplus.com/reference/stack/stack/#:~:text=same%20as%20size_t-,Member%20functions,-(constructor)
			 */

			bool				empty() const
			{
				return c.empty();
			};

			size_type			size() const
			{
				return c.size();
			};

			value_type&			top()
			{
				return c.back();
			};

			const value_type&	top() const
			{
				return c.back();
			};

			void				push (const value_type& val)
			{
				c.push_back(val);
			};

			void				pop()
			{
				c.pop_back();
			};

			template <class T1, class _C1>
			friend bool operator==(const stack<T1, _C1>& lhs, const stack<T1, _C1>& rhs);

			template <class T1, class _C1>
			friend bool operator< (const stack<T1, _C1>& lhs, const stack<T1, _C1>& rhs);
	};

	template< class T, class Container >
	bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs.c == rhs.c;
	};

	template< class T, class Container >
	bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return !(lhs == rhs);
	};

	template< class T, class Container >
	bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs.c < rhs.c;
	};

	template< class T, class Container >
	bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return !(rhs < lhs);
	};

	template< class T, class Container >
	bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return (rhs < lhs);
	};

	template< class T, class Container >
	bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return !(lhs < rhs);
	};
}