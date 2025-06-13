/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:14:28 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/12 23:45:46 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	resizer( int32_t width, int32_t height, void *param)
{
	t_game *game;
	
	game = (t_game *)param;
	game->height = height;
	game->width = width;
	mlx_delete_image(game->mlx, game->img);
	// null check it
	game->img = mlx_new_image(game->mlx, width, height);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	render_frame(param);
}

int	load_textures(t_game *game)
{
	if (!game || !game->mlx)
		return (0);
	game->map.north_texture = mlx_load_png(game->map.texture[NO]);
	if (!game->map.north_texture)
		return (0);
	game->map.south_texture = mlx_load_png(game->map.texture[SO]);
	if (!game->map.south_texture)
		return (0);
	game->map.west_texture = mlx_load_png(game->map.texture[WE]);
	if (!game->map.west_texture)
		return (0);
	game->map.east_texture = mlx_load_png(game->map.texture[EA]);
	if (!game->map.east_texture)
		return (0);
	return (1);
}

void	start_game(t_game *game)
{
	if (!game || !game->mlx || !game->img)
	{
		ft_exit_handler(game,
			(char *[]){"Error\nGame not initialized properly.\n", NULL}, 1,
			NULL);
	}
	if (!load_textures(game))
	{
		// this will probably murder some memory bits
		ft_exit_handler(game, (char *[]){"Error\nFailed to load textures.\n",
			NULL}, 1, NULL);
	}
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
	else if (game->player.dir == 'E')
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
	mlx_resize_hook(game->mlx, &resizer, (void *)game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_key_hook(game->mlx, &handle_keypress, game);
	mlx_loop(game->mlx);
	mlx_delete_image(game->mlx, game->img);
	mlx_terminate(game->mlx);
}
