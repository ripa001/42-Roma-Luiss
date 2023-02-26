#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>
#include <string>
#include "asserts.hpp"
#include "utils.hpp"
#include "iterator/iterator.hpp"
#include "iterator/vector_iterator.hpp"
#include "iterator/reverse_iterator.hpp"
#include <limits>


namespace ft
{
	/**
	 * @brief Template from cplusplus.com
	 * @link https://cplusplus.com/reference/vector/vector/#:~:text=template%20%3C%20class%20T%2C%20class%20Alloc%20%3D%20allocator%3CT%3E%20%3E%20class%20vector%3B
	 */
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			/**
			 * @brief Member types from cppreference.com
			 * @link https://en.cppreference.com/w/cpp/container/vector#:~:text=Member%20types-,Member%20type,-Definition
			 */
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer  			const_pointer;
			typedef typename allocator_type::size_type					size_type;
			typedef typename allocator_type::difference_type			difference_type;
			typedef ft::vector_iterator<pointer>						iterator;
			typedef ft::vector_iterator<const_pointer>					const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		protected:
			pointer			__vector;
			size_t			_size;
			size_t			_capacity;
			allocator_type	_allocator;
		/* -------------------------------------- PRIVATE FUNCTIONS -------------------------------------- */
		private:
			void	deallocate()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_allocator.destroy(this->__vector + i);
				this->_allocator.deallocate(this->__vector, this->_capacity);
				this->_capacity = 0;
			}
		public:
			/**
			 * @brief Construct from cplusplus.com
			 * @link https://cplusplus.com/reference/vector/vector/vector/
			 */
			explicit vector(const allocator_type& alloc = allocator_type()) :
				 __vector(NULL), _size(0), _capacity(0), _allocator(alloc)
			{
				this->__vector = this->_allocator.allocate(0);
			};

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
				 __vector(NULL), _size(n), _capacity(n), _allocator(alloc)
			{
				if (n > this->max_size())
					throw std::length_error("vector");
				this->__vector = this->_allocator.allocate(n);
				for (size_t i = 0; i < _size; i++)
					_allocator.construct(__vector + i, val);
			};
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0):
				 __vector(NULL), _size(0), _capacity(0), _allocator(alloc)
			{
				this->__vector = _allocator.allocate(0);
				assign(first, last);
			}

			vector(const vector& x) {this->__vector = NULL;this->_size = 0;this->_capacity = 0; this->_allocator = allocator_type() ;*this = x; };

			~vector() {
				this->deallocate();
			}

			vector&					operator=(const vector& x)
			{
				this->deallocate();
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_allocator = x._allocator;
				this->__vector = this->_allocator.allocate(this->_capacity);
				for (size_t i = 0; i < this->_size; i++)
					_allocator.construct(__vector + i, x.__vector[i]);
				return *this;
			}

			/**
			 * @brief Member function from cplusplus.com
			 * @link https://cplusplus.com/reference/vector/vector/#:~:text=same%20as%20size_t-,Member%20functions,-(constructor)
			 */

			iterator				begin()
			{
				return (this->__vector);
			};
			const_iterator			begin() const
			{
				return const_iterator(this->__vector);
			};

			iterator				end()
			{
				return (this->begin() + this->size());
			};

			const_iterator			end() const
			{
				return const_iterator(this->begin() + this->size()) ;
			};

			reverse_iterator		rbegin()
			{
				return reverse_iterator(end());
			};

			const_reverse_iterator	rbegin() const
			{
				return const_reverse_iterator(end());
			};

			reverse_iterator		rend()
			{
				return reverse_iterator(begin());
			};

			const_reverse_iterator	rend() const
			{
				return const_reverse_iterator(begin());
			};

			size_type				size() const { return this->_size; };

			size_type				max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); };

			void					resize (size_type n, value_type val = value_type())
			{
				while (n < this->size())
					this->pop_back();
				while (n > this->size())
					this->push_back(val);
			}

			size_type				capacity() const { return this->_capacity; };

			bool					empty() const { return (this->_size == 0); };

			void					reserve(size_type n)
			{
				if (n > this->max_size())
					throw (std::length_error("vector max_size"));
				if (n <= this->capacity())
					return;
				pointer tmp = this->_allocator.allocate(n);
				for (size_type i = 0; i < this->size(); i++)
					tmp[i] = this->__vector[i];
				this->deallocate();
				this->_capacity = n;
				this->__vector = tmp;
			};

			reference				operator[] (size_type n) { return (this->__vector[n]); }
			const_reference			operator[] (size_type n) const { return (this->__vector[n]); }

			reference				at (size_type n)
			{
				if (n < 0 || n >= this->size())
					throw std::out_of_range("out of bounds");
				return (this->__vector[n]);
			}
			const_reference			at (size_type n) const
			{
				if (n < 0 || n >= this->size())
					throw std::out_of_range("out of bounds");
				return (this->__vector[n]);
			}

			reference				front() { return (this->__vector[0]); };
			const_reference			front() const { return (this->__vector[0]); };

			reference				back() { return (this->__vector[this->size() - 1]); };
			const_reference			back() const { return (this->__vector[this->size() - 1]); };

			template <class InputIterator>
			void					assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				this->clear();
				this->insert(begin(), first, last);
			};
			void					assign(size_type n, const value_type& val)
			{
				this->clear();
				this->insert(begin(), n, val);
			};

			void push_back(const value_type& x)
			{
				size_type i = 0;
				if (this->_capacity == 0)
				{
					this->reserve(1);
					this->_size++;
					this->_allocator.construct(this->__vector, x);
					return ;
				}
				if (this->_size == this->_capacity)
				{
					if (this->_capacity == 0)
						this->_capacity = 1;
					T* temp = this->_allocator.allocate(2 * this->_capacity);
					this->_capacity *= 2;
					while(i < this->_size)
					{
						this->_allocator.construct(temp + i, this->__vector[i]);
						i++;
					}
					this->_allocator.deallocate(this->__vector, this->_size);
					this->__vector = temp;
				}
				this->_allocator.construct(this->__vector + this->_size, x);
				this->_size++;
			};

			void					pop_back()
			{
				if (this->size() > 0)
					this->_size--;
			};

			iterator					insert(iterator pos, const value_type &v)
			{
				size_type n = pos - this->begin();
				this->insert(pos, 1, v);
				return (iterator(this->__vector + n));
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				pointer		tmp;
				size_type	cap = this->_capacity;
				size_type	shift = -1;
				size_type	pos = position - this->begin();
				size_type	newSize = ((pos + n) >= (this->_size + n)) ? (pos + n): (this->_size + n);

				if (newSize > this->_capacity)
				{
					tmp = this->__vector;
					this->_capacity = ((this->_capacity * 2) >= (this->_size + n)) ? (this->_capacity * 2) : (this->_size + n) ;
					this->__vector = this->_allocator.allocate(this->_capacity);
					while(++shift < this->_size)
						this->__vector[shift] = tmp[shift];
					this->_allocator.deallocate(tmp, cap);
				}
				shift = this->_size - pos;
				this->_size = newSize;
				while ((int)shift-- > 0 && newSize--)
					this->__vector[newSize] = this->__vector[newSize - n];
				while (n--)
					this->__vector[pos++] = val;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral <InputIterator>::value, InputIterator>::type * = NULL)
			{
				InputIterator tmp2 = first;
				pointer		tmp;
				size_type	count = 0;
				while (tmp2++ != last)
					count++;
				size_type	cap = this->_capacity;
				size_type	shift = -1;
				size_type	n = count;
				size_type	pos = position - this->begin();
				size_type	newSize = ((pos + n - 1) >= (this->_size + n - 1)) ? (pos + n - 1): (this->_size + n - 1);

				newSize++;
				if (newSize > this->_capacity)
				{
					tmp = this->__vector;
					this->_capacity = ((this->_capacity * 2) >= (this->_size + n)) ? (this->_capacity * 2) : (this->_size + n);
					this->__vector = this->_allocator.allocate(this->_capacity);
					while(++shift < this->_size)
						this->__vector[shift] = tmp[shift];
				this->_allocator.deallocate(tmp, cap);
				}
					shift = this->_size - pos;
					this->_size = newSize;
					while ((int)shift-- > 0 && newSize--)
						__vector[newSize] = __vector[newSize - n];
				try
				{
					while (n--)
						__vector[pos++] = *(first++);
				}
				catch (...)
				{
					this->_size = 0;
					this->_capacity = 0;
					throw std::exception();
				}
			}

			iterator				erase (iterator position)
			{
				size_type i = position - begin();

				--_size;
				for (; i < _size; i++)
					__vector[i] = __vector[i + 1];
				_allocator.destroy(__vector + i);
				return (position);
			};

			iterator				erase (iterator first, iterator last)
			{
				size_type size = last - first;
				size_type _first = first - begin();
				size_type  i = _first + size - 1;

				while (i >= _first && i != 0){
					_allocator.destroy(__vector + i--);
				}
				if (_first == 0)
					_allocator.destroy(__vector + i--);
				_size -= size;
				for (i = i + 1; i < _size; i++){
					__vector[i] = __vector[i + size];
				}
				_size = i;
				return (first);
			}

			void					swap (vector& x)
			{
				std::swap(this->_size, x._size);
				std::swap(this->_capacity, x._capacity);
				std::swap(this->_allocator, x._allocator);
				std::swap(this->__vector, x.__vector);
			}

			void					clear()
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(__vector + i);
				this->_size = 0;
			};

			allocator_type			get_allocator() const { return (this->_allocator); };
	};


	/**
	 * @brief Operators
	 * @link https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.2/stl__vector_8h-source.html#:~:text=operator%3D%3D(const%20vector%3C_Tp%2C%20_Alloc%3E%26%20__x%2C%20const%20vector%3C_Tp%2C%20_Alloc%3E%26%20__y)
	 */
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}


	/**
	 *  @brief  Vector ordering relation.
	 *  @param  lhs  A %vector.
	 *  @param  rhs  A %vector of the same type as @a lhs.
	 *  @return  True if @a lhs is lexicographically less than @a rhs.
	 *
	 *  This is a total ordering relation.  It is linear in the size of the
	 *  vectors.  The elements must be comparable with @c <.
	 *
	 *  See std::lexicographical_compare() for how the determination is made.
	*/

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

}
namespace std
{
	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	};
}



