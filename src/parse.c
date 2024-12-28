/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:43 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:11:01 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <libft.h>

t_list	*new_node(char *str)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

int	open_file(char *filename)
{
	char	*str;
	char	*ext;

	ext = "fdf.";
	str = filename;
	if (!str || !*str)
		return (-1);
	str += ft_strlen(str);
	while (*ext)
		if (*(ext++) != *(--str))
			return (-1);
	return (open(filename, O_RDONLY));
}

t_list	*parse_file(int fd)
{
	t_list	*head;
	t_list	*curr;
	char	*str;
	int		term_count;

	str = get_next_line(fd);
	term_count = count_words(str, " ");
	if (!str || !*str || term_count < 1)
		return (free(str), NULL);
	head = new_node(str);
	curr = head;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (!*str || count_words(str, " ") != term_count)
			return (free(str), t_free_list(&head), NULL);
		curr->next = new_node(str);
		curr = curr->next;
	}
	return (head);
}

t_vertex3	*populate_arr(t_list *node, int size, int y)
{
	t_vertex3	*arr;
	char		*str;
	int			i;

	arr = malloc(size * sizeof(t_vertex3));
	str = node->str;
	i = 0;
	while (i < size)
	{
		arr[i].col = 0x00FFFFFF;
		arr[i].pos.y = y;
		arr[i].pos.x = i;
		arr[i].pos.z = ft_atoi_ptr(&str);
		if (*str == ',')
			arr[i].col = ft_atoi_base_ptr(&str);
		i++;
	}
	return (arr);
}

t_vertex3	**convert_to_coords(t_list *head)
{
	t_vertex3	**arr;
	t_vector2	dim;
	int			i;

	dim.x = count_words(head->str, " ");
	dim.y = list_len(head);
	arr = malloc(dim.y * sizeof(t_vertex3 *));
	i = 0;
	while (i < dim.y)
	{
		arr[i] = populate_arr(head, dim.x, i);
		head = head->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
