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

void	t_free_list(t_list **head)
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
		free(temp);
	}
	*head = NULL;
}
