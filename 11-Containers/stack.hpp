#pragma once

#include "vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
	class stack
	{
		protected:
			Container _container;
		public:
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;
			typedef Container						container_type;

			/**
			 * @brief Construct a new stack object
			 * @link https://cplusplus.com/reference/stack/stack/stack/#:~:text=explicit%20stack%20(const%20container_type%26%20ctnr%20%3D%20container_type())%3B
			 * @param ctnr
			 */
			explicit stack (const container_type& ctnr = container_type())  : _container(ctnr) {};

			stack (const stack& other){*this = other;};
			~stack(){};
			stack& operator=(const stack& other){_container = other._container;return *this;}
			/**
			 * @brief Member functions
			 * @link https://cplusplus.com/reference/stack/stack/#:~:text=same%20as%20size_t-,Member%20functions,-(constructor)
			 */

			bool				empty() const
			{
				return _container.empty();
			};

			size_type			size() const
			{
				return _container.size();
			};

			value_type&			top()
			{
				return _container.back();
			};

			const value_type&	top() const
			{
				return _container.back();
			};

			void				push (const value_type& val)
			{
				_container.push_back(val);
			};

			void				pop()
			{
				_container.pop_back();
			};

			template <class T1, class _C1>
			friend bool operator==(const stack<T1, _C1>& lhs, const stack<T1, _C1>& rhs);

			template <class T1, class _C1>
			friend bool operator< (const stack<T1, _C1>& lhs, const stack<T1, _C1>& rhs);
	};

	template< class T, class Container >
	bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs._container == rhs._container;
	};

	template< class T, class Container >
	bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return !(lhs == rhs);
	};

	template< class T, class Container >
	bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return lhs._container < rhs._container;
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