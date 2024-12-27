#include "fdf.h"
#include <libft.h>

list_t	*new_node(char *str)
{
	list_t	*new;

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

void	free_list_t(list_t **head)
{
	list_t	*current;
	list_t	*temp;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
}

int open_file(char *filename)
{
	char *str;
	char *ext = "fdf.";

	str = filename;
	if (!str || !*str)
		return (-1);
	str += ft_strlen(str);
	while (*ext)
		if (*(ext++) != *(--str))
			return (-1);
	return (open(filename, O_RDONLY));
}

list_t *parse_file(int fd)
{
	list_t *head;
	list_t *curr;
	char	*str;
	int term_count;

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
			return (free(str), free_list_t(&head), NULL);
		curr->next = new_node(str);
		curr = curr->next;
	}
	return (head);
}

size_t list_len(list_t *head)
{
	size_t len;
	list_t *curr;

	curr = head;
	len = 0;
	while (curr)
	{
		len++;
		curr = curr->next;
	}
	return (len);
}

vertex3_t *populate_arr(list_t *node, int size, int y)
{
	vertex3_t *arr;
	char *str;
	int i;

	arr = malloc(size * sizeof(vertex3_t));
	str = node->str;
	i = 0;
	while (i < size)
	{
		arr[i].color = 0x00FFFFFF;
		arr[i].pos.y = y;
		arr[i].pos.x = i;
		arr[i].pos.z = ft_atoi_ptr(&str);
		if (*str == ',')
			arr[i].color = ft_atoi_base_ptr(&str);
		i++;
	}
	return (arr);
}

vertex3_t **convert_to_coords(list_t *head)
{
	vertex3_t	**arr;
	vector2_t	dim;
	int			i;

	dim.x = count_words(head->str, " ");
	dim.y = list_len(head);
	arr = malloc(dim.y * sizeof(vertex3_t *));
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