/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:04:27 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/10 11:49:55 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

static void	add_node(t_list **head_list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buf);
		return ;
	}
	new_node->string = strdup_memcpy(buf, head_list);
	free(buf);
	new_node->next = NULL;
	if (*head_list == NULL)
		*head_list = new_node;
	else
	{
		last_node = *head_list;
		while (last_node->next != NULL)
		{
			last_node = last_node->next;
		}
		last_node->next = new_node;
	}
}

static char	*assemble_line(t_list **list, int pos_nl)
{
	char	*str;
	t_list	*temp;

	if (list == NULL || *list == NULL)
		return (NULL);
	if ((*list)->next == NULL && (*list)->string[0] == '\0')
	{
		gnl_free_list(list, 1);
		return (NULL);
	}
	str = NULL;
	temp = *list;
	while (temp->next != NULL)
	{
		str = gnl_strjoin(str, temp->string, -1);
		temp = temp->next;
	}
	str = gnl_strjoin(str, temp->string, pos_nl);
	if (pos_nl < 0)
		gnl_free_list(list, 1);
	else
		gnl_free_list(list, 0);
	return (str);
}

static char	*process_add_node(int readcount, t_list **list)
{
	char	*return_str;
	char	*rest;

	if (readcount < BUFFER_SIZE && nl_check(*list) == -1)
		return (assemble_line(list, -1));
	if (nl_check(*list) >= 0)
	{
		return_str = assemble_line(list, nl_check(*list));
		rest = strdup_memcpy((*list)->string + nl_check(*list) + 1, list);
		if (!rest)
			return (free((*list)->string), (*list)->string = NULL, NULL);
		free((*list)->string);
		(*list)->string = rest;
		return (return_str);
	}
	return (NULL);
}

static char	*return_existing_line(t_list **list)
{
	char	*return_str;
	char	*rest;

	return_str = assemble_line(list, nl_check(*list));
	rest = strdup_memcpy((*list)->string + nl_check(*list) + 1, list);
	if (!rest)
		return (free((*list)->string), (*list)->string = NULL, NULL);
	free((*list)->string);
	(*list)->string = rest;
	return (return_str);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	int				readcount;
	char			*buf;

	if (list && nl_check(list) >= 0)
		return (return_existing_line(&list));
	while (1)
	{
		if (fd < 0 || BUFFER_SIZE <= 0)
			return (NULL);
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		readcount = read(fd, buf, BUFFER_SIZE);
		if (readcount < 0)
			return (gnl_free_list(&list, 1), free(buf), NULL);
		buf[readcount] = '\0';
		if (readcount == 0)
			return (free(buf), assemble_line(&list, -1));
		add_node(&list, buf);
		if (nl_check(list) >= 0 || readcount < BUFFER_SIZE)
			return (process_add_node(readcount, &list));
	}
	return (NULL);
}
