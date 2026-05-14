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
	if (map->no && map->so && map->we && map->ea
		&& map->c[0] != -1 && map->f[0] != -1)
	{
		map->all_elements_found = true;
		return ;
	}
}

static int	process_line(t_data *d, char *line, bool *map_ended)
{
	if (!is_empty_line(line))
	{
		if (d->map.map_list != NULL)
			*map_ended = true;
		return (0);
	}
	if (d->map.all_elements_found == false)
	{
		if (check_map_elements(&d->map, line))
			return (1);
		all_elements_found(&d->map);
	}
	else
	{
		if (*map_ended == true || add_map_node(&d->map, line))
			return (1);
	}
	return (0);
}

int	check_input_file(t_data *d, int fd)
{
	char	*line;
	bool	map_ended;

	map_ended = false;
	line = get_next_line(fd);
	while (line)
	{
		if (process_line(d, line, &map_ended))
		{
			free(line);
			free_data(d);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (parse_map_and_check(d));
}
