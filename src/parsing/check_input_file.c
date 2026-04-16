/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:35:47 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 17:29:31 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "check_input_file.h"
#include "get_next_line.h"

static int	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (1);	
}

static void	all_elements_found(t_mapinfo *map)
{
	if (map->NO && map->SO && map->WE && map->EA \
		&& map->C[0] != -1 && map->F[0] != -1)
	{
		map->all_elements_found = true;
		return ;
	}
}

/*
Wir brauchen noch eine free function die in mapinfo aufraeumt, das kann in allen
returns eintreten, weil dann immer ein teil schon mit strtrim in die texturenpfade
gemalloced sein kann. Wir brauchen eine aehnliche function wie das hier:

void	free_mapinfo(t_mapinfo *map)
{
	if (map->NO)
		free(map->NO);
	if (map->SO)
		free(map->SO);
	if (map->WE)
		free(map->WE);
	if (map->EA)
		free(map->EA);
	if (map->map_list)
		gnl_free_list(&map->map_list, 1);
}
*/

int	check_input_file(t_data *d, int fd)
{
	char	*line;
	bool	map_ended;

	map_ended = false;
	while ((line = get_next_line(fd)))
	{
		if (!is_empty_line(line)) 
		{
			if (d->map.map_list != NULL)
				map_ended = true;
			free(line);
			continue ;
		}
		if (d->map.all_elements_found == false)
		{
			if (check_map_elements(&d->map, line))
				return (free(line), 1); // free_mapinfo() einbauen
			all_elements_found(&d->map);
		}
		else
		{
			if (map_ended == true)
				return (free(line), gnl_free_list(&d->map.map_list, 1), 1);
			if (add_map_node(&d->map, line))
				return (free(line), gnl_free_list(&d->map.map_list, 1), 1);
		}
		free(line);
	}
	return (parse_map_and_check(d));
}
