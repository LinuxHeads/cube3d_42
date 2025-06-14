/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 04:18:56 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/14 03:24:53 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define _USE_MATH_DEFINES
# include "../libft_42/include/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
// #include "/home/msalim/MLX42/include/MLX42/MLX42.h"
# include <MLX42/MLX42.h>
# define FOV (M_PI / 3) // field of view in radians
# define FPS 60         // frames per second, used for timing the game loop
# define STEP 0.01
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
// I use these macros to make sure the order of input is correct
# define MASK_TEXTURES ((1 << (NO + 1)) | (1 << (SO + 1)) | (1 << (WE \
			+ 1)) | (1 << (EA + 1)))
# define MASK_COLORS ((1 << (FlOOR + 1)) | (1 << (CEILING + 1)))

enum				e_texture
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
	double			x;
	double			y;
}					t_vec;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct map_s
{
	char			**content;
	size_t			width;
	size_t			height;
	char			*texture[4];
	t_rgb			floor_color;
	t_rgb			ceiling_color;
	t_list			*buffer;
	int				occurence;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
}					t_map;

typedef struct s_player
{
	t_vec			pos;
	t_vec			player_dir;
	t_vec			camera_plane;
	char			dir;
	double			angle;
}					t_player;

// typedef struct s_ray
// {
// 	t_vec dir; // Ray direction
// 	t_vec		pos;
// 	t_vec delta;      // Delta distances
// 	t_vec side_dist;  // Side distances
// 	t_vec map;        // Map cell we're in
// 	t_vec step;       // Step in x/y (+1 or -1)
// 	double perp_dist; // Distance to wall
// 	int hit;          // Wall hit flag
// 	int side;         // 0 = x side, 1 = y side
// }				t_ray;
typedef struct s_ray
{
	t_vec			dir;
	t_vec			pos;
	t_vec			delta;
	t_vec			side_dist;
	t_vec			map;
	t_vec			step;
	double			perp_dist;
	int				hit;
	int				side;
}					t_ray;

typedef struct s_game
{
	t_map			map;
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				fd;
	int				width;
	int				height;
}					t_game;

/**
 * @brief Initializes the game structure and sets up the game environment,
 *  by checking the input arguments, calling init_map and init_mlx.
 * @param game Pointer to the game structure to be initialized.
 * @param ac Number of command line arguments.
 * @param av Array of command line arguments.
 */
void				init_game(t_game *game, int ac, char **av);

/**
 * @brief Initializes the mlx library and creates a window for the game.
 * @param game Pointer to the game structure.
 */
void				init_mlx(t_game *game);

/**

 * @brief checks the order of the input file to ensure that
	the textures and colors are set in the correct order.
 * @param game Pointer to the game structure.
 * @param order The order to check against.
 * @return 1 if the order is correct, 0 otherwise.
 */
int					check_order(t_game *game, int order);

/**

 * @brief Sets up the input file for the game by
 * opening it and checking for errors.
 * @param game Pointer to the game structure.
 * @param file The name of the input file to be opened.
 * @return void
 * @note This function will exit the program if the file cannot be opened.
 */
void				setup_input_file(t_game *game, char *file);

/**
 * @brief Determines the type of a line in the input file.
 * @param line The line to be checked.
 * @return An integer representing the type of the line:
 *      0 - empty line or comment,\n
 *      1 - North texture,\n
 *      2 - South texture,\n
 *      3 - West texture,\n
 *      4 - East texture,\n
 *      5 - Floor color,\n
 *      6 - Ceiling color,\n
 *      7 - Map line.\n
 * @note The function trims the line before checking its type.
 * @note If the line is empty or contains only whitespace, it returns 0.
 */
int					line_type(char *line);

/**


 * @brief Parses a line from the input file and updates the game map accordingly.
 * @param game Pointer to the game structure.
 * @param line The line to be parsed.
 * @return void
 * @note this is used to parse the map lines and add them to the map buffer.
 */
void				parse_map_line(t_game *game, char *line);

/**

 * @brief Combines multiple lines into a single line by
	removing newline characters.
 * @param line An array of strings representing the lines to be combined.
 * @return A single string containing all the lines combined,
	or NULL if an error occurs.
 * @note The function allocates memory for the combined line,
	which should be freed by the caller.
 */
char				*combine_line(char **line);

/**
 * @brief Parses a line of text to extract RGB color values.
 * @param text A pointer to a string containing the RGB values.
* @param rgb A pointer to a t_rgb struct where the parsed RGB values are stored.
 * @return An integer indicating the success of the parsing:
 *     0 - parsing failed,\n
 *     1 - parsing succeeded.
 */
int					parse_rgb(char **text, t_rgb *rgb);

