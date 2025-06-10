/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 05:59:31 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/06 01:13:12 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
void init_mlx(t_game *game)
{
    game->mlx = mlx_init(W_WIDTH, W_HEIGHT, "Cube3D", true);
    if (!game->mlx)
    {
        ft_exit_handler(game, (char *[]){"Error\nFailed to initialize mlx.\n", NULL}, 1, NULL);
    }
    game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
    if (!game->img)
    {
        mlx_close_window(game->mlx);
        ft_exit_handler(game, (char *[]){"Error\nFailed to create image.\n", NULL}, 1, NULL);
    }
}

