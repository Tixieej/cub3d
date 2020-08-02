/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floodfill.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 22:01:01 by rixt          #+#    #+#                 */
/*   Updated: 2020/07/21 14:07:51 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floodfill(t_map map, int x, int y)
{
	if (map.map[y][x] == '0' || map.map[y][x] == '2')
	{
		if (x - 1 < 0 || y - 1 < 0 || x + 1 >= map.width || y + 1 >= map.height)
			print_error(4, NULL);
		map.map[y][x] = '3';
		floodfill(map, x, y + 1);
		floodfill(map, x, y - 1);
		floodfill(map, x + 1, y);
		floodfill(map, x - 1, y);
		floodfill(map, x + 1, y + 1);
		floodfill(map, x + 1, y - 1);
		floodfill(map, x - 1, y + 1);
		floodfill(map, x - 1, y - 1);
	}
	else if (map.map[y][x] != '1' && map.map[y][x] != '3')
		print_error(4, NULL);
}

void	empty_out(t_map map, t_vars *vars)
{
	int x;
	int y;
	int k;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.map[y][x] == '3')
				map.map[y][x] = '0';
			x++;
		}
		y++;
	}
	k = 0;
	while (k < vars->sprite_count)
	{
		map.map[(int)vars->sprite_array[k].y]
			[(int)vars->sprite_array[k].x] = '2';
		k++;
	}
}
