/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:36:56 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 17:13:03 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "check_input_file.h"

int check_filename(char *fn)
{
	int	strlen;

	strlen = ft_strlen(fn);

	if (strlen >= 5)
	{
		if (!ft_strcmp(".cub", fn + strlen - 4))
			return (0);
	}
	return (1);
}

void	init_mapinfo(t_mapinfo *map)
{
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
	map->EA = NULL;
	map->F[0] = -1;
	map->F[1] = -1;
	map->F[2] = -1;
	map->C[0] = -1;
	map->C[1] = -1;
	map->C[2] = -1;
	map->all_elements_found = false;
	map->map_list = NULL;
	map->map_arr = NULL;
}

void	init_data(t_data *d)
{
	d->mlx = NULL;
	d->win = NULL;
	
	ft_memset(&d->screen, 0, sizeof(t_img));
	ft_memset(d->tex, 0, sizeof(d->tex));

    // Parsing Informationen
	init_mapinfo(&d->map);
	
	// Spieler-Werte initialisieren
	d->pos_x = 0.0;
	d->pos_y = 0.0;
	d->dir_x = 0.0;
	d->dir_y = 0.0;
	d->plane_x = 0.0;
	d->plane_y = 0.0;
}




int main(int ac, char **av)
{
	int			fd;
	t_data		d;

	// Input Check und Filename Validierung
	if (ac != 2)
		return (printf("Error\nUsage: ./programmname <filename>\n"), 1);
	
	if (check_filename(av[1]))
		return (printf("Error\nInvalid filename\n"), 1);

	// Open Filename
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nOpening file\n"), 1);

	init_data(&d);
		
	// Check Map
	if (check_input_file(&d, fd))
		return (printf("Error\nInvalid File\n"), 1);


	if (init_mlx(&d))
		return (printf("Error\nMlx init failed\n"), 1);

	mlx_loop(d.mlx);
		
	return (0);
}

