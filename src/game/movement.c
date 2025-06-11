/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:17:57 by msalim            #+#    #+#             */
/*   Updated: 2025/06/11 15:28:31 by msalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void move_forward(t_game *game)
{
    double new_x = game->player.pos.x + game->player.player_dir.x * MOVE_SPEED;
    double new_y = game->player.pos.y + game->player.player_dir.y * MOVE_SPEED;
    
    // Check collision before moving
    if (game->map.content[(int)new_y][(int)game->player.pos.x] != '1')
        game->player.pos.y = new_y;
    if (game->map.content[(int)game->player.pos.y][(int)new_x] != '1')
        game->player.pos.x = new_x;
}

void move_backward(t_game *game)
{
    double new_x = game->player.pos.x - game->player.player_dir.x * MOVE_SPEED;
    double new_y = game->player.pos.y - game->player.player_dir.y * MOVE_SPEED;
    
    if (game->map.content[(int)new_y][(int)game->player.pos.x] != '1')
        game->player.pos.y = new_y;
    if (game->map.content[(int)game->player.pos.y][(int)new_x] != '1')
        game->player.pos.x = new_x;
}

void move_left(t_game *game)
{
    // Strafe left (perpendicular to direction)
    double new_x = game->player.pos.x - game->player.camera_plane.x * MOVE_SPEED;
    double new_y = game->player.pos.y - game->player.camera_plane.y * MOVE_SPEED;
    
    if (game->map.content[(int)new_y][(int)game->player.pos.x] != '1')
        game->player.pos.y = new_y;
    if (game->map.content[(int)game->player.pos.y][(int)new_x] != '1')
        game->player.pos.x = new_x;
}

void move_right(t_game *game)
{
    // Strafe right (perpendicular to direction)
    double new_x = game->player.pos.x + game->player.camera_plane.x * MOVE_SPEED;
    double new_y = game->player.pos.y + game->player.camera_plane.y * MOVE_SPEED;
    
    if (game->map.content[(int)new_y][(int)game->player.pos.x] != '1')
        game->player.pos.y = new_y;
    if (game->map.content[(int)game->player.pos.y][(int)new_x] != '1')
        game->player.pos.x = new_x;
}

void rotate_right(t_game *game)
{
    double old_dir_x = game->player.player_dir.x;
    double old_plane_x = game->player.camera_plane.x;
    
    game->player.player_dir.x = game->player.player_dir.x * cos(ROT_SPEED) 
                               - game->player.player_dir.y * sin(ROT_SPEED);
    game->player.player_dir.y = old_dir_x * sin(ROT_SPEED) 
                               + game->player.player_dir.y * cos(ROT_SPEED);
    
    game->player.camera_plane.x = game->player.camera_plane.x * cos(ROT_SPEED) 
                                 - game->player.camera_plane.y * sin(ROT_SPEED);
    game->player.camera_plane.y = old_plane_x * sin(ROT_SPEED) 
                                 + game->player.camera_plane.y * cos(ROT_SPEED);
}

void rotate_left(t_game *game)
{
    double old_dir_x = game->player.player_dir.x;
    double old_plane_x = game->player.camera_plane.x;
    
    game->player.player_dir.x = game->player.player_dir.x * cos(-ROT_SPEED) 
                               - game->player.player_dir.y * sin(-ROT_SPEED);
    game->player.player_dir.y = old_dir_x * sin(-ROT_SPEED) 
                               + game->player.player_dir.y * cos(-ROT_SPEED);
    
    game->player.camera_plane.x = game->player.camera_plane.x * cos(-ROT_SPEED) 
                                 - game->player.camera_plane.y * sin(-ROT_SPEED);
    game->player.camera_plane.y = old_plane_x * sin(-ROT_SPEED) 
                                 + game->player.camera_plane.y * cos(-ROT_SPEED);
}

void handle_keypress(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(game->mlx);
        else if (keydata.key == MLX_KEY_W)
            move_forward(game);
        else if (keydata.key == MLX_KEY_S)
            move_backward(game);
        else if (keydata.key == MLX_KEY_A)
            move_left(game);
        else if (keydata.key == MLX_KEY_D)
            move_right(game);
        else if (keydata.key == MLX_KEY_LEFT)
            rotate_left(game);
        else if (keydata.key == MLX_KEY_RIGHT)
            rotate_right(game);
    }
}


