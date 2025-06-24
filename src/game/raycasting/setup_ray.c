/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 07:23:59 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/24 10:54:40 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	trace_ray(t_ray *ray, t_map *map)
{
	int	hit;

	hit = 0;
	ray->hit = hit;
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (map->content[(int)ray->map.y][(int)ray->map.x] == '1')
			ray->hit = 1;
	}
}

static void	render_scene(t_game *game)
{
	int		col;
	t_ray	ray;

	col = 0;
	while (col < game->width)
	{
		ray = init_ray(game->player, col, game->width);
		trace_ray(&ray, &game->map);
		draw_column(col, ray, game);
		col++;
	}
}

void	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
	render_scene(game);
}
