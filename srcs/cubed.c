/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cubed.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 09:21:25 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/30 13:06:43 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>//

int				close_window(void)
{
	exit(0);
	return (1);
}

void			open_window(t_vars *vars)
{
	mlx_loop_hook(vars->mlx, &render_next_frame, vars);
	mlx_hook(vars->win, CLOSE_WINDOW, 1L << 17, close_window, vars);
	mlx_loop(vars->mlx);
}

void			run_game(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, keypress, vars);
	mlx_hook(vars->win, 3, 1L << 1, keyrelease, vars);
	open_window(vars);
}

int				main(int argc, char **argv)
{
	t_vars	vars;

	start_conditions(&vars);
	read_cubfile(argv, &vars);
	if (argc > 3)
		print_error(22, NULL);
	if (argc == 2)
		set_screensize(&vars);
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save") != 0)
			print_error(0, NULL);
	}
	initialize_image(&vars);
	import_images(&vars);
	vars.move = 1;
	if (argc == 3)
	{
		vars.save = 1;
		render_next_frame(&vars);
		make_screenshot(&vars);
	}
	else
		run_game(&vars);
}
