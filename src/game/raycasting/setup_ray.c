/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 07:23:59 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/12 23:13:20 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	trace_ray(t_ray *ray, t_map *map)
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
			ray->side = 0; // Hit X side
		}
		else
		{
			ray->side_dist.y += ray->delta.y;
			ray->map.y += ray->step.y;
			ray->side = 1; // Hit Y side
		}
		if (map->content[(int)ray->map.y][(int)ray->map.x] == '1')
			ray->hit = 1;
	}
}

/*
 *
 * msalim: code below is just for testing compilation , it drawed colors
 * abdsalah: shove it up
 *
 * */
int	choose_wall_color(t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.dir.x > 0)
			return (get_rgba(255, 0, 0, 255)); // East wall - Red
		else
			return (get_rgba(0, 255, 0, 255)); // West wall - Green
	}
	else
	{
		if (ray.dir.y > 0)
			return (get_rgba(0, 0, 255, 255)); // South wall - Blue
		else
			return (get_rgba(255, 255, 0, 255)); // North wall - Yellow
	}
}

void	render_scene(t_game *game)
{
	int		col;
	t_ray	ray;

	col = 0;
	while (col < game->width)
	{
		ray = init_ray(game->player, col, game->width); // Setup the ray
		trace_ray(&ray, &game->map);       // Perform DDA to find wall hit
		draw_column(col, ray, game);       // Draw vertical slice
		col++;
	}
}

// Main loop function - combines input and rendering
void	render_frame(void *param)
{
	t_game *game;
	game = (t_game *)param;

	handle_input(game);
	render_scene(game);
}
