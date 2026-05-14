/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:23:22 by jnieders          #+#    #+#             */
/*   Updated: 2026/05/14 11:41:00 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "check_input_file.h"

static int	character_check(char **arr)
{
	int		i;
	int		j;
	bool	duplicates_flag;

	duplicates_flag = false;
	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (!ft_strchr(" 01NSEW", arr[i][j]))
				return (1);
			if (ft_strchr("NSEW", arr[i][j]))
			{
				if (duplicates_flag == true)
					return (1);
				duplicates_flag = true;
			}
			j++;
		}
		i++;
	}
	return (duplicates_flag == false);
}

static char	**copy_map(char **map_arr)
{
	char	**copy;
	int		i;
	int		height;

	height = 0;
	while (map_arr[height])
		height++;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map_arr[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			return (free(copy), NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	flood_fill(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (1);
	if (map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (0);
	map[y][x] = 'F';
	if (flood_fill(map, x, y + 1, height)
		|| flood_fill(map, x, y - 1, height)
		|| flood_fill(map, x + 1, y, height)
		|| flood_fill(map, x - 1, y, height))
		return (1);
	return (0);
}

int	validate_map(t_data *d)
{
	int		height;
	char	**copy_map_arr;

	if (character_check(d->map.map_arr))
		return (1);
	set_player_data(d);
	height = 0;
	while (d->map.map_arr[height])
		height++;
	copy_map_arr = copy_map(d->map.map_arr);
	if (!copy_map_arr)
		return (1);
	if (flood_fill(copy_map_arr, (int)d->pos_x, (int)d->pos_y, height))
		return (free_str_arr(copy_map_arr), 1);
	free_str_arr(copy_map_arr);
	return (0);
}
