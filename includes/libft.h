/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:31:32 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:09:53 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_list_gnl
{
	char				c;
	struct s_list_gnl	*next;
}				t_list_gnl;

size_t		ft_strlen(const char *str);
int			count_words(char *str, char *set);
int			contains_nl(char *str);
void		populate_list(t_list_gnl **head, char *str);
char		*get_next_line(int fd);
t_list_gnl	*add_node(t_list_gnl **head, char c);
void		free_list(t_list_gnl **head);
char		*make_str(t_list_gnl **head, int size);
int			listchr_len(t_list_gnl *head);
int			ft_atoi_ptr(char **str);
int			ft_isdigit(int c);
int			ft_atoi_base_ptr(char **str);
char		*ft_strchr(const char *str, int c);

#endif
