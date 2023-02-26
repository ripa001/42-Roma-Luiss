/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:49:56 by ddelladi          #+#    #+#             */
/*   Updated: 2023/02/26 18:34:42 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstddef>
#include "../utils.hpp"

namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t,
						class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T								*pointer;
		typedef T								&reference;
	};

	template<class  T>
	struct iterator_traits<const T*>{
		typedef T 									value_type;
		typedef std::ptrdiff_t 						difference_type;
		typedef std::random_access_iterator_tag 	iterator_category;
		typedef const T* 							pointer;
		typedef const T& 							reference;
	};
	
}