/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_release.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:38:57 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/11 12:52:10 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	check_keys(t_vars *vars)
{
	if (vars->key.w == 1)
		forward(vars);
	if (vars->key.a == 1)
		left(vars);
	if (vars->key.s == 1)
		backward(vars);
	if (vars->key.d == 1)
		right(vars);
	if (vars->key.left == 1)
		rotate_left(vars);
	if (vars->key.right == 1)
		rotate_right(vars);
}

int		keypress(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->key.w = 1;
	if (keycode == KEY_A)
		vars->key.a = 1;
	if (keycode == KEY_S)
		vars->key.s = 1;
	if (keycode == KEY_D)
		vars->key.d = 1;
	if (keycode == KEY_RIGHT)
		vars->key.right = 1;
	if (keycode == KEY_LEFT)
		vars->key.left = 1;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int		keyrelease(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->key.w = 0;
	if (keycode == KEY_A)
		vars->key.a = 0;
	if (keycode == KEY_S)
		vars->key.s = 0;
	if (keycode == KEY_D)
		vars->key.d = 0;
	if (keycode == KEY_RIGHT)
		vars->key.right = 0;
	if (keycode == KEY_LEFT)
		vars->key.left = 0;
	return (0);
}

void	rotate_left(t_vars *vars)
{
	t_dvector	old_dir;
	t_dvector	old_plane;
	double		rot_speed;

	vars->move = 1;
	rot_speed = vars->player.rot_speed;
	old_dir.x = vars->dir.x;
	vars->dir.x = vars->dir.x * cos(-rot_speed) - vars->dir.y * sin(-rot_speed);
	vars->dir.y = old_dir.x * sin(-rot_speed) + vars->dir.y * cos(-rot_speed);
	old_plane.x = vars->plane.x;
	vars->plane.x = vars->plane.x * cos(-rot_speed)
		- vars->plane.y * sin(-rot_speed);
	vars->plane.y = old_plane.x * sin(-rot_speed)
		+ vars->plane.y * cos(-rot_speed);
}

void	rotate_right(t_vars *vars)
{
	t_dvector	old_dir;
	t_dvector	old_plane;
	double		rot_speed;

	vars->move = 1;
	rot_speed = vars->player.rot_speed;
	old_dir.x = vars->dir.x;
	vars->dir.x = vars->dir.x * cos(rot_speed) - vars->dir.y * sin(rot_speed);
	vars->dir.y = old_dir.x * sin(rot_speed) + vars->dir.y * cos(rot_speed);
	old_plane.x = vars->plane.x;
	vars->plane.x = vars->plane.x * cos(rot_speed)
		- vars->plane.y * sin(rot_speed);
	vars->plane.y = old_plane.x * sin(rot_speed)
		+ vars->plane.y * cos(rot_speed);
}
