/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 07:23:59 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/12 09:37:08 by abdsalah         ###   ########.fr       */
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
	if (ray.side == 0) // X-side (vertical walls)
	{
		if (ray.dir.x > 0)
			return (get_rgba(255, 0, 0, 255)); // East wall - Red
		else
			return (get_rgba(0, 255, 0, 255)); // West wall - Green
	}
	else // Y-side (horizontal walls)
	{
		if (ray.dir.y > 0)
			return (get_rgba(0, 0, 255, 255)); // South wall - Blue
		else
			return (get_rgba(255, 255, 0, 255)); // North wall - Yellow
	}
}

// CORRECTED render_frame function for MLX42
void	render_frame(void *param)
{
	t_game		*game;
	int			col;
	t_ray		ray;
	static int	frame_count = 0;

	game = (t_game *)param;
	// Debug: Print player position once every 60 frames (roughly 1 second)
	if (frame_count % 60 == 0)
	{
		printf("Player pos: (%.2f, %.2f), dir: (%.2f, %.2f)\n",
			game->player.pos.x, game->player.pos.y, game->player.player_dir.x,
			game->player.player_dir.y);
	}
	frame_count++;
	col = 0;
	while (col < W_WIDTH)
	{
		ray = init_ray(game->player, col); // Setup the ray
		trace_ray(&ray, &game->map);       // Perform DDA to find wall hit
		draw_column(col, ray, game);       // Draw vertical slice
		col++;
	}
}
