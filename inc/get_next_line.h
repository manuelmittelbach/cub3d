/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:35:47 by jnieders          #+#    #+#             */
/*   Updated: 2026/05/14 12:28:00 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include "cub3d.h"

/* ************************************************************************** */
/*                               Core Functions                               */
/* ************************************************************************** */
char	*get_next_line(int fd);

/* ************************************************************************** */
/*                               Utils                                        */
/* ************************************************************************** */
void	gnl_free_list(t_list **list, int flag);
int		nl_check(t_list *last_node);
char	*gnl_strjoin(char *s1, char *s2, int pos_nl);
char	*strdup_memcpy(char *s, t_list **list);

#endif