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

void	free_map_and_list(t_mapinfo *map)
{
	if (map->NO)
		free(map->NO);
	if (map->SO)
		free(map->SO);
	if (map->WE)
		free(map->WE);
	if (map->EA)
		free(map->EA);
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
	map->EA = NULL;
	if (map->map_list)
		gnl_free_list(&map->map_list, 1);
}

int	get_rgb_color(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
