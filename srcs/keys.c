/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 09:25:37 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/11 12:51:33 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forward(t_vars *vars)
{
	double speed;

	vars->move = 1;
	speed = vars->player.speed;
	if (vars->map.map[(int)vars->pos.y]
			[(int)(vars->pos.x + vars->dir.x * speed)] == '0')
		vars->pos.x += vars->dir.x * speed;
	if (vars->map.map[(int)(vars->pos.y + vars->dir.y * speed)]
			[(int)vars->pos.x] == '0')
		vars->pos.y += vars->dir.y * speed;
}

void	left(t_vars *vars)
{
	double speed;

	vars->move = 1;
	speed = vars->player.speed;
	if (vars->map.map[(int)(vars->pos.y - vars->dir.x * speed)]
				[(int)vars->pos.x] == '0')
		vars->pos.y -= vars->dir.x * speed;
	if (vars->map.map[(int)vars->pos.y]
				[(int)(vars->pos.x + vars->dir.y * speed)] == '0')
		vars->pos.x += vars->dir.y * speed;
}

void	backward(t_vars *vars)
{
	double speed;

	vars->move = 1;
	speed = vars->player.speed;
	if (vars->map.map[(int)(vars->pos.y)]
				[(int)(vars->pos.x - vars->dir.x * speed)] == '0')
		vars->pos.x -= vars->dir.x * speed;
	if (vars->map.map[(int)(vars->pos.y - vars->dir.y * speed)]
				[(int)(vars->pos.x)] == '0')
		vars->pos.y -= vars->dir.y * speed;
}

void	right(t_vars *vars)
{
	double speed;

	vars->move = 1;
	speed = vars->player.speed;
	if (vars->map.map[(int)(vars->pos.y + vars->dir.x * speed)]
				[(int)vars->pos.x] == '0')
		vars->pos.y += vars->dir.x * speed;
	if (vars->map.map[(int)vars->pos.y]
				[(int)(vars->pos.x - vars->dir.y * speed)] == '0')
		vars->pos.x -= vars->dir.y * speed;
}
