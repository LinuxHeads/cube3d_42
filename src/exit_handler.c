/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:50:13 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/06 05:13:05 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_mlx(t_game *game)
{
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
	}
	game->img = NULL;
	game->mlx = NULL;
}

void	free_map(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map.height)
	{
		free(game->map.content[i]);
		i++;
	}
	free(game->map.content);
	game->map.content = NULL;
	if (game->map.buffer)
		ft_lstclear(&game->map.buffer, free);
	game->map.buffer = NULL;
	i = -1;
	while (++i < 4)
	{
		if (game->map.texture[i])
		{
			free(game->map.texture[i]);
			game->map.texture[i] = NULL;
		}
	}
	if (game->fd > 0)
		close(game->fd);
	game->fd = -1;
}

void	print_error_message(char **message)
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
	if (game)
		free_map(game);
	if (ptr)
		free(ptr);
	print_error_message(message);
	exit(exit_code);
}
