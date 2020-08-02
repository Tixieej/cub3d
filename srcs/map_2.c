/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 13:19:06 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/21 13:45:42 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_north(t_vars *vars, char *line, int i, int j)
{
	if ((int)vars->pos.x != 0)
		print_error(20, line);
	vars->pos.x = (double)(j + .5);
	vars->pos.y = (double)(i + .5);
	vars->dir.x = 0;
	vars->dir.y = -1;
	vars->plane.x = 0.66;
	vars->plane.y = 0;
	line[j] = '0';
}

void	player_east(t_vars *vars, char *line, int i, int j)
{
	if ((int)vars->pos.x != 0)
		print_error(20, line);
	vars->pos.x = (double)(j + .5);
	vars->pos.y = (double)(i + .5);
	vars->dir.x = 1;
	vars->dir.y = 0;
	vars->plane.x = 0;
	vars->plane.y = 0.66;
	line[j] = '0';
}

void	player_south(t_vars *vars, char *line, int i, int j)
{
	if ((int)vars->pos.x != 0)
		print_error(20, line);
	vars->pos.x = (double)(j + .5);
	vars->pos.y = (double)(i + .5);
	vars->dir.x = 0;
	vars->dir.y = 1;
	vars->plane.x = -0.66;
	vars->plane.y = 0;
	line[j] = '0';
}

void	player_west(t_vars *vars, char *line, int i, int j)
{
	if ((int)vars->pos.x != 0)
		print_error(20, line);
	vars->pos.x = (double)(j + .5);
	vars->pos.y = (double)(i + .5);
	vars->dir.x = -1;
	vars->dir.y = 0;
	vars->plane.x = 0;
	vars->plane.y = -0.66;
	line[j] = '0';
}

void	make_sprite_array(t_vars *vars, int i, int j)
{
	int			k;
	t_dvector	*tmp_array;

	tmp_array = malloc(sizeof(t_dvector) * (vars->sprite_count + 1));
	if (tmp_array == NULL)
		print_error(23, NULL);
	tmp_array[0].x = (double)(j + .5);
	tmp_array[0].y = (double)(i + .5);
	k = 1;
	while (k < vars->sprite_count + 1)
	{
		tmp_array[k].x = vars->sprite_array[k - 1].x;
		tmp_array[k].y = vars->sprite_array[k - 1].y;
		k++;
	}
	free(vars->sprite_array);
	vars->sprite_count++;
	vars->sprite_array = tmp_array;
}
