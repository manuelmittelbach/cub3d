/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:15:28 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/10 11:49:32 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	gnl_free_list(t_list **list, int flag)
{
	t_list	*temp;

	if (list == NULL || *list == NULL)
		return ;
	while ((*list)->next != NULL)
	{
		temp = (*list)->next;
		free ((*list)->string);
		free(*list);
		*list = temp;
	}
	if (flag)
	{
		free((*list)->string);
		free(*list);
		*list = NULL;
	}
}

int	nl_check(t_list *last_node)
{
	int		i;

	while (last_node->next != NULL)
		last_node = last_node->next;
	i = 0;
	while (last_node->string[i])
	{
		if (last_node->string[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_strjoin(char *s1, char *s2, int pos_nl)
{
	char	*ptr;
	int		str_len_s2;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = strdup_memcpy("", NULL);
	str_len_s2 = ft_strlen(s2);
	if (pos_nl >= 0)
		str_len_s2 = pos_nl;
	ptr = malloc(ft_strlen(s1) + str_len_s2 + 2);
	if (!ptr)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	j = -1;
	while (++j <= str_len_s2)
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	if (s1 != NULL)
		free (s1);
	return (ptr);
}

char	*strdup_memcpy(char *s, t_list **list)
{
	char	*ptr;
	int		i;
	int		len;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (!ptr)
	{
		if (list)
			gnl_free_list(list, 1);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
