/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast_2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 12:58:32 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/23 13:46:22 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			create_trgb(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

void		calc_step_dist(t_vars *vars, t_dvector *raydir,
					t_dvector *delta_dist, t_ivector *map)
{
	if (raydir->x < 0)
	{
		vars->step.x = -1;
		vars->side_dist.x = (vars->pos.x - map->x) * delta_dist->x;
	}
	else
	{
		vars->step.x = 1;
		vars->side_dist.x = (map->x + 1.0 - vars->pos.x) * delta_dist->x;
	}
	if (raydir->y < 0)
	{
		vars->step.y = -1;
		vars->side_dist.y = (vars->pos.y - map->y) * delta_dist->y;
	}
	else
	{
		vars->step.y = 1;
		vars->side_dist.y = (map->y + 1.0 - vars->pos.y) * delta_dist->y;
	}
}

t_data		*get_new_image(t_vars *vars)
{
	if (vars->active == 1)
		return (&vars->img2);
	return (&vars->img1);
}

void		set_new_image(t_vars *vars)
{
	if (vars->active == 1)
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img2.img, 0, 0);
		vars->active = 2;
	}
	else
	{
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img1.img, 0, 0);
		vars->active = 1;
	}
}
