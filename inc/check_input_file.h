/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_file.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:39:46 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/13 14:25:09 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_INPUT_FILE_H
# define CHECK_INPUT_FILE_H


/* ============= Check Input File =============*/
void	init_mapinfo(t_mapinfo *map);
int	check_input_file(t_data *d, int fd);

int	add_map_node(t_mapinfo *map, char *line);

/* ============= Check Elements =============*/
int	check_map_elements(t_mapinfo *map, char *line);

/* ============= Validate Map =============*/
int	parse_map_and_check(t_data *d);
int	validate_map(t_data *d);









#endif
