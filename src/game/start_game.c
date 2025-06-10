/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:14:28 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/06 01:15:43 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	start_game(t_game *game)
{
	if (!game || !game->mlx || !game->img)
	{
		ft_exit_handler(game,
			(char *[]){"Error\nGame not initialized properly.\n", NULL}, 1,
			NULL);
	}
	if (game->player.dir == 'N')
		game->player.angle = M_PI_2;
	if (game->player.dir == 'S')
		game->player.angle = 3 * M_PI_2;
	if (game->player.dir == 'E')
		game->player.angle = 0;
	if (game->player.dir == 'W')
		game->player.angle = M_PI;
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_loop(game->mlx);
	mlx_delete_image(game->mlx, game->img);
	mlx_terminate(game->mlx);
}
