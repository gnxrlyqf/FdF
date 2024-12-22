/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:31:32 by mchetoui          #+#    #+#             */
/*   Updated: 2024/11/03 02:43:55 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_list
{
	char			c;
	struct s_list	*next;
}				t_list;

size_t	ft_strlen(const char *str);
int		count_words(char *str, char *set);
int		contains_nl(char *str);
void	populate_list(t_list **head, char *str);
char	*get_next_line(int fd);
t_list	*add_node(t_list **head, char c);
void	free_list(t_list **head);
char	*make_str(t_list **head, int size);
int		listchr_len(t_list *head);
int		ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif
