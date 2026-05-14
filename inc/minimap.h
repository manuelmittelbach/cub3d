/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:38:53 by jnieders          #+#    #+#             */
/*   Updated: 2026/05/14 12:20:00 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

/* ************************************************************************** */
/*                                  Structure                                 */
/* ************************************************************************** */

typedef struct s_minimap
{
	t_data	*d;
	int		tile_size;
	int		player_size;
	int		map_width;
	int		map_height;
	int		offset_x;
	int		offset_y;
	int		color_wall;
	int		color_floor;
	int		color_player;
}	t_minimap;

/* ************************************************************************** */
/*                                  Functions                                 */
/* ************************************************************************** */
void	init_minimap(t_data *d, t_minimap *mm);
void	draw_minimap(t_data *d);

#endif