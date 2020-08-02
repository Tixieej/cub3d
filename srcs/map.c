/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 09:56:56 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/23 23:12:28 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

void		free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int			more_options(t_vars *vars, char *line)
{
	if (*line == '\0')
		return (1);
	else if (*line == 'R')
		resolution(line, vars);
	else if (*line == 'F' || *line == 'C')
		ceiling_floor(line, vars);
	else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
		path_to_png(line, vars);
	else
		return (0);
	return (1);
}

void		divide_function(t_vars *vars, int fd)
{
	int		result;
	char	*line;
	int		begin_found;

	begin_found = 0;
	result = 1;
	while (result == 1)
	{
		result = get_next_line(fd, &line);
		if (result == -1)
			print_error(26, NULL);
		if (begin_found == 0)
			vars->map.map_begin++;
		if (more_options(vars, line) != 1)
		{
			if (*line == '0' || *line == '1' || *line == '2' || *line == ' ')
			{
				map_size(line, vars);
				if (begin_found == 0)
					vars->map.map_begin--;
				begin_found = 1;
			}
			else
				print_error(5, line);
		}
		free(line);
	}
}

void		check_complete(t_vars *vars)
{
	if (!(vars->cub.wall_n.path))
		print_error(10, NULL);
	if (!(vars->cub.wall_e.path))
		print_error(11, NULL);
	if (!(vars->cub.wall_s.path))
		print_error(12, NULL);
	if (!(vars->cub.wall_w.path))
		print_error(13, NULL);
	if (vars->cub.floor == -1)
		print_error(15, NULL);
	if (vars->cub.ceiling == -1)
		print_error(14, NULL);
	if ((int)vars->pos.x == 0)
		print_error(16, NULL);
	if (vars->cub.screenwidth == -1 && vars->cub.screenheight == -1)
		print_error(17, NULL);
	if (!(vars->cub.sprite.path))
		print_error(19, NULL);
}

void		read_cubfile(char **argv, t_vars *vars)
{
	int		fd;

	vars->map.width = 0;
	vars->map.height = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_error(2, NULL);
	if (file_extension(argv[1], ".cub") != 1)
		print_error(24, NULL);
	divide_function(vars, fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_error(2, NULL);
	make_map(vars, fd);
	close(fd);
	check_complete(vars);
}
