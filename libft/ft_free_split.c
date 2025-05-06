/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:32:24 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/06 02:32:29 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **split)
{
    int	i;

    i = 0;
    if (!split)
        return ;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}