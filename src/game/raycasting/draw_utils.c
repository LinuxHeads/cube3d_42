/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:15:16 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/12 23:09:39 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_draw_end(double line_height, int height)
{
	int	draw_end;

	draw_end = line_height / 2 + height / 2;
	if (draw_end >= height)
		draw_end = height - 1;
	return (draw_end);
}

int	get_draw_start(double line_height, int height)
{
	int	draw_start;

	draw_start = -line_height / 2 + height / 2;
	if (draw_start < 0)
		draw_start = 0;
	return (draw_start);
}

int	get_tex_x(t_game *game, t_ray ray, mlx_texture_t *texture)
{
	double	wall_x;
	int		tex_x;

	if (ray.side == 0)
		wall_x = game->player.pos.y + ray.perp_dist * ray.dir.y;
	else
		wall_x = game->player.pos.x + ray.perp_dist * ray.dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray.side == 0 && ray.dir.x > 0) || (ray.side == 1 && ray.dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

mlx_texture_t	*get_wall_texture(t_game *game, t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.step.x > 0)
			return (game->map.east_texture);
		else
			return (game->map.west_texture);
	}
	else
	{
		if (ray.step.y > 0)
			return (game->map.south_texture);
		else
			return (game->map.north_texture);
	}
}
