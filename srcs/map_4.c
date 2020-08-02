/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_4.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/18 13:06:42 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/30 09:26:49 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

void	map_size(char *line, t_vars *vars)
{
	int	i;

	i = 0;
	vars->map.height++;
	while (line[i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != ' '
		&& line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
			print_error(8, line);
		i++;
	}
	if (i > vars->map.width)
		vars->map.width = i;
}

void	read_line(char *line, t_vars *vars, int i)
{
	int j;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'N')
			player_north(vars, line, i, j);
		else if (line[j] == 'E')
			player_east(vars, line, i, j);
		else if (line[j] == 'S')
			player_south(vars, line, i, j);
		else if (line[j] == 'W')
			player_west(vars, line, i, j);
		else if (line[j] == '2')
			make_sprite_array(vars, i, j);
		j++;
	}
}

void	check_line_of_map(t_vars *vars, char *line, int i)
{
	if (*line == '0' || *line == '1' || *line == '2' || *line == ' ')
	{
		read_line(line, vars, i);
		vars->map.map[i] = (char *)malloc(sizeof(char) * (vars->map.width + 1));
		if (vars->map.map[i] == NULL)
			print_error(23, line);
		ft_strlcpy(vars->map.map[i], line, vars->map.width + 1);
	}
	else
		print_error(8, line);
}

void	make_map(t_vars *vars, int fd)
{
	int		result;

	if (vars->map.height <= 0)
		print_error(18, NULL);
	result = 1;
	vars->map.map = (char **)malloc(sizeof(char *) * vars->map.height);
	if (vars->map.map == NULL)
		print_error(23, NULL);
	read_map(vars, result, fd);
	floodfill(vars->map, (int)vars->pos.x, (int)vars->pos.y);
	empty_out(vars->map, vars);
}

void	read_map(t_vars *vars, int result, int fd)
{
	int		i;
	char	*line;

	line = NULL;
	result = go_to_map(vars, result, fd, line);
	i = 0;
	while (i < vars->map.height && result == 1)
	{
		result = get_next_line(fd, &line);
		if (result == -1)
			print_error(26, NULL);
		check_line_of_map(vars, line, i);
		i++;
		free(line);
	}
	if (i < vars->map.height)
		print_error(8, line);
	while (result == 1)
	{
		result = get_next_line(fd, &line);
		if (*line != '\0' || result == -1)
			print_error(21, line);
		free(line);
	}
	close(fd);
}
