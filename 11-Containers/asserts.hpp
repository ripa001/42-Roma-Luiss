/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:03:04 by ddelladi          #+#    #+#             */
/*   Updated: 2022/12/08 15:37:18 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <typeinfo>
#include <string>

namespace ft
{
	template <bool is_integral, typename T>
	struct is_integral_res
	{
		typedef T			type;
		static const bool	value = is_integral;
		operator type() const { return value; }
	};

	template <typename>
	struct is_integral_type : public is_integral_res<false, bool> {};

	template <>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};

	template <>
	struct is_integral_type<char> : public is_integral_res<true, char> {};

	template <>
	struct is_integral_type<wchar_t> : public is_integral_res<true, wchar_t> {};

	template <>
	struct is_integral_type<char16_t> : public is_integral_res<true, char16_t> {};

	template <>
	struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

	template <>
	struct is_integral_type<short int> : public is_integral_res<true, short int> {};

	template <>
	struct is_integral_type<int> : public is_integral_res<true, int> {};

	template <>
	struct is_integral_type<long int> : public is_integral_res<true, long int> {};

	template <>
	struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

	template <>
	struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

	template <>
	struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

	template <>
	struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

	template <>
	struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};

	template <>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	template <typename T>
	struct is_integral : public is_integral_type<T> {};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag	{};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	struct contiguous_iterator_tag : public random_access_iterator_tag {};
	
	template <bool is_valid, typename T>
	struct valid_iterator_tag_res
	{
		typedef T			type;
		const static bool	value = is_valid;
	};

	template <typename T>
	struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> {};

	template <>
	struct is_input_iterator_tagged<random_access_iterator_tag> : public valid_iterator_tag_res<true, random_access_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<contiguous_iterator_tag> : public valid_iterator_tag_res<true, contiguous_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<bidirectional_iterator_tag> : public valid_iterator_tag_res<true, bidirectional_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<forward_iterator_tag> : public valid_iterator_tag_res<true, forward_iterator_tag> {};
	
	template <>
	struct is_input_iterator_tagged<input_iterator_tag> : public valid_iterator_tag_res<true, input_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<output_iterator_tag> : public valid_iterator_tag_res<true, output_iterator_tag> {};

	template <typename T>
	struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> {};

	template <>
	struct is_ft_iterator_tagged<random_access_iterator_tag> : public valid_iterator_tag_res<true, random_access_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged< ::std::random_access_iterator_tag> : public valid_iterator_tag_res<true, ::std::random_access_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<bidirectional_iterator_tag> : public valid_iterator_tag_res<true, bidirectional_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged< ::std::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ::std::bidirectional_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<forward_iterator_tag> : public valid_iterator_tag_res<true, forward_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged< ::std::forward_iterator_tag> : public valid_iterator_tag_res<true, ::std::forward_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<input_iterator_tag> : public valid_iterator_tag_res<true, input_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged< ::std::input_iterator_tag> : public valid_iterator_tag_res<true, ::std::input_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<output_iterator_tag> : public valid_iterator_tag_res<true, output_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged< ::std::output_iterator_tag> : public valid_iterator_tag_res<true, ::std::output_iterator_tag> {};

	template <bool Cond, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };
	
	template <typename T>
	class InvalidIteratorException : public std::exception
	{
		private:
		
		public:
			InvalidIteratorException() throw() {}
			InvalidIteratorException(InvalidIteratorException const &src) throw() { *this = src; }
			virtual ~InvalidIteratorException() throw() {}
			InvalidIteratorException &operator=(InvalidIteratorException const &rhs) throw() { (void)rhs; return *this; }
			virtual const char *what() const throw() { return "Invalid iterator"; }
	};
}
