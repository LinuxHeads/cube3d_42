/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:11:24 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/12 08:12:04 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_ray_x(t_ray *ray, t_player player)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player.pos.x - ray->map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - player.pos.x) * ray->delta.x;
	}
}

static void	init_ray_y(t_ray *ray, t_player player)
{
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player.pos.y - ray->map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - player.pos.y) * ray->delta.y;
	}
}

t_ray	init_ray(t_player player, int col)
{
	t_ray	ray;
	double	camera_x;

	camera_x = 2.0 * col / (double)W_WIDTH - 1.0;
	ray.dir.x = player.player_dir.x + player.camera_plane.x * camera_x;
	ray.dir.y = player.player_dir.y + player.camera_plane.y * camera_x;
	ray.map.x = (int)player.pos.x;
	ray.map.y = (int)player.pos.y;
	if (ray.dir.x == 0)
		ray.delta.x = 1e30;
	else
		ray.delta.x = fabs(1.0 / ray.dir.x);
	if (ray.dir.y == 0)
		ray.delta.y = 1e30;
	else
		ray.delta.y = fabs(1.0 / ray.dir.y);
	init_ray_x(&ray, player);
	init_ray_y(&ray, player);
	ray.hit = 0;
	ray.side = -1;
	ray.perp_dist = 0.0;
	return (ray);
}
