/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atoi_colour.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <rde-vrie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 13:27:27 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/21 14:07:01 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_atoi_colour(const char *str, int *index)
{
	long	nb;

	nb = 0;
	if (!(str[*index] >= '0' && str[*index] <= '9'))
		return (-1);
	while (str[*index] != '\0' && str[*index] >= '0' && str[*index] <= '9')
	{
		nb = nb * 10 + str[*index] - '0';
		(*index)++;
	}
	return (nb);
}
