/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:50:13 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/24 23:26:56 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	print_error_message(char **message)
{
	int	i;

	if (message == NULL)
		return ;
	i = 0;
	while (message[i])
	{
		ft_putstr_fd(message[i], 2);
		i++;
	}
}

void	ft_exit_handler(t_game *game, char *message[], int exit_code, void *ptr)
{
	char *l;
	
	if (game)
	{
		if (game->line)
			free(game->line);
		while (1)
		{
			l = get_next_line(game->fd);
			if (l)
				free(l);
			else
				break ;
		}
		free_map(game);
	}
	if (ptr)
		free(ptr);
	print_error_message(message);
	exit(exit_code);
}
