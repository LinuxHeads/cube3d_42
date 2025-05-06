/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:55:29 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/06 06:34:55 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void    init_map(t_game *game)
{
    ft_bzero(&game->map, sizeof(t_map));
    ft_bzero(&game->player, sizeof(t_player));
}

static void    check_args(int ac, char **av)
{
    if (ac != 2)
    {
        ft_exit_handler(NULL, (char *[]){"Error\nInvalid number of arguments.\nUsage: ./cube3d map.cub", NULL}, 1, NULL);
    }
    if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
    {
        ft_exit_handler(NULL, (char *[]){"Error\nInvalid file extension. Expected .cub", NULL}, 1, NULL);
    }
}

void    init(t_game *game, int ac, char **av)
{
    check_args(ac, av);
    // init_mlx(game);
    init_map(game);
    game->fd = -1;
}