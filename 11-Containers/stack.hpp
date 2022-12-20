#pragma once

#include "vector.hpp"

namespace ft{
	template <class T, class Container = vector<T>>
	class stack{
		public:
			typedef				Container					container_type;
			typedef typename	Container::value_type		value_type;
			typedef typename	Container::size_type		size_type;
			typedef typename	Container::reference		reference;
			typedef typename	Container::const_reference	const_reference;

			explicit stack(const Container& ctnr = Container()) {this->c = ctnr;};
			stack(const stack& other){this = other;}
			stack&	operator=(const stack& rhs)
			{
				if (this == &rhs)
					return (*this);
				this->c = rhs.c;
				return (*this);
			}
			virtual	~stack(){};

			bool		empty() const { return (c.empty()); };
			size_type	size() const { return (c.size()); };
			
			reference		top(){ return (c.back()); };
			const_reference	top() const { return (c.back()); };

			void			push(const value_type &value){ c.push_back(value); };
			void 			pop(){ c.pop_back(); };
			


		protected:
			Container c;

	};
}