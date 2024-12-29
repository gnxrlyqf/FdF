/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchetoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:06:00 by mchetoui          #+#    #+#             */
/*   Updated: 2024/12/28 14:09:26 by mchetoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define DEG 57.295779513
# ifndef SIZE
# 	define SIZE 720
# endif

# include <stdio.h>
# include <mlx.h>
# include <libft.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

typedef struct s_mlx_instance
{
	void	*obj;
	void	*window;
}				t_mlx_instance;

typedef struct s_vector2
{
	int	x;
	int	y;
}				t_vector2;

typedef struct s_fvector3
{
	float	x;
	float	y;
	float	z;
}				t_fvector3;

typedef struct s_vertex3
{
	t_fvector3		pos;
	unsigned int	col;
}				t_vertex3;

typedef struct s_vertex2
{
	t_vector2		pos;
	unsigned int	col;
}				t_vertex2;

typedef struct s_matrix3
{
	t_fvector3	x;
	t_fvector3	y;
	t_fvector3	z;
}				t_matrix3;


typedef struct s_color
{
	int	a;
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}				t_list;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	t_mlx_instance	mlx;
	t_vector2		dim;
	t_vector2		offset;
	float			scale;
	t_vertex3		**arr;
	int				right_down;
	int				left_down;
	int				type;
}				t_vars;

void		draw_line(t_vertex2 p1, t_vertex2 p2, t_data *img);
t_fvector3	mul_matrix3(t_fvector3 vec, t_matrix3 mat);
t_vertex2	project_point(t_vertex3 point, int type, float scale);
t_vertex2	project_isometric(t_vertex3 point, float scale);
t_fvector3	init_v3(float x, float y, float z);
int			open_file(char *filename);
t_list		*parse_file(int fd);
void		scan_file(int fd);
t_list		*new_node(char *str);
void		free_t_list(t_list **head);
t_vertex3	**convert_to_coords(t_list *head);
size_t		list_len(t_list *head);
int			draw_fdf(t_vars *vars_ig);
void		draw_x(t_vars *vars, t_data *img);
void		draw_y(t_vars *vars, t_data *img);
int			mouse_motion(int x, int y, t_vars *vars);
int			mouse_down(int b, int x, int y, t_vars *vars);
int			mouse_up(int b, int x, int y, t_vars *vars);
t_fvector3	rotate_x(t_fvector3 point, float angle);
t_fvector3	rotate_y(t_fvector3 point, float angle);
t_fvector3	rotate_z(t_fvector3 point, float angle);
void		rotate_model(t_vertex3 ***arr, float angle,
				t_fvector3 (*f)(t_fvector3, float), t_vector2 dim);
t_vertex3	**adjust_model(t_vertex3 **arr, t_vector2 dim);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			max(int a, int b);
t_color		int_to_color(int color);
int			max(int a, int b);
int			get_grad(int p1color, int p2color, int step, int steps);
int			close_window(t_vars *vars);
void		free_model(t_vertex3 **arr, int size);
void		throw_err(int code, char *str, t_list **head);
t_vars		init_vars(t_list *head);

#endif