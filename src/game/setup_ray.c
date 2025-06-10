#include	"cube3d.h"

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

void	trace_ray(t_ray *ray, t_map *map)
{
	int hit;

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
 * code below is just for testing compilation , it drawed colors
 *
 *
 *
 * */
/* int choose_wall_color(t_ray ray) */
/* { */
/*     if (ray.side == 0) // X-side (vertical walls) */
/*     { */
/*         if (ray.dir.x > 0) */
/*             return get_rgba(255, 0, 0, 255);    // East wall - Red */
/*         else */
/*             return get_rgba(0, 255, 0, 255);    // West wall - Green */
/*     } */
/*     else // Y-side (horizontal walls) */
/*     { */
/*         if (ray.dir.y > 0) */
/*             return get_rgba(0, 0, 255, 255);    // South wall - Blue */
/*         else */
/*             return get_rgba(255, 255, 0, 255);  // North wall - Yellow */
/*     } */
/* } */

/* // Function to draw a vertical line using MLX42 */
/* void draw_vertical_line(t_game *game, int col, int draw_start, int draw_end, int color) */
/* { */
/*     int y; */
    
/*     // Draw ceiling */
/*     for (y = 0; y < draw_start; y++) */
/*     { */
/*         if (col >= 0 && col < W_WIDTH && y >= 0 && y < W_HEIGHT) */
/*             mlx_put_pixel(game->img, col, y, get_rgba(game->map.ceiling_color.r, */ 
/*                          game->map.ceiling_color.g, game->map.ceiling_color.b, 255)); */
/*     } */
    
/*     // Draw wall */
/*     for (y = draw_start; y <= draw_end; y++) */
/*     { */
/*         if (col >= 0 && col < W_WIDTH && y >= 0 && y < W_HEIGHT) */
/*             mlx_put_pixel(game->img, col, y, color); */
/*     } */
    
/*     // Draw floor */
/*     for (y = draw_end + 1; y < W_HEIGHT; y++) */
/*     { */
/*         if (col >= 0 && col < W_WIDTH && y >= 0 && y < W_HEIGHT) */
/*             mlx_put_pixel(game->img, col, y, get_rgba(game->map.floor_color.r, */ 
/*                          game->map.floor_color.g, game->map.floor_color.b, 255)); */
/*     } */
/* } */

/* // CORRECTED draw_column function */
/* void draw_column(int col, t_ray ray, t_game *game) */
/* { */
/*     double line_height; */
/*     int draw_start; */
/*     int draw_end; */

/*     // Calculate perpendicular distance to fix fish-eye effect */
/*     if (ray.side == 0) // X-side hit */
/*         ray.perp_dist = (ray.map.x - game->player.pos.x + (1 - ray.step.x) / 2) / ray.dir.x; */
/*     else // Y-side hit */
/*         ray.perp_dist = (ray.map.y - game->player.pos.y + (1 - ray.step.y) / 2) / ray.dir.y; */

/*     // Calculate line height */
/*     line_height = (double)W_HEIGHT / ray.perp_dist; */
    
/*     // Calculate draw start and end points */
/*     draw_start = (int)(-line_height / 2 + W_HEIGHT / 2); */
/*     if (draw_start < 0) */
/*         draw_start = 0; */
    
/*     draw_end = (int)(line_height / 2 + W_HEIGHT / 2); */
/*     if (draw_end >= W_HEIGHT) */
/*         draw_end = W_HEIGHT - 1; */

/*     draw_vertical_line(game, col, draw_start, draw_end, choose_wall_color(ray)); */
/* } */

/* // CORRECTED render_frame function for MLX42 */
/* void render_frame(void *param) */
/* { */
/*     t_game *game = (t_game *)param; */
/*     int col; */
/*     t_ray ray; */
    
/*     // Debug: Print player position once every 60 frames (roughly 1 second) */
/*     static int frame_count = 0; */
/*     if (frame_count % 60 == 0) */
/*     { */
/*         printf("Player pos: (%.2f, %.2f), dir: (%.2f, %.2f)\n", */ 
/*                game->player.pos.x, game->player.pos.y, */
/*                game->player.player_dir.x, game->player.player_dir.y); */
/*     } */
/*     frame_count++; */
    
/*     col = 0; */
/*     while (col < W_WIDTH) */
/*     { */
/*         ray = init_ray(game->player, col);  // Setup the ray */
/*         trace_ray(&ray, &game->map);        // Perform DDA to find wall hit */
/*         draw_column(col, ray, game);        // Draw vertical slice */
/*         col++; */
/*     } */
/* } */

