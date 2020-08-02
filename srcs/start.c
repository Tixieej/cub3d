/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/20 10:55:55 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/30 14:31:39 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			start_cub(t_vars *vars)
{
	vars->cub.wall_n.path = NULL;
	vars->cub.wall_e.path = NULL;
	vars->cub.wall_w.path = NULL;
	vars->cub.wall_s.path = NULL;
	vars->cub.wall_n.width = 0;
	vars->cub.wall_e.width = 0;
	vars->cub.wall_w.width = 0;
	vars->cub.wall_s.width = 0;
	vars->cub.wall_n.height = 0;
	vars->cub.wall_e.height = 0;
	vars->cub.wall_w.height = 0;
	vars->cub.wall_s.height = 0;
	vars->cub.wall_n.present = 0;
	vars->cub.wall_e.present = 0;
	vars->cub.wall_w.present = 0;
	vars->cub.wall_s.present = 0;
	vars->cub.ceiling = -1;
	vars->cub.floor = -1;
	vars->cub.screenwidth = -1;
	vars->cub.screenheight = -1;
	vars->map.map_begin = 0;
}

void			start_conditions(t_vars *vars)
{
	vars->key.w = 0;
	vars->key.a = 0;
	vars->key.s = 0;
	vars->key.d = 0;
	vars->key.left = 0;
	vars->key.right = 0;
	vars->player.speed = 0.08;
	vars->player.rot_speed = 0.05;
	vars->sprite_count = 0;
	vars->save = 0;
	start_cub(vars);
}

void			set_screensize(t_vars *vars)
{
	int		height;
	int		width;

	mlx_get_screen_size(vars->mlx, &width, &height);
	if (vars->cub.screenwidth > width)
		vars->cub.screenwidth = width;
	if (vars->cub.screenheight > height - 45)
		vars->cub.screenheight = height - 45;
}

void			initialize_image(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		print_error(23, NULL);
	if (vars->cub.screenwidth > 16384 || vars->cub.screenheight > 16384)
		print_error(7, NULL);
	vars->win = mlx_new_window(vars->mlx, vars->cub.screenwidth,
			vars->cub.screenheight, "Cub3D");
	if (!vars->win)
		print_error(23, NULL);
	vars->img1.img = mlx_new_image(vars->mlx, vars->cub.screenwidth,
			vars->cub.screenheight);
	if (!vars->img1.img)
		print_error(6, NULL);
	vars->img1.addr = mlx_get_data_addr(vars->img1.img, &vars->img1.bpp,
			&vars->img1.line_length, &vars->img1.endian);
	vars->img2.img = mlx_new_image(vars->mlx, vars->cub.screenwidth,
			vars->cub.screenheight);
	if (!vars->img2.img)
		print_error(6, NULL);
	vars->img2.addr = mlx_get_data_addr(vars->img2.img, &vars->img2.bpp,
			&vars->img2.line_length, &vars->img2.endian);
	vars->active = 2;
}
