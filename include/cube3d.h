/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 04:18:56 by abdsalah          #+#    #+#             */
/*   Updated: 2025/05/13 05:11:04 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include <MLX42.h>

# define W_WIDTH 1280
# define W_HEIGHT 720

enum e_texture
{
    NO = 0,
    SO,
    WE,
    EA,
    FlOOR,
    CEILING,
};

typedef struct s_vec
{
    double	x;
    double	y;
}	t_vec;

typedef struct s_rgb
{
    int		r;
    int		g;
    int		b;
}	t_rgb;

typedef struct map_s
{
    char	**content;
    size_t	width;
    size_t	height;
    char    *texture[4];
    t_rgb   floor_color;
    t_rgb   ceiling_color;
    t_list  *buffer;
    int     occurence;
}	t_map;

typedef struct s_player
{
    t_vec	pos;
    t_vec	dir;
}	t_player;


typedef struct s_game
{
    t_map		map;
    t_player	player;
    mlx_t		*mlx;
    mlx_image_t	*img;
    int          fd;
}	t_game;

void    init(t_game *game, int ac, char **av);
void    setup_input_file(t_game *game, char *file);
int     line_type(char *line);
void    parse_map_line(t_game *game, char *line);
char    *combine_line(char **line);
int     parse_rgb(char** text, t_rgb *rgb);
void    parse_color(t_game *game, char *line);
void    parse(t_game *game, char *file);
void    ft_exit_handler(t_game *game, char **message, int exit_code, void *ptr);
void    parse_texture(t_game *game, char *line, int i, int type);
void    set_occurrence(t_game *game, int type);
int     occurence_check(t_game *game, int type);
#endif /* CUBE3D_H */