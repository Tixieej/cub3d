/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:20:00 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/23 13:45:40 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ceiling_floor(char *line, t_vars *vars)
{
	char	**array;
	int		rgb[3];
	int		i;

	array = ft_split(line, ' ');
	if (array == NULL)
		print_error(23, line);
	if (!array[1])
		print_error(9, line);
	i = 0;
	rgb[0] = ft_atoi_colour(array[1], &i);
	if (array[1][i] != ',')
		print_error(9, line);
	i++;
	rgb[1] = ft_atoi_colour(array[1], &i);
	if (array[1][i] != ',')
		print_error(9, line);
	i++;
	rgb[2] = ft_atoi_colour(array[1], &i);
	if (rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1 || array[1][i] != '\0'
	|| array[2] != '\0')
		print_error(9, line);
	ceiling_floor_2(vars, array, rgb, line);
	free_array(array);
}

void	ceiling_floor_2(t_vars *vars, char **array, int *rgb, char *line)
{
	if (ft_strcmp(array[0], "F") == 0)
		parse_floor(vars, rgb);
	else if (ft_strcmp(array[0], "C") == 0)
		parse_ceiling(vars, rgb);
	else
		print_error(5, line);
}

void	parse_floor(t_vars *vars, int *rgb)
{
	if (vars->cub.floor != -1)
		print_error(3, NULL);
	vars->cub.floor = create_trgb(rgb[0], rgb[1], rgb[2]);
	if (vars->cub.floor == -1)
		print_error(9, NULL);
}

void	parse_ceiling(t_vars *vars, int *rgb)
{
	if (vars->cub.ceiling != -1)
		print_error(3, NULL);
	vars->cub.ceiling = create_trgb(rgb[0], rgb[1], rgb[2]);
	if (vars->cub.ceiling == -1)
		print_error(9, NULL);
}
