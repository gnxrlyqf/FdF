/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:23:48 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:11:09 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	list_len(t_list *head)
{
	size_t	len;
	t_list	*curr;

	curr = head;
	len = 0;
	while (curr)
	{
		len++;
		curr = curr->next;
	}
	return (len);
}
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

void	free_t_list(t_list **head)
{
	t_list	*current;
	t_list	*temp;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->str);
		free(temp);
	}
	*head = NULL;
}
void free_model(t_vertex3 **arr, int size)
{
	int i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}

void throw_err(int code, char *str, t_list **head)
{
	if (str)
		free(str);
	if (head)
		free_t_list(head);
	if (code == 1)
		write(1, "Error 1 - Invalid input: invalid file extension\n", 48);
	if (code == 2)
		write(1, "Error 2 - Invalid input: wrong number of arguments\n", 51);
	if (code == 3)
		write(1, "Error 3 - Invalid file: file doesn't exist\n", 43);
	if (code == 4)
		write(1, "Error 4 - Invalid file: unknown character\n", 42);
	if (code == 5)
		write(1, "Error 5 - Invalid map: map too small\n", 37);
	if (code == 6)
		write(1, "Error 6 - Invalid map: map not rectangular\n", 43);
	exit(code);
}