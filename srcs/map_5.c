/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_5.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 13:02:31 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/30 16:30:01 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	valid_chars(char **array, char *line)
{
	int i;

	i = 0;
	while (array[1][i] != '\0')
	{
		if (!(array[1][i] >= '0' && array[1][i] <= '9'))
			print_error(7, line);
		i++;
	}
	i = 0;
	while (array[2][i] != '\0')
	{
		if (!(array[2][i] >= '0' && array[2][i] <= '9'))
			print_error(7, line);
		i++;
	}
}

void	resolution(char *line, t_vars *vars)
{
	char **array;

	array = ft_split(line, ' ');
	if (array == NULL)
		print_error(23, line);
	if (ft_strcmp(array[0], "R") != 0)
		print_error(5, line);
	if (!array[1] || !array[2] || array[3])
		print_error(7, line);
	if (vars->cub.screenwidth != -1 || vars->cub.screenheight != -1)
		print_error(3, line);
	valid_chars(array, line);
	vars->cub.screenwidth = ft_atoi(array[1]);
	vars->cub.screenheight = ft_atoi(array[2]);
	if (vars->cub.screenwidth <= 0 || vars->cub.screenheight <= 0)
		print_error(7, line);
	free_array(array);
}

void	path_to_png(char *line, t_vars *vars)
{
	t_texture *tex;

	tex = NULL;
	if (!ft_strncmp(line, "NO ", 3))
		tex = pick_texture(vars, 0);
	else if (!ft_strncmp(line, "EA ", 3))
		tex = pick_texture(vars, 1);
	else if (!ft_strncmp(line, "SO ", 3))
		tex = pick_texture(vars, 2);
	else if (!ft_strncmp(line, "WE ", 3))
		tex = pick_texture(vars, 3);
	else if (!ft_strncmp(line, "S ", 2))
		tex = pick_texture(vars, 4);
	else
		print_error(5, line);
	if (tex->present == 1)
		print_error(3, line);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	tex->path = ft_strdup(line);
	tex->present = 1;
}

int		go_to_map(t_vars *vars, int result, int fd, char *line)
{
	int	i;

	i = 0;
	while (i < vars->map.map_begin)
	{
		result = get_next_line(fd, &line);
		if (result == -1)
			print_error(26, NULL);
		i++;
		free(line);
	}
	return (result);
}
