/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 11:04:35 by rixt          #+#    #+#                 */
/*   Updated: 2020/07/30 16:26:15 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	my_mlx_pixel_get(t_texture texture, t_data *data, int x, int y)
{
	char	*dst;

	if (y >= texture.width)
		y = texture.width - 1;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int*)dst);
}

t_texture		texture_on_side(t_vars *vars, int side)
{
	t_texture texture;

	if (side == 0)
		texture = vars->cub.wall_e;
	else if (side == 1)
		texture = vars->cub.wall_s;
	else if (side == 2)
		texture = vars->cub.wall_w;
	else
		texture = vars->cub.wall_n;
	return (texture);
}

void			textured_line(int x, t_data *img, t_vars *vars, t_calc *calc)
{
	int				y;
	unsigned int	colour;
	t_texture		texture;
	double			ratio;

	texture = texture_on_side(vars, calc->side);
	ratio = (double)calc->wall_height / (double)texture.height;
	calc->wall_x *= (double)texture.width;
	y = draw_ceiling(vars, img, calc, x);
	while (y <= calc->draw_end)
	{
		colour = my_mlx_pixel_get(texture, &texture.img, (int)calc->wall_x,
		(int)((y - (vars->cub.screenheight / 2 - calc->wall_height / 2)) /
		ratio));
		my_mlx_pixel_put(img, x, y, colour);
		y++;
	}
	while (y < vars->cub.screenheight)
	{
		my_mlx_pixel_put(img, x, y, vars->cub.floor);
		y++;
	}
}

int				draw_ceiling(t_vars *vars, t_data *img, t_calc *calc, int x)
{
	int y;

	y = 0;
	while (y < calc->draw_start)
	{
		my_mlx_pixel_put(img, x, y, vars->cub.ceiling);
		y++;
	}
	return (y);
}