/**

 * @brief extract rgb color values from a line and store them in the game struct.
	expected format is "F r,g,b" or "C r,g,b".
 * @param game Pointer to the game structure.
 * @param line The line to be parsed,
	which should contain the color information.
 * @return void
 */
void				parse_color(t_game *game, char *line);

/**
 * @brief the main function that parses the input file and initializes the game.
 * @param game Pointer to the game structure.
 * @param file The name of the input file to be parsed.
 * @return void
 */
void				parse(t_game *game, char *file);

/**
 * @brief exit the program with a message and an exit code,
	free everything along the way.
 * @param game Pointer to the game structure.
 * @param message An array of strings containing the message
	to be displayed before exiting.
 * @param exit_code The exit code to be returned to the operating system.

 * @param ptr A pointer to any extra data that needs to be freed before exiting.
 * @return void
 */
void				ft_exit_handler(t_game *game, char **message, int exit_code,
						void *ptr);

/**
 * @brief Parses a texture line and sets the corresponding texture
	in the game structure.
 * @param game Pointer to the game structure.
 * @param line The line to be parsed,
	which should contain the texture information.
 * @param i The index of the texture in the game structure's texture array.
 * @param type The type of the texture being parsed (e.g., NO, SO, WE, EA).
 * @return void
 */
void				parse_texture(t_game *game, char *line, int type);

/**
 * @brief Sets the occurrence of a specific type in the game structure.
 * @param game Pointer to the game structure.
 * @param type The type of occurrence to be set (e.g., NO, SO, WE, EA, FlOOR,
	CEILING, map content).
 * @return void
 */
void				set_occurrence(t_game *game, int type);

/**
 * @brief Checks the occurrence of a specific type in the game structure.
 * @param game Pointer to the game structure.
 * @param type The type of occurrence to be checked (e.g., NO, SO, WE, EA,
	FlOOR, CEILING, map content).
 * @return An integer indicating the occurrence:
 */
int					occurence_check(t_game *game, int type);

/**
 * @brief Initializes the map structure in the game.
 * @param game Pointer to the game structure.
 * @return void
 */
void				fill_map(t_game *game);

/**
 * @brief checks the map for errors such as invalid characters,
	missing player position, and map boundaries.
 * also replaces the player position with a 0. and spaces with 0s.
 * @param game Pointer to the game structure.
 * @return An integer indicating the validity of the map.
 */
int					check_map(t_game *game);

/**
 * @brief duplicate the map content into a new array of strings.
 * @param game Pointer to the game structure.
 * @return A new array of strings containing the duplicated map content,
	or NULL if an error occurs.
 */
char				**dup_map(t_game *game);

/**
 * @brief the main graphcis loop of the game,
	it will render the frame and handle events.
 * @param game Pointer to the game structure.
 * @return void
 */
void				render_frame(void *game);

/**
 * @brief Starts the game by initializing the player position and direction,
	and entering the main loop.
 * @param game Pointer to the game structure.
 * @return void
 */
void				start_game(t_game *game);

/**
 * @brief returns the color value in RGBA format.
 * @param r The red component of the color (0-255).
 * @param g The green component of the color (0-255).
 * @param b The blue component of the color (0-255).
 * @param a The alpha component of the color (0-255).
 * @return An integer representing the color in RGBA format.
 */
int					get_rgba(int r, int g, int b, int a);

int					get_r(int rgba);
int					get_g(int rgba);
int					get_b(int rgba);
int					get_a(int rgba);

/**
 * @brief handles the keypress events for the game, such as moving the player,
	rotating the camera, and closing the window.
 * @param keydata The key data struct containing info about the key pressed.
 * @param param A pointer to the game structure.
 * @return void
 */
void				handle_keypress(mlx_key_data_t keydata, void *param);

t_ray				init_ray(t_player player, int col, int width);
void				draw_column(int col, t_ray ray, t_game *game);

/**
 * @brief calculates the expected wall column drawing-end (wall bottom) index.
 * @param line_height window screen height / distance to the wall
 * @param height window screen height
 * @return an integer representing the end index of drawing a wall
 */
int					get_draw_end(double line_height, int height);


int					get_draw_start(double line_height, int height);
int					get_tex_x(t_game *game, t_ray ray, mlx_texture_t *texture);
mlx_texture_t		*get_wall_texture(t_game *game, t_ray ray);
void				rotate_right(t_game *game);
void				rotate_left(t_game *game);
void				move_forward(t_game *game);
void				move_backward(t_game *game);
void				move_left(t_game *game);
void				move_right(t_game *game);
void				print_game(t_game *game);
void				mouse_move(double x, double y, void *param);
void	free_map(t_game *game);
#endif /* CUBE3D_H */
