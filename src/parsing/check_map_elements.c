/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:35:47 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 14:24:26 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "check_input_file.h"
#include "get_next_line.h"

static int	set_texture_path(char *line, char **target, char *direction)
{
	if (ft_strncmp(line, direction, 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
	{
		if (*target)
			return (1);
		*target = ft_strtrim(line + 2, " \t\n");
		if (!*target)
			return (1);
		return (0);
	}
	return (1);
}

static int  is_digit_str(char *str)
{
    while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
        str++;
    if (!*str || *str < '0' || *str > '9')
        return (1);
    while (*str >= '0' && *str <= '9')
        str++;
    while (*str && (*str == ' ' || *str == '\n' || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '\0')
		return (0);
	else
		return (1);
}

static int	count_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static int	set_colors(char *line, int *color)
{
	int		i;
	char	**rgb;

	if (color[1] != -1)
		return (1);
	if (count_commas(line) != 2)
		return (1);
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_str_arr(rgb), 1);
	i = 0;
	while (i < 3)
	{
		if (is_digit_str(rgb[i]))
			return (free_str_arr(rgb), 1);
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255)
			return (free_str_arr(rgb), 1);
		i++;
	}
	free_str_arr(rgb);
	return (0);
}


/*
aktuell koennen wir nur eine allgemeine error meldung geben, weil es drei 
Zustaende gibt bei dem wir hier 1 also error returnen:
1. Malloc Error
2. Eine Himmelsrichtung hat bereits einen Wert, also ein Duplikat
3. Die Zeile war keine emptyline und hat einen Inhalt der sich nicht zuordnen lies
Das sind alles fehler und fuehren direkt zum Abbruch des Programms. Spaeter koennen
wir dann aber nur sehr allgemein error melden.
*/
int	check_map_elements(t_mapinfo *map, char *line)
{
	while (*line && (*line == ' ' || (*line >= 9 && *line <= 13)))
		line++;
	if (!set_texture_path(line, &map->NO, "NO"))
		return (0);
	if (!set_texture_path(line, &map->SO, "SO"))
		return (0);
	if (!set_texture_path(line, &map->WE, "WE"))
		return (0);
	if (!set_texture_path(line, &map->EA, "EA"))
		return (0);
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (!set_colors(line + 1, map->F))
			return (0);
	}
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (!set_colors(line + 1, map->C))
			return (0);
	}
	return (1);
}
