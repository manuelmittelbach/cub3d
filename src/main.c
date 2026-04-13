/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:36:56 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 14:36:28 by jnieders         ###   ########.fr       */
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




void testing_function(t_data *d)
{
	int	i;

	printf("\n==========================================\n");
	printf("   🛠️  CUB3D PARSER - STATUS BERICHT  🛠️\n");
	printf("==========================================\n\n");

	printf("[1] TEXTUREN:\n");
	printf("  NO: [%s]\n", d->map.NO ? d->map.NO : "NULL");
	printf("  SO: [%s]\n", d->map.SO ? d->map.SO : "NULL");
	printf("  WE: [%s]\n", d->map.WE ? d->map.WE : "NULL");
	printf("  EA: [%s]\n", d->map.EA ? d->map.EA : "NULL");
	printf("\n");

	printf("[2] FARBEN (RGB):\n");
	printf("  Floor (F)   : %d, %d, %d\n", d->map.F[0], d->map.F[1], d->map.F[2]);
	printf("  Ceiling (C) : %d, %d, %d\n", d->map.C[0], d->map.C[1], d->map.C[2]);
	printf("\n");

	printf("[3] SPIELER DATEN:\n");
	printf("  Start-Position (x, y) : %f, %f\n", d->pos_x, d->pos_y);
	printf("  Blickrichtung  (x, y) : %f, %f\n", d->dir_x, d->dir_y);
	printf("  Kamera-Ebene   (x, y) : %f, %f\n", d->plane_x, d->plane_y);
	printf("\n");

	printf("[4] MAP ARRAY:\n");
	i = 0;
	if (d->map.map_arr)
	{
		while (d->map.map_arr[i])
		{
			printf("  [%02d]: %s\n", i, d->map.map_arr[i]);
			i++;
		}
	}
	else
	{
		printf("  [ERROR] map_arr ist NULL!\n");
	}
	printf("\n==========================================\n");
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
	
	testing_function(&d);

	if (init_mlx(&d))
		return (printf("Error\nMlx init failed\n"), 1);


		
	return (0);
}

