/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:55:29 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/06 00:12:48 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// TO-DO : follow the subjects error message protocol

static void    init_mlx(t_game *game)
{
    game->mlx = mlx_init(W_WIDTH, W_HEIGHT, "Cube3D", true);
    if (!game->mlx)
    {
        ft_putendl_fd("Error: Failed to initialize MLX.", 2);
        exit(1);
    }
    game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
    if (!game->img)
    {
        mlx_terminate(game->mlx);
        ft_putendl_fd("Error: Failed to create image.", 2);
        exit(1);
    }
}

static void    init_map(t_game *game)
{
    ft_bzero(&game->map, sizeof(t_map));
    ft_bzero(&game->player, sizeof(t_player));
}

static void    check_args(int ac, char **av)
{
    if (ac != 2)
    {
        ft_putendl_fd("Error: Invalid number of arguments.", 2);
        exit(1);
    }
    if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
    {
        ft_putendl_fd("Error: Invalid file extension. Expected .cub", 2);
        exit(1);
    }
}

void    init(t_game *game, int ac, char **av)
{
    check_args(ac, av);
    init_mlx(game);
    init_map(game);
}