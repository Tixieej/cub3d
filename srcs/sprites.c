/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 13:46:20 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/30 16:33:48 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_last_sprite(t_vars *vars, int i, double *next, double *last)
{
	*next = ((vars->pos.x - vars->sprite_array[i].x) * (vars->pos.x
	- vars->sprite_array[i].x) + (vars->pos.y - vars->sprite_array[i].y)
	* (vars->pos.y - vars->sprite_array[i].y));
	*last = ((vars->pos.x - vars->sprite_array[i - 1].x) * (vars->pos.x
	- vars->sprite_array[i - 1].x) + (vars->pos.y - vars->sprite_array[i - 1].y)
	* (vars->pos.y - vars->sprite_array[i - 1].y));
}

int		sprite_translate(t_sprite_data *info, t_vars *vars)
{
	int		x;

	info->inv_det = 1.0 / (vars->plane.x * vars->dir.y - vars->dir.x *
		vars->plane.y);
	info->transform_x = (double)info->inv_det * (vars->dir.y * info->sprite_x
		- (double)vars->dir.x * info->sprite_y);
	info->transform_y = info->inv_det * (-vars->plane.y * info->sprite_x +
		vars->plane.x * info->sprite_y);
	info->sprite_screen_x = (int)(((double)vars->cub.screenwidth / 2.0) *
		(1.0 + info->transform_x / info->transform_y));
	info->sprite_height = abs((int)((double)vars->cub.screenheight /
		(info->transform_y)));
	info->sprite_start = -info->sprite_height / 2 + vars->cub.screenheight / 2;
	if (info->sprite_start < 0)
		info->sprite_start = 0;
	info->sprite_end = (int)((double)info->sprite_height / 2.0 +
		(double)vars->cub.screenheight / 2.0);
	if (info->sprite_end >= vars->cub.screenheight)
		info->sprite_end = vars->cub.screenheight - 1;
	info->sprite_width = abs((int)((double)vars->cub.screenwidth /
		(2.0 * info->transform_y)));
	x = -info->sprite_width / 2 + info->sprite_screen_x;
	if (x < 0)
		x = 0;
	return (x);
}

void	sprite_column(int x, t_sprite_data *info, t_vars *vars, t_data *img)
{
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;
	unsigned int	colour;

	tex_x = (int)(256 * (x - (-info->sprite_width / 2 + info->sprite_screen_x))
	* vars->cub.sprite.width / info->sprite_width) / 256;
	if (info->transform_y > 0 && x > 0 && x < vars->cub.screenwidth &&
	info->transform_y < vars->z_buffer[x])
	{
		y = info->sprite_start;
		while (y < info->sprite_end)
		{
			d = (y) * 256 - vars->cub.screenheight * 128 + info->sprite_height
				* 128;
			tex_y = ((d * vars->cub.sprite.height) / info->sprite_height) / 256;
			colour = my_mlx_pixel_get(vars->cub.sprite, &vars->cub.sprite.img,
			tex_x, tex_y);
			if ((colour & 0x00FFFFFF) != 0 && (colour & 0xFF000000) == 0)
				my_mlx_pixel_put(img, x, y, colour);
			y++;
		}
	}
}

void	sprites(t_vars *vars, t_data *img)
{
	t_sprite_data	info;
	int				i;
	int				x;
	int				x_end;

	sprite_sort(vars);
	i = 0;
	while (i < vars->sprite_count)
	{
		info.sprite_x = (double)vars->sprite_array[i].x - vars->pos.x;
		info.sprite_y = (double)vars->sprite_array[i].y - vars->pos.y;
		x = sprite_translate(&info, vars);
		x_end = info.sprite_width / 2 + info.sprite_screen_x;
		if (x_end >= vars->cub.screenwidth)
			x_end = vars->cub.screenwidth - 1;
		while (x < x_end)
		{
			sprite_column(x, &info, vars, img);
			x++;
		}
		i++;
	}
}
