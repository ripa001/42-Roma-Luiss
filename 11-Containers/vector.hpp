#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>
#include <string>
#include "asserts.hpp"
#include "utils.hpp"
#include "iterator.hpp"

namespace ft {

	template <class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::size_type								size_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef ft::random_access_iterator<value_type>							iterator;
			typedef ft::random_access_iterator<const value_type>					const_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			
			// Constructors
			explicit vector(allocator_type const &alloc = allocator_type()) : _size(0), _capacity(0), _begin(NULL), _end(NULL), _alloc(alloc) {};
			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
			_size(0),
			_capacity(0),
			_begin(NULL),
			_alloc(alloc)
			{
				if (n >= 0 && n < this->max_size())
				{
					_size = n;
					_capacity = n;
					_begin = _alloc.allocate(_capacity);
					_end = _begin;
					while (n--)
						_alloc.construct(_end++, val);
				}
				else
					throw std::length_error("vector");
			}
			// explicit vector(size_type n, value_type const &val = value_type(), allocator_type const &alloc = allocator_type()) : _size(0), _capacity(0), _begin(NULL), _end(NULL), _alloc(alloc) {
			// 	if (n > 0 && n < this->max_size())
			// 	{
			// 		_size = n;
			// 		_capacity = n;
			// 		_begin = _alloc.allocate(_capacity);
			// 		_end = _begin + n;
			// 		for (size_type i = 0; i < n; i++)
			// 			_alloc.construct(_begin + i, val);
			// 	}
			// 	else
			// 		throw std::length_error("vector");
			// };
			template <class InputIterator>
			explicit vector(InputIterator first, InputIterator last, allocator_type const &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) : _size(0), _capacity(0), _begin(NULL), _end(NULL), _alloc(alloc) {
				bool is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value;
				if (is_valid)
				{
					size_type	n = ft::distance(first, last);
					if (n > 0 && n < this->max_size())
					{
						_size = n;
						_capacity = n;
						_begin = _alloc.allocate(_capacity);
						_end = _begin + n;
						for (size_type i = 0; i < n; i++)
							_alloc.construct(_begin + i, *first++);
					}
					else
						throw std::length_error("vector");
				}
				else
					throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>();
			};
			
			explicit vector(const vector &x) : _size(0), _capacity(0), _begin(NULL), _end(NULL), _alloc(x._alloc) {
				*this = x;
			};

			vector &operator=(vector const &x) {
				if (x == *this)
					return (*this);
				this->clear();
				if (this->capacity())
				{
					_alloc.deallocate(_begin, _capacity);
					_begin = _alloc.allocate(x.capacity());
					_capacity = x.capacity();
					_end = _begin;
				}
				this->insert(this->end(), x.begin(), x.end());
				return (*this);
			};

			iterator insert(iterator position, const value_type &val)
			{
				size_type	dist = position - this->begin();
				if (this->size() == this->capacity())
				{
					if (!this->capacity())
						this->reserve(1);
					else
						this->reserve(this->size() * 2);
				}
				_end++;
				position = this->begin() + dist;
				size_type	idx = _size + 1;
				size_type	idx2 = _size;
				dist = this->end() - position + 1;
				while (dist--)
					_begin[idx--] = _begin[idx2--];
				*position = val;
				_size++;
				return (position);
			}

			void insert(iterator position, size_type n, const value_type &val)
			{
				size_type	dist = position - this->begin();
				size_type	finalSize = this->size() + n;
				if (finalSize > this->capacity())
					this->reserve(finalSize);
				position = this->begin() + dist;
				_end = _begin + _size;
				size_type	toMove = ft::distance(position, this->end());
				_end = _begin + finalSize;
				_size = finalSize;
				int i = 1;
				while (toMove--)
					_alloc.construct(_end - i++, _begin[dist + toMove]);
				while (n--)
					_alloc.construct(_begin + dist++, val);
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
			{
				bool is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value;
				if (!is_valid)
					throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>();

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
					throw "hey";
				}
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

			void resize(size_type n, value_type val = value_type())
			{
				size_type	new_cap = this->capacity();

				if (n > this->max_size())
					throw std::length_error("vector::resize");
				if (n > this->capacity())
				{
					while (n > new_cap)
						new_cap *= 2;
					this->reserve(new_cap);
					this->insert(this->end(), n - this->size(), val);
				}
				else if (n > this->size())
					this->insert(this->end(), n - this->size(), val);
				else if (n == this->size())
					return ;
				else
				{
					for (size_type i = _size - n; i > 0; i--)
					{
						_alloc.destroy(_end--);
						_size--;
					}
				}
			}

			void	assign(size_type n, const value_type &val) {
				this->clear();
				if (n > this->capacity())
					this->reserve(n);
				this->insert(this->begin(), n, val);
			};

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
				bool is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value;
				if (is_valid)
				{
					this->clear();
					size_type count = ft::distance(first, last);
					if (count > this->capacity())
						this->reserve(count);
					this->insert(this->begin(), first, last);
				}
				else
					throw ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::type>();
			};

