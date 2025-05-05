/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 05:16:17 by abdsalah          #+#    #+#             */
/*   Updated: 2025/03/31 19:40:20 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>

double ft_atod(const char *s)
{
    double result = 0.0;
    double factor = 1.0;
    int sign = 1;
    int i = 0;

    if (!s || *s == '\0')
        return 0.0;

    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' ||
           s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
        i++;

    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (s[i] == '+')
        i++;

    while (s[i] >= '0' && s[i] <= '9')
    {
        result = result * 10.0 + (s[i] - '0');
        i++;
    }

    if (s[i] == '.')
    {
        i++;
        while (s[i] >= '0' && s[i] <= '9')
        {
            factor /= 10.0;
            result += (s[i] - '0') * factor;
            i++;
        }
    }

    return sign * result;
}
