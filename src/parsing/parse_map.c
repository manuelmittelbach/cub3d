/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:01:00 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 13:57:39 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "check_input_file.h"
#include "get_next_line.h"

int	add_map_node(t_mapinfo *map, char *line)
{
	t_list	*new_node;
	t_list	*last;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (1);
	new_node->string = ft_strdup(line);
	if (!new_node->string)
		return (free(new_node), 1);
	new_node->next = NULL;
	if (map->map_list == NULL)
		map->map_list = new_node;
	else
	{
		last = map->map_list;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	return (0);
}

static int	count_map_nodes(t_list *list)
{
	int	c;

	c = 0;
	while (list)
	{
		c++;
		list = list->next;
	}
	return (c);
}

int	parse_map_and_check(t_data *d)
{
	int		n_lines;
	int		i;
	t_list	*temp;

	n_lines = count_map_nodes(d->map.map_list);
	if (n_lines == 0)
		return (free_data(d), 1);
	d->map.map_arr = malloc(sizeof(char *) * (n_lines + 1));
	if (!d->map.map_arr)
		return (free_data(d), 1);
	i = 0;
	while (d->map.map_list)
	{
		d->map.map_arr[i++] = d->map.map_list->string;
		temp = d->map.map_list;
		d->map.map_list = d->map.map_list->next;
		free(temp);
	}
	d->map.map_arr[i] = NULL;
	if (validate_map(d))
		return (free_data(d), 1);
	return (0);
}
