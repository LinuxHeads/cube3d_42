/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:14:39 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/24 10:53:52 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_ceiling(t_game *game, int col, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(game->img, col, y, get_rgba(game->map.ceiling_color.r,
				game->map.ceiling_color.g, game->map.ceiling_color.b, 255));
		y++;
	}
}

static void	draw_floor(t_game *game, int col, int draw_end)
{
	int	y;

	y = draw_end;
	while (y < game->height)
	{
		mlx_put_pixel(game->img, col, y, get_rgba(game->map.floor_color.r,
				game->map.floor_color.g, game->map.floor_color.b, 255));
		y++;
	}
}

void	draw_wall(t_game *game, int *col_and_draw_end, mlx_texture_t *texture,
		t_ray ray)
{
	int		y;
	int		d;
	int		tex_xy[2];
	int		idx;
	double	line_height;

	line_height = (double)game->height / ray.perp_dist;
	tex_xy[0] = get_tex_x(game, ray, texture);
	y = get_draw_start(line_height, game->height) - 1;
	while (++y <= col_and_draw_end[1])
	{
		d = y * 256 - game->height * 128 + (int)(line_height * 128);
		tex_xy[1] = ((d * texture->height) / (int)line_height) / 256;
		if (tex_xy[0] >= 0 && tex_xy[0] < (int)texture->width && tex_xy[1] >= 0
			&& tex_xy[1] < (int)texture->height)
		{
			idx = (tex_xy[1] * texture->width + tex_xy[0]) * 4;
			mlx_put_pixel(game->img, col_and_draw_end[0], y,
				get_rgba(texture->pixels[idx + 0], texture->pixels[idx + 1],
					texture->pixels[idx + 2], texture->pixels[idx + 3]));
		}
	}
}

void	draw_column(int col, t_ray ray, t_game *game)
{
	double			line_height;
	int				draw_end;
	mlx_texture_t	*texture;
	int				draw_start;

	if (ray.side == 0)
		ray.perp_dist = (ray.map.x - game->player.pos.x + (1 - ray.step.x) / 2)
			/ ray.dir.x;
	else
		ray.perp_dist = (ray.map.y - game->player.pos.y + (1 - ray.step.y) / 2)
			/ ray.dir.y;
	line_height = (double)game->height / ray.perp_dist;
	if (line_height == 0)
		return ;
	draw_start = get_draw_start(line_height, game->height);
	draw_end = get_draw_end(line_height, game->height);
	texture = get_wall_texture(game, ray);
	if (!texture)
		return ;
	draw_ceiling(game, col, draw_start);
	draw_wall(game, (int []){col, draw_end}, texture, ray);
	draw_floor(game, col, draw_end);
}
