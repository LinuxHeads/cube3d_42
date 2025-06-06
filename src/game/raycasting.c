/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:15:00 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/06 05:18:30 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	setup_direction(int *step_xy, double *rayDirXY)
{
	if (rayDirXY[0] < 0)
	{
		step_xy[0] = -1;
	}
	else
	{
		step_xy[0] = 1;
	}
	if (rayDirXY[1] < 0)
	{
		step_xy[1] = -1;
	}
	else
	{
		step_xy[1] = 1;
	}
}

void	setup_distance(t_game *game, double *rayDirXY_deltaDistXY, int *map_xy,
		double *side_dist_xy)
{
	if (rayDirXY_deltaDistXY[0] < 0)
	{
		side_dist_xy[0] = (game->player.pos.x - map_xy[0])
			* rayDirXY_deltaDistXY[2];
	}
	else
	{
		side_dist_xy[0] = (map_xy[0] + 1.0 - game->player.pos.x)
			* rayDirXY_deltaDistXY[2];
	}
	if (rayDirXY_deltaDistXY[1] < 0)
	{
		side_dist_xy[1] = (game->player.pos.y - map_xy[1])
			* rayDirXY_deltaDistXY[3];
	}
	else
	{
		side_dist_xy[1] = (map_xy[1] + 1.0 - game->player.pos.y)
			* rayDirXY_deltaDistXY[3];
	}
}

int	dda(t_game *game, double *side_dist_xy, double *deltaDistXY, int *step_xy,
		int *map_xy)
{
	int	hit;
	int	side;

	hit = 0;
	while (!hit)
	{
		if (side_dist_xy[0] < side_dist_xy[1])
		{
			side_dist_xy[0] += deltaDistXY[0];
			map_xy[0] += step_xy[0];
			side = 0;
		}
		else
		{
			side_dist_xy[1] += deltaDistXY[1];
			map_xy[1] += step_xy[1];
			side = 1;
		}
		if (map_xy[1] < 0 || map_xy[1] >= (int)game->map.height || map_xy[0] < 0
			|| map_xy[0] >= (int)game->map.width)
			break ;
		if (game->map.content[map_xy[1]][map_xy[0]] == '1')
			hit = 1;
	}
	return (side);
}

double	cast_ray(t_game *game, int col)
{
	double	ray_dir_xy[2];
	double	delta_dist_xy[2];
	int		step_xy[2];
	double	side_dist_xy[2];
	int		map_xy[2];

	ray_dir_xy[0] = cos(game->player.angle) + (2 * col / (double)W_WIDTH - 1)
		* cos(game->player.angle + M_PI_2);
	ray_dir_xy[1] = sin(game->player.angle) + (2 * col / (double)W_WIDTH - 1)
		* sin(game->player.angle + M_PI_2);
	map_xy[0] = (int)game->player.pos.x;
	map_xy[1] = (int)game->player.pos.y;
	delta_dist_xy[0] = fabs(1 / ray_dir_xy[0]);
	delta_dist_xy[1] = fabs(1 / ray_dir_xy[1]);
	setup_direction(step_xy, ray_dir_xy);
	setup_distance(game, (double []){ray_dir_xy[0], ray_dir_xy[1],
		delta_dist_xy[0], delta_dist_xy[1]}, map_xy, side_dist_xy);
	// Calculate exact distance to wall hit
	if (dda(game, side_dist_xy, delta_dist_xy, step_xy, map_xy) == 0)
		return (side_dist_xy[0] - delta_dist_xy[0]);
	else
		return (side_dist_xy[1] - delta_dist_xy[1]);
}

void	cast_pixel(t_game *game, int col, int y, int *start_end)
{
	if (y < start_end[0])
		mlx_put_pixel(game->img, col, y, get_rgba(game->map.ceiling_color.r,
				game->map.ceiling_color.g, game->map.ceiling_color.b, 255));
	else if (y >= start_end[0] && y <= start_end[1])
		mlx_put_pixel(game->img, col, y, get_rgba(100, 200, 200, 255));
	// temporary wall color, till we add textures
	else
		mlx_put_pixel(game->img, col, y, get_rgba(game->map.floor_color.r,
				game->map.floor_color.g, game->map.floor_color.b, 255));
}

void	raycast(t_game *game)
{
	int		col;
	double	corrected_dist;
	int		wall_height;
	int		start_end[2];
	int		y;

	col = 0;
	while (col < W_WIDTH)
	{
		corrected_dist = cast_ray(game, col);
		wall_height = (int)(W_HEIGHT / corrected_dist);
		start_end[0] = (W_HEIGHT / 2) - (wall_height / 2);
		start_end[1] = (W_HEIGHT / 2) + (wall_height / 2);
		y = 0;
		while (y < W_HEIGHT)
		{
			cast_pixel(game, col, y, start_end);
			y++;
		}
		col++;
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	render_frame(void *game)
{
	t_game	*game_ptr;

	game_ptr = (t_game *)game;
	if (!game_ptr || !game_ptr->mlx || !game_ptr->img)
	{
		ft_exit_handler(game_ptr,
			(char *[]){"Error\nGame not initialized properly.\n", NULL}, 1,
			NULL);
	}
	raycast(game_ptr);
}
