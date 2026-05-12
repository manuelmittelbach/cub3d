/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:01:47 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/01 18:02:15 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	if (!str_arr)
		return ;
	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
	return ;
}

void	free_data(t_data *d)
{
	if (d->map.NO)
	{
		free(d->map.NO);
		d->map.NO = NULL;
	}
	if (d->map.SO)
	{
		free(d->map.SO);
		d->map.SO = NULL;
	}
	if (d->map.WE)
	{
		free(d->map.WE);
		d->map.WE = NULL;
	}
	if (d->map.EA)
	{
		free(d->map.EA);
		d->map.EA = NULL;
	}
	if (d->map.map_list)
		gnl_free_list(&d->map.map_list, 1);
	if (d->map.map_arr)
	{
		free_str_arr(d->map.map_arr);
		d->map.map_arr = NULL;
	}
}

int	get_rgb_color(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
