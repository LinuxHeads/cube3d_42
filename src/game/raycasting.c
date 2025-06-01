/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:15:00 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/01 03:51:20 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	setup_direction(int *stepXY, double *rayDirXY)
{
	if (rayDirXY[0] < 0)
	{
		stepXY[0] = -1;
	}
	else
	{
		stepXY[0] = 1;
	}
	if (rayDirXY[1] < 0)
	{
		stepXY[1] = -1;
	}
	else
	{
		stepXY[1] = 1;
	}
}

void	setup_distance(t_game *game,  double *rayDirXY_deltaDistXY, int *mapXY, double *sideDistXY)
{
	if (rayDirXY_deltaDistXY[0] < 0)
	{
		sideDistXY[0] = (game->player.pos.x - mapXY[0]) * rayDirXY_deltaDistXY[2];
	}
	else
	{
		sideDistXY[0] = (mapXY[0] + 1.0 - game->player.pos.x) * rayDirXY_deltaDistXY[2];
	}
	if (rayDirXY_deltaDistXY[1] < 0)
	{
		sideDistXY[1] = (game->player.pos.y - mapXY[1]) * rayDirXY_deltaDistXY[3];
	}
	else
	{
		sideDistXY[1] = (mapXY[1] + 1.0 - game->player.pos.y) * rayDirXY_deltaDistXY[3];
	}
}

int	dda(t_game *game, double *sideDistXY, double *deltaDistXY, int *stepXY, int *mapXY)
{
	int		hit;
	int		side;
	
	hit = 0;
	while (!hit)
	{
		if (sideDistXY[0] < sideDistXY[1])
		{
			sideDistXY[0] += deltaDistXY[0];
			mapXY[0] += stepXY[0];
			side = 0;
		}
		else
		{
			sideDistXY[1] += deltaDistXY[1];
			mapXY[1] += stepXY[1];
			side = 1;
		}
		if (mapXY[1] < 0 || mapXY[1] >= (int)game->map.height || mapXY[0] < 0 || mapXY[0] >= (int)game->map.width)
			break;
		if (game->map.content[mapXY[1]][mapXY[0]] == '1')
			hit = 1;
	}
	return (side);
}

double	cast_ray(t_game *game, int col)
{
	double	rayDirXY[2];
	double	deltaDistXY[2];
	int		stepXY[2];
	double	sideDistXY[2];
	int		mapXY[2];

	rayDirXY[0] = cos(game->player.angle) + (2 * col / (double)W_WIDTH - 1) * cos(game->player.angle + M_PI_2);
	rayDirXY[1] = sin(game->player.angle) + (2 * col / (double)W_WIDTH - 1) * sin(game->player.angle + M_PI_2);
	mapXY[0] = (int)game->player.pos.x;
	mapXY[1] = (int)game->player.pos.y;
	deltaDistXY[0] = fabs(1 / rayDirXY[0]);
	deltaDistXY[1] = fabs(1 / rayDirXY[1]);
	setup_direction(stepXY, rayDirXY);
	setup_distance( game, (double []){rayDirXY[0], rayDirXY[1], deltaDistXY[0], deltaDistXY[1]}, mapXY, sideDistXY);
	// Calculate exact distance to wall hit
	if (dda( game, sideDistXY, deltaDistXY, stepXY, mapXY) == 0)
		return (sideDistXY[0] - deltaDistXY[0]);
	else
		return (sideDistXY[1] - deltaDistXY[1]);
}

void cast_pixel(t_game *game, int col, int y, int *start_end)
{
	if (y < start_end[0])
		mlx_put_pixel(game->img, col, y, get_rgba(game->map.ceiling_color.r, game->map.ceiling_color.g, game->map.ceiling_color.b, 255));
	else if (y >= start_end[0] && y <= start_end[1])
		mlx_put_pixel(game->img, col, y, get_rgba(100, 200, 200, 255)); // temporary wall color, till we add textures
	else
		mlx_put_pixel(game->img, col, y, get_rgba(game->map.floor_color.r, game->map.floor_color.g, game->map.floor_color.b, 255));
}

void	raycast(t_game *game)
{
	int col;
	double corrected_dist;
	int wall_height;
	int start_end[2];
	int y;
	
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

void    render_frame(void *game)
{
    t_game *game_ptr = (t_game *)game;
    if (!game_ptr || !game_ptr->mlx || !game_ptr->img)
    {
        ft_exit_handler(game_ptr, (char *[]){"Error\nGame not initialized properly.\n", NULL}, 1, NULL);
    }
    
    raycast(game_ptr);
}
