/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 15:56:28 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/30 16:13:07 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int			is_hit(t_vars *vars, t_dvector *delta_dist, t_ivector *map,
		t_calc *calc)
{
	if (vars->side_dist.x < vars->side_dist.y)
	{
		vars->side_dist.x += delta_dist->x;
		map->x += vars->step.x;
		calc->side = 0;
		if (vars->pos.x > map->x)
			calc->side = 2;
	}
	else
	{
		vars->side_dist.y += delta_dist->y;
		map->y += vars->step.y;
		calc->side = 1;
		if (vars->pos.y > map->y)
			calc->side = 3;
	}
	if (vars->map.map[map->y][map->x] == '1')
		calc->hit = 1;
	return (calc->hit);
}

double		where_hit(t_vars *vars, t_dvector *raydir, t_ivector *map,
			t_calc *calc)
{
	double	wall_x;

	if (calc->side == 0 || calc->side == 2)
	{
		calc->perpwalldist = (map->x - vars->pos.x + (1 - vars->step.x) / 2)
			/ raydir->x;
		wall_x = vars->pos.y + calc->perpwalldist * raydir->y;
	}
	else
	{
		calc->perpwalldist = (map->y - vars->pos.y + (1 - vars->step.y) / 2)
			/ raydir->y;
		wall_x = vars->pos.x + calc->perpwalldist * raydir->x;
	}
	if (calc->perpwalldist < 0.00001)
		calc->perpwalldist = 0.00001;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void		draw_start_end(t_calc *calc, int screenheight)
{
	calc->draw_start = screenheight / 2 - calc->wall_height / 2;
	if (calc->draw_start < 0)
		calc->draw_start = 0;
	calc->draw_end = screenheight / 2 + calc->wall_height / 2;
	if (calc->draw_end >= screenheight)
		calc->draw_end = screenheight - 1;
}

void		draw_column(t_vars *vars, int x, t_calc *calc)
{
	t_dvector	raydir;
	t_ivector	map;
	t_dvector	delta_dist;
	double		cam_x;

	cam_x = 2.0 * (double)x / (double)vars->cub.screenwidth - 1;
	raydir.x = vars->dir.x + vars->plane.x * cam_x;
	raydir.y = vars->dir.y + vars->plane.y * cam_x;
	map.x = (int)vars->pos.x;
	map.y = (int)vars->pos.y;
	delta_dist.x = fabs(1 / raydir.x);
	delta_dist.y = fabs(1 / raydir.y);
	calc_step_dist(vars, &raydir, &delta_dist, &map);
	calc->hit = 0;
	while (calc->hit == 0)
		calc->hit = is_hit(vars, &delta_dist, &map, calc);
	calc->wall_x = where_hit(vars, &raydir, &map, calc);
	vars->z_buffer[x] = calc->perpwalldist;
	calc->wall_height = (int)(vars->cub.screenheight / calc->perpwalldist);
	draw_start_end(calc, vars->cub.screenheight);
	textured_line(x, get_new_image(vars), vars, calc);
}

int			render_next_frame(t_vars *vars)
{
	int			x;
	t_calc		calc;

	x = 0;
	vars->z_buffer = (double *)malloc((sizeof(double)) * vars->cub.screenwidth);
	if (vars->z_buffer == NULL)
		print_error(23, NULL);
	check_keys(vars);
	if (vars->move == 0)
	{
		free(vars->z_buffer);
		return (0);
	}
	while (x < vars->cub.screenwidth)
	{
		draw_column(vars, x, &calc);
		x++;
	}
	sprites(vars, get_new_image(vars));
	if (!vars->save)
		set_new_image(vars);
	vars->move = 0;
	free(vars->z_buffer);
	return (0);
}
