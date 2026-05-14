/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:01:47 by jnieders          #+#    #+#             */
/*   Updated: 2026/05/14 12:00:00 by jnieders         ###   ########.fr       */
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
}

static void	free_textures(t_mapinfo *map)
{
	if (map->no)
		free(map->no);
	map->no = NULL;
	if (map->so)
		free(map->so);
	map->so = NULL;
	if (map->we)
		free(map->we);
	map->we = NULL;
	if (map->ea)
		free(map->ea);
	map->ea = NULL;
}

void	free_data(t_data *d)
{
	free_textures(&d->map);
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
