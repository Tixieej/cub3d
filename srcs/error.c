/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 10:54:55 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/27 11:45:38 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

void	print_error(int e_type, char *line)
{
	if (line)
		free(line);
	write(1, "\033[0;31mError\n\033[0m", 17);
	if (e_type == 0)
		write(1, "wrong argument, try '--save'.\n", 30);
	else if (e_type == 1)
		write(1, "incorrect texture.\n", 19);
	else if (e_type == 2)
		write(1, "cubfile doesn't exist.\n", 23);
	else if (e_type == 3)
		write(1, "double line.\n", 13);
	else if (e_type == 4)
		write(1, "map is open.\n", 13);
	else if (e_type == 5)
		write(1, "unknown identifier in cubfile.\n", 31);
	else if (e_type == 6)
		write(1, "no memory for image.\n", 21);
	else if (e_type == 7)
		write(1, "invalid resolution.\n", 20);
	else if (e_type >= 8 && e_type <= 18)
		print_error_2(e_type);
	else
		print_error_3(e_type);
	exit(1);
}

void	print_error_2(int e_type)
{
	if (e_type == 8)
		write(1, "invalid map.\n", 13);
	else if (e_type == 9)
		write(1, "invalid colour.\n", 16);
	else if (e_type == 10)
		write(1, "NO line is missing from cubfile.\n", 33);
	else if (e_type == 11)
		write(1, "EA line is missing from cubfile.\n", 33);
	else if (e_type == 12)
		write(1, "SO line is missing from cubfile.\n", 33);
	else if (e_type == 13)
		write(1, "WE line is missing from cubfile.\n", 33);
	else if (e_type == 14)
		write(1, "C line is missing from cubfile.\n", 32);
	else if (e_type == 15)
		write(1, "F line is missing from cubfile.\n", 32);
	else if (e_type == 16)
		write(1, "no starting position found.\n", 28);
	else if (e_type == 17)
		write(1, "R line is missing from cubfile.\n", 32);
	else if (e_type == 18)
		write(1, "map missing from cubfile.\n", 26);
}

void	print_error_3(int e_type)
{
	if (e_type == 19)
		write(1, "S line is missing from cubfile.\n", 32);
	else if (e_type == 20)
		write(1, "double starting position found.\n", 32);
	else if (e_type == 21)
		write(1, "no text aloud after map.\n", 25);
	else if (e_type == 22)
		write(1, "too many arguments.\n", 20);
	else if (e_type == 23)
		write(1, "no memory for malloc.\n", 22);
	else if (e_type == 24)
		write(1, "wrong argument, not a .cub file.\n", 34);
	else if (e_type == 25)
		write(1, "screenshot not possible.\n", 25);
	else if (e_type == 26)
		write(1, "get_next_line could not read file.\n", 36);
}
