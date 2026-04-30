/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:27:27 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/30 16:56:20 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

typedef struct s_minimap
{
    t_data  *d;
    int		tile_size;
    int		map_width;
    int		map_height;
    int		offset_x;
    int		offset_y;
    int		color_wall;
    int		color_floor;
    int		color_player;
    int     player_size;
}	t_minimap;

/* ============= Minimap Drawing =============*/
void	draw_minimap(t_data *d);

/* ============= Minimap Initialization =============*/
void	init_minimap(t_data *d, t_minimap *mm);

#endif