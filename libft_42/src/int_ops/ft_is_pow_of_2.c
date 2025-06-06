/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_pow_of_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:18:17 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/06 05:21:39 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_is_power_of_2(int num)
{
	if (num <= 0)
		return (false);
	while (num > 1)
	{
		if (num % 2 != 0)
			return (false);
		num /= 2;
	}
	return (true);
}
