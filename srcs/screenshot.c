/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screenshot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 12:10:13 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/30 16:33:40 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

void		bit_converter(unsigned char *header, int value)
{
	int		and;
	int		shift;
	int		i;

	i = 0;
	shift = 0;
	and = 255;
	while (i < 4)
	{
		header[i] = (value & and) >> shift;
		shift += 8;
		and <<= 8;
		i++;
	}
}

unsigned int	my_mlx_pixel_get_screenshot(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int*)dst);
}

void		image_body(t_vars *vars, int fd)
{
	int				padding;
	int				x;
	int				y;
	unsigned int	colour;
	int				ret;

	y = vars->cub.screenheight - 1;
	padding = (4 - (3 * vars->cub.screenwidth) % 4) % 4;
	while (y >= 0)
	{
		x = 0;
		while (x < vars->cub.screenwidth)
		{
			colour = my_mlx_pixel_get_screenshot(get_new_image(vars), x, y);
			ret = write(fd, &colour, 3);
			if (ret == -1)
				print_error(6, NULL);
			x++;
		}
		write(fd, "\0\0\0", padding);
		y--;
	}
}

void		image_header(t_vars *vars, int fd)
{
	int				i;
	int				padding;
	unsigned char	header[54];

	i = 2;
	while (i < 54)
	{
		header[i] = 0;
		i++;
	}
	padding = (4 - (3 * vars->cub.screenwidth) % 4) % 4;
	bit_converter(header, 66);
	bit_converter(header + 1, 77);
	bit_converter(header + 2, (54 + vars->cub.screenheight *
				(vars->cub.screenwidth + padding) * 3));
	bit_converter(header + 10, 54);
	bit_converter(header + 14, 40);
	bit_converter(header + 18, vars->cub.screenwidth);
	bit_converter(header + 22, vars->cub.screenheight);
	bit_converter(header + 26, 1);
	bit_converter(header + 28, 24);
	write(fd, header, 54);
}

void		make_screenshot(t_vars *vars)
{
	int		fd;

	fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		print_error(25, NULL);
	image_header(vars, fd);
	image_body(vars, fd);
}
