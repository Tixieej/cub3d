/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 13:50:12 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/23 13:50:56 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap(t_dvector *a, t_dvector *b)
{
	t_dvector tmp;

	tmp.x = a->x;
	tmp.y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = tmp.x;
	b->y = tmp.y;
}

void	sprite_sort(t_vars *vars)
{
	int		n;
	int		i;
	int		swapped;
	double	dist_next;
	double	dist_last;

	n = vars->sprite_count;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 1;
		while (i < n)
		{
			next_last_sprite(vars, i, &dist_next, &dist_last);
			if (dist_last < dist_next)
			{
				swap(&(vars->sprite_array[i - 1]), &(vars->sprite_array[i]));
				swapped = 1;
			}
			i++;
		}
		n = n - 1;
	}
}
