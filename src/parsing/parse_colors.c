/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 02:47:28 by abdsalah          #+#    #+#             */
/*   Updated: 2025/06/14 04:00:33 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief checks if a given string is a valid rgb value (0 - 255)
 * @param rgb a string string which contains the rgb value
 * @return a boolean value, True if the value is rgb, False if not
 */
static bool	is_rgb(char *rgb)
{
	if (ft_strlen(rgb) == 0 || ft_strlen(rgb) > 3)
		return (false);
	if (!ft_isnumber(rgb))
		return (false);
	if (ft_atoi(rgb) < 0 || ft_atoi(rgb) > 255)
		return (false);
	return (true);
}

/**
 * @brief assigns a value into a member of the rgb struct 
 	based on the value index
 * @param rgb a pointer to the rgb struct
 * @param i which rgb value to assign based on index 
 	0 for red 1 for green and 2 for blue
 * @param cmp the string containing the rgb value
 * @returns 1 for failure and 0 for success
 */
static int	assign_rgb(t_rgb *rgb, int i, char *cmp)
{
	int	value;

	if (is_rgb(cmp))
	{
		value = ft_atoi(cmp);
		if (i == 0)
			rgb->r = value;
		if (i == 1)
			rgb->g = value;
		if (i == 2)
			rgb->b = value;
	}
	else
		return (1);
	return (0);
}

int	parse_rgb(char **text, t_rgb *rgb)
{
	int		i;
	char	*cmp;

	i = 0;
	while (i < 3)
	{
		cmp = ft_strtrim(text[i], " \tFC\n");
		if (!cmp)
			return (1);
		if (assign_rgb(rgb, i, cmp))
		{
			free(cmp);
			ft_putendl_fd("Error: Invalid RGB value.", 2);
			return (1);
		}
		free(cmp);
		i++;
	}
	return (0);
}

void	parse_color(t_game *game, char *line)
{
	char	**text;
	t_rgb	rgb;

	text = ft_split(line, ',');
	if (!text || !text[0] || !text[1])
	{
		if (text)
			ft_free_split(text);
		ft_exit_handler(game,
			(char *[]){"Error\nInvalid color format on line: ", " file: ",
			__FILE__, " .\n", NULL}, 1, NULL);
	}
	if (parse_rgb(text, &rgb))
	{
		if (text)
			ft_free_split(text);
		ft_exit_handler(game,
			(char *[]){"Error\nInvalid color format\n.", NULL}, 1, NULL);
	}
	if (ft_strncmp(text[0], "F", 1) == 0)
		game->map.floor_color = rgb;
	else if (ft_strncmp(text[0], "C", 1) == 0)
		game->map.ceiling_color = rgb;
	ft_free_split(text);
}