			void clear() {
				pointer tmp = _begin;
				while (tmp != _end)
					_alloc.destroy(tmp++);
				_end = _begin;
				_size = 0;
			};

			iterator erase(iterator first, iterator last)
			{
				if (last == this->end())
				{
					_size = first - _begin;
					_end = _begin + _size;
					size_type	dist = ft::distance(first, last);
					size_type	idx = _size;
					while (dist--)
					{
						_alloc.destroy(_begin + idx);
						idx--;
					}
					return (this->end());
				}
				else
				{
					iterator	ret = first;
					_size -= ft::distance(first, last);
					while (last != this->end())
					{
						_alloc.construct(first.pointed(), *last++);
						first++;
					}
					_end = _begin + _size;
					return (ret);
				}
			}

			iterator erase(iterator position)
			{
				iterator	ret = position;
				size_type	idx = position - this->begin();
				size_type	dist = this->end() - position;
				while (dist-- && idx + 1 < this->size())
				{
					_begin[idx] = _begin[idx + 1];
					idx++;
				}
				_alloc.destroy(_end--);
				_size--;
				return (ret);
			}

			void	swap(vector &x) {
				pointer		tmp_begin = this->_begin;
				pointer		tmp_end = this->_end;
				size_type	tmp_capacity = this->_capacity;
				size_type	tmp_size = this->_size;

				this->_begin = x._begin;
				this->_end = x._end;
				this->_capacity = x._capacity;
				this->_size = x._size;

				x._begin = tmp_begin;
				x._end = tmp_end;
				x._capacity = tmp_capacity;
				x._size = tmp_size;
			};

			void push_back(const value_type &val) {
				if (_size == _capacity && _capacity + 1 > this->max_size())
					throw std::length_error("vector::push_back");
				if (this->empty())
					this->reserve(1);
				else if (_size == _capacity)
					this->reserve(_capacity * 2);
				_alloc.construct(_end++, val);
				_size++;
			}

			void pop_back()	{
				if (this->empty())
					return;
				iterator iter = this->end() - 1;
				_alloc.destroy(&(*iter));
				_size--;
				_end--;
			}

			// element access

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

			// const	operator!= (const vector &rhs) const { return (!(*this == rhs)); };
			
			// front and back
			reference		front() { return (*_begin); };
			const_reference	front() const { return (*_begin); };
			reference		back() { return (*(_end - 1)); };
			const_reference	back() const { return (*(_end - 1)); };
		
			// write iterators for vector
			iterator		begin() { return (iterator(_begin)); };
			const_iterator	begin() const { return (const_iterator(_begin)); };
			iterator		end() { return (iterator(_end)); };
			const_iterator	end() const { return (const_iterator(_end)); };
			// reverse_iterator		rbegin() { return (reverse_iterator(_end)); };
			// const_reverse_iterator	rbegin() const { return (const_reverse_iterator(_end)); };
			// reverse_iterator		rend() { return (reverse_iterator(_begin)); };
			// const_reverse_iterator	rend() const { return (const_reverse_iterator(_begin)); };

