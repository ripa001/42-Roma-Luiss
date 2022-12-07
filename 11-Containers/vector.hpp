#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>
#include <string>
#include "utility.hpp"
#include "iterator.hpp"

namespace ft{
	template <class T, class Alloc = std::allocator<T> >
	class vector{


		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef allocator_type::size_type								size_type;
			typedef allocator_type::difference_type							difference_type;
			typedef allocator_type::reference								reference;
			typedef allocator_type::const_reference							const_reference;
			typedef allocator_type::pointer									pointer;
			typedef allocator_type::const_pointer							const_pointer;
			typedef ft::random_access_iterator<value_type>					iterator;
			typedef ft::random_access_iterator<value_type>					const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			

			explicit vector(allocator_type const &alloc = allocator_type()) : _size(0), _capacity(0), _begin(NULL), _end(NULL), _alloc(alloc) {};
			explicit vector(size_type n, value_type const &val = value_type(), allocator_type const &alloc = allocator_type()) : _size(0), _capacity(0), _begin(NULL), _end(NULL), _alloc(alloc) {
				if (n > 0 && _begin != NULL && _end != NULL && n < this->max_size())
				{
					_size = n;
					_capacity = n;
					_begin = _alloc.allocate(_capacity);
					_end = _begin + n;
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_begin + i, val);
				}
				else
					throw std::length_error("vector");
			};

			vector &operator=(vector const &x) {
				if (this != &x)
				{
					this.clear();
					if (this->capacity())
					{
						this._alloc.deallocate(this._begin, this._capacity);
						this._begin = this._alloc.allocate(x.capacity());
						this._capacity = x._size;
						this._end = this._begin + x._size;
					}
					this->insert(this->end(), other.begin(), other.end())
				}
				return (*this);
			};

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
				bool is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value;
				if (is_valid)
				{
					size_type	positionDist = position - this->begin();
					size_type	finalSize = this->size() + ft::distance(first, last);
					size_type	new_cap = this->capacity();
					if (finalSize > this->capacity())
					{
						if (!this->capacity())
							new_cap = 1;
						while (finalSize > new_cap)
							new_cap *= 2;
						this->reserve(new_cap);
					}
					position = this->begin() + positionDist;
					_end = _begin + _size;
					size_type	toMove = ft::distance(position, this->end());
					_end = _begin + finalSize;
					_size = finalSize;
					size_type	dist = ft::distance(first, last);
					try
					{
						int i = 1;
						while (toMove--)
							_begin[_size - i++] = _begin[positionDist + toMove];
						while (dist--)
							_begin[positionDist++] = *first++;
					}
					catch (...)
					{
						_size = 0;
						_capacity = 0;
						throw "err";
					}
				}
				else
					throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>();
			}

			void reserve(size_type n)
			{
				pointer 	prev_begin = _begin;
				pointer 	prev_end = _end;
				size_type 	prev_capacity = _capacity;
				pointer		tmp_begin = prev_begin;

				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n > _capacity)
				{
					_begin = _alloc.allocate(n);
					_end = _begin;
					_capacity = n;
					while (prev_begin != prev_end)
					{
						_alloc.construct(_end, *prev_begin);
						_end++;
						prev_begin++;
					}
					_end = _begin + ft::distance(tmp_begin, prev_end);
					if (tmp_begin)
						_alloc.deallocate(tmp_begin, prev_capacity);
				}
			};

			size_type		max_size() const { return (allocator_type().max_size()); };
			size_type		capacity() const { return (_capacity); };
			size_type		size() const { return (_size); };
			bool			empty() const { return (_size == 0); };

			// element access and indexing operator

			reference		at(size_type n) {
				if (n >= _size)
					throw std::out_of_range("vector::out_of_range");
				return (_begin[n]);
			};
			const_reference	at(size_type n) const {
				if (n >= _size)
					throw std::out_of_range("vector::out_of_range");
				return (_begin[n]);
			};
			reference 		operator[](size_type n) { 
				if (n >= _capacity)
					throw std::out_of_range("vector::out_of_range");
				return (_begin[n]);
			};
			const_reference	operator[](size_type n) const {
				if (n >= _capacity)
					throw std::out_of_range("vector::out_of_range");
				return (_begin[n]);
			};
			reference		front() { return (*_begin); };
			const_reference	front() const { return (*_begin); };
			reference		back() { return (*(_end - 1)); };
			const_reference	back() const { return (*(_end - 1)); };

			virtual	~vector();
		private:
			size_type		_size;
			size_type		_capacity;
			pointer			_begin;
			pointer			_end;
			allocator_type	_alloc;
			
		};
};