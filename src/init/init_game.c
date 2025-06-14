/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:55:29 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/14 03:55:49 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_map(t_game *game)
{
	ft_bzero(&game->map, sizeof(t_map));
	ft_bzero(&game->player, sizeof(t_player));
	game->width = 1280;
	game->height = 720;
	game->fd = -1;
}

static void	check_args(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nInvalid number of args.\nUsage: ./cube3d map.cub\n");
		exit(1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		printf("Error\nInvalid file extension. Expected .cub\n");
		exit(1);
	}
}

void	init_game(t_game *game, int ac, char **av)
{
	check_args(ac, av);
	init_map(game);
}
