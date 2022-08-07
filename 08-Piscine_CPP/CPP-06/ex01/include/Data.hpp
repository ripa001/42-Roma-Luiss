/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dripanuc <dripanuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 13:09:43 by dripanuc          #+#    #+#             */
/*   Updated: 2022/08/07 13:09:43 by dripanuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

#include <iostream>
#include <stdint.h>
struct Data
{
	int	value;

	Data();
	Data(const Data& other);
	~Data();

	Data&	operator =(const Data& other);
};

#endif