			virtual	~vector(){};
		private:
			size_type		_size;
			size_type		_capacity;
			pointer			_begin;
			pointer			_end;
			allocator_type	_alloc;
			
		};

		template <class T, class Alloc>
		bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			typename vector<T>::const_iterator iter = lhs.begin();
			typename vector<T>::const_iterator iter2 = rhs.begin();
			while (iter != lhs.end())
			{
				if (iter2 == rhs.end() || *iter != *iter2)
					return (false);
				iter++;
				iter2++;
			}
			return (true);
		}


		// template <class T, class Alloc>
		// bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		// {
		// 	return (!(lhs == rhs));
		// }
	
		// template <class T, class Alloc>
		// bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		// {
		// 	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		// }
	
		// template <class T, class Alloc>
		// bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		// {
		// 	return (!(rhs < lhs));
		// }
	
		// template <class T, class Alloc>
		// bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		// {
		// 	return (rhs < lhs);
		// }
	
		// template <class T, class Alloc>
		// bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		// {
		// 	return (!(rhs > lhs));
		// }
		// Overloads

		template <class InputIt>
		random_access_iterator<InputIt>	operator+(int n, random_access_iterator<InputIt> const & rhs) { return rhs.pointed() + n; };

		template <class InputIt>
		random_access_iterator<InputIt>	operator-(int n, random_access_iterator<InputIt> const & rhs) { return rhs.pointed() - n; };

		template <class InputIt>
		reverse_iterator<InputIt>	operator+(int n, reverse_iterator<InputIt> const & rhs) { return reverse_iterator<InputIt>(rhs.base() - n); };

		template <class InputIt>
		reverse_iterator<InputIt>	operator-(int n, reverse_iterator<InputIt> const & rhs) { return reverse_iterator<InputIt>(rhs.base() + n); };

		template <class InputIt>
		bool	operator==(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() == rhs.pointed()) ? true : false); };

		template <class InputIt, class InputIt2>
		bool	operator==(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() == rhs.pointed()) ? true : false); };

		template <class InputIt>
		bool	operator!=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() == rhs.pointed()) ? false : true); };

		template <class InputIt, class InputIt2>
		bool	operator!=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() == rhs.pointed()) ? false : true); };

		template <class InputIt>
		bool	operator<(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() < rhs.pointed()) ? true : false); };

		template <class InputIt, class InputIt2>
		bool	operator<(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() < rhs.pointed()) ? true : false); };

		template <class InputIt>
		bool	operator<=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() <= rhs.pointed()) ? true : false); };

		template <class InputIt, class InputIt2>
		bool	operator<=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() <= rhs.pointed()) ? true : false); };

		template <class InputIt>
		bool	operator>(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() > rhs.pointed()) ? true : false); };

		template <class InputIt, class InputIt2>
		bool	operator>(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() > rhs.pointed()) ? true : false); };
		
		template <class InputIt>
		bool	operator>=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt> const & rhs) { return ((lhs.pointed() >= rhs.pointed()) ? true : false); };

		template <class InputIt, class InputIt2>
		bool	operator>=(random_access_iterator<InputIt> const & lhs, random_access_iterator<InputIt2> const & rhs) { return ((lhs.pointed() >= rhs.pointed()) ? true : false); };

		template <class InputIt>
		bool			operator==(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return (lhs.base() == rhs.base()); }

		template <class InputIt, class InputIt2>
		bool			operator==(reverse_iterator<InputIt2> const & lhs, reverse_iterator<InputIt> const & rhs) { return (lhs.base() == rhs.base()); }

		template <class InputIt>
		bool			operator!=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() == rhs.base()) ? false : true); }

		template <class InputIt, class InputIt2>
		bool			operator!=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() == rhs.base()) ? false : true); }

		template <class InputIt>
		bool	operator<(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() > rhs.base()) ? true : false); };

		template <class InputIt, class InputIt2>
		bool	operator<(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() > rhs.base()) ? true : false); };

		template <class InputIt>
		bool	operator<=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() >= rhs.base()) ? true : false); };

		template <class InputIt, class InputIt2>
		bool	operator<=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() >= rhs.base()) ? true : false); };

		template <class InputIt>
		bool	operator>(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() < rhs.base()) ? true : false); };

		template <class InputIt, class InputIt2>
		bool	operator>(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() < rhs.base()) ? true : false); };
		
		template <class InputIt>
		bool	operator>=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt> const & rhs) { return ((lhs.base() <= rhs.base()) ? true : false); };

		template <class InputIt, class InputIt2>
		bool	operator>=(reverse_iterator<InputIt> const & lhs, reverse_iterator<InputIt2> const & rhs) { return ((lhs.base() <= rhs.base()) ? true : false); };
};