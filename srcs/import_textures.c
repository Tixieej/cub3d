/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   import_textures.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 13:40:51 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/30 14:28:52 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			file_extension(char *filename, char *filetype)
{
	int len;

	len = ft_strlen(filename);
	if (ft_strcmp(&filename[len - 4], filetype) == 0)
		return (1);
	return (0);
}

t_texture	*pick_texture(t_vars *vars, int id)
{
	if (id == 0)
		return (&vars->cub.wall_n);
	else if (id == 1)
		return (&vars->cub.wall_e);
	else if (id == 2)
		return (&vars->cub.wall_s);
	else if (id == 3)
		return (&vars->cub.wall_w);
	else
		return (&vars->cub.sprite);
}

void		import_images(t_vars *vars)
{
	int			i;
	t_texture	*tex;

	i = 0;
	while (i < 5)
	{
		tex = pick_texture(vars, i);
		import_image(vars, tex);
		i++;
	}
}

void		import_image(t_vars *vars, t_texture *tex)
{
	if (file_extension(tex->path, ".png") == 1)
		tex->img.img = mlx_png_file_to_image(vars->mlx, tex->path,
				&tex->width, &tex->height);
	else if (file_extension(tex->path, ".xpm") == 1)
		tex->img.img = mlx_xpm_file_to_image(vars->mlx, tex->path,
				&tex->width, &tex->height);
	else
		print_error(1, NULL);
	if (tex->img.img == NULL)
		print_error(1, NULL);
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bpp,
			&tex->img.line_length, &tex->img.endian);
}
