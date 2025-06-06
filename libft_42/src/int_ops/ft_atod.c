/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 05:16:17 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/06 15:10:02 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	apply_exponent(const char *s, int *i, double value)
{
	int	exp_sign;
	int	exponent;

	exp_sign = 1;
	exponent = 0;
	if (s[*i] != 'e' && s[*i] != 'E')
		return (value);
	(*i)++;
	if (s[*i] == '-' || s[*i] == '+')
	{
		if (s[(*i)++] == '-')
			exp_sign = -1;
		else if (s[(*i)++] == '+')
			exp_sign = 1;
	}
	while (ft_isdigit(s[*i]))
		exponent = exponent * 10 + (s[(*i)++] - '0');
	while (exponent--)
	{
		if (exp_sign == 1)
			value *= 10.0;
		else
			value /= 10.0;
	}
	return (value);
}

int	get_integral_part(const char *s, int *i)
{
	int	integral_part;

	integral_part = 0;
	while (ft_isdigit(s[*i]))
	{
		integral_part = integral_part * 10 + (s[*i] - '0');
		(*i)++;
	}
	return (integral_part);
}

static double	ft_get_fractional_part(const char *s, int *i)
{
	int		fractional_part;
	double	factor;

	fractional_part = 0;
	factor = 1.0;
	if (s[*i] == '.')
		(*i)++;
	while (ft_isdigit(s[*i]))
	{
		fractional_part = fractional_part * 10 + (s[*i] - '0');
		factor *= 10.0;
		(*i)++;
	}
	return (fractional_part / factor);
}

static int	get_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	else if (s[*i] == '+')
		(*i)++;
	return (sign);
}

double	ft_atod(const char *s)
{
	int		i;
	int		sign;
	int		integral;
	double	fractional;
	double	result;

	if (!s || !*s)
		return (0.0);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	sign = get_sign(s, &i);
	integral = get_integral_part(s, &i);
	fractional = ft_get_fractional_part(s, &i);
	result = sign * (integral + fractional);
	return (apply_exponent(s, &i, result));
}
/*
will rewrite in unity tests later
int	main(void)
{
	const char	*str = "  -123.456e2";
	double		result;
	const char	*test1 = "42.0";
	const char	*test2 = "  +3.14";
	const char	*test3 = "-0.001";

	result = ft_atod(str);
	printf("The converted value is: %f\n", result);
	if (fabs(result + -12345.6) < 1e-6)
		printf("Test passed!\n");
	else
		printf("Test failed!\n");
	// Additional test cases
	printf("Test 1: %f\n", ft_atod(test1)); // Expected: 42.0
	printf("Test 2: %f\n", ft_atod(test2)); // Expected: 3.14
	printf("Test 3: %f\n", ft_atod(test3)); // Expected: -0.001
	printf("Test 4: %f\n", ft_atod("1.234e2")); // Expected: 123.4
	return (0);
}
*/
