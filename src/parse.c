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

int	open_file(char *filename)
{
	char	*str;
	char	*ext;
	int		fd;

	ext = "fdf.";
	str = filename;
	if (!str || !*str)
		return (-1);
	str += ft_strlen(str);
	while (*ext)
		if (*(ext++) != *(--str))
			throw_err(1, NULL, NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		throw_err(3, NULL, NULL);
	scan_file(fd);
	return (open(filename, O_RDONLY));
}

void	scan_file(int fd)
{
	char	*str;
	char	*cpy;

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		cpy = str;
		while (*cpy)
		{
			if (!ft_strchr("0123456789 ,-abcdefABCDEFx\n\t\r", *cpy))
				throw_err(4, str, NULL);
			cpy++;
		}
		free(str);
	}
	close(fd);
}

t_list	*parse_file(int fd)
{
	t_list	*head;
	t_list	*curr;
	char	*str;
	int		word_count;

	str = get_next_line(fd);
	word_count = count_words(str, " \n");
	if (!str || !*str || word_count < 1)
		throw_err(5, str, NULL);
	head = new_node(str);
	curr = head;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (!*str || count_words(str, " \n") != word_count)
			throw_err(6, str, &head);
		curr->next = new_node(str);
		curr = curr->next;
	}
	if (!head->next)
		throw_err(5, str, &head);
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
		arr[i].pos.z = (float)ft_atoi_ptr(&str);
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
	if (dim.x < 2)
		throw_err(5, NULL, &head);
	arr = malloc(dim.y * sizeof(t_vertex3 *));
	i = 0;
	while (i < dim.y)
	{
		arr[i] = populate_arr(head, dim.x, i);
		head = head->next;
		i++;
	}
	return (arr);
}
