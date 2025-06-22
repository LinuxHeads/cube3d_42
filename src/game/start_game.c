/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:14:28 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/22 17:41:17 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	resizer(int32_t width, int32_t height, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->height = height;
	game->width = width;
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, width, height);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	render_frame(param);
}

void	init_direction_ns(t_game *game)
{
	if (game->player.dir == 'N')
	{
		game->player.angle = M_PI_2;
		game->player.player_dir.x = 0;
		game->player.player_dir.y = -1;
		game->player.camera_plane.x = 0.66;
		game->player.camera_plane.y = 0;
	}
	else if (game->player.dir == 'S')
	{
		game->player.angle = 3 * M_PI_2;
		game->player.player_dir.x = 0;
		game->player.player_dir.y = 1;
		game->player.camera_plane.x = -0.66;
		game->player.camera_plane.y = 0;
	}
}

void	init_direction_ew(t_game *game)
{
	if (game->player.dir == 'E')
	{
		game->player.angle = 0;
		game->player.player_dir.x = 1;
		game->player.player_dir.y = 0;
		game->player.camera_plane.x = 0;
		game->player.camera_plane.y = 0.66;
	}
	else if (game->player.dir == 'W')
	{
		game->player.angle = M_PI;
		game->player.player_dir.x = -1;
		game->player.player_dir.y = 0;
		game->player.camera_plane.x = 0;
		game->player.camera_plane.y = -0.66;
	}
}

void	check_game_and_textures(t_game *game)
{
	char	*msg1;

	msg1 = "Error\nGame not initialized properly.\n";
	if (!game || !game->mlx || !game->img)
		ft_exit_handler(game, (char *[]){msg1, NULL}, 1, NULL);
}

void	start_game(t_game *game)
{
	check_game_and_textures(game);
	init_direction_ns(game);
	init_direction_ew(game);
	mlx_resize_hook(game->mlx, &resizer, (void *)game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_loop(game->mlx);
	mlx_delete_image(game->mlx, game->img);
	mlx_terminate(game->mlx);
}
