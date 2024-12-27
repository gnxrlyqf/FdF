#ifndef FDF_H
#define FDF_H

#define DEG 57.295779513
#define MIN 480
#define MAX 720

#include <stdio.h>
#include <mlx.h>
#include <libft.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>

typedef struct mlx_instance_s {
	void *obj;
	void *window;
} mlx_instance_t;

typedef struct vector2_s {
	int x, y;
} vector2_t;

typedef struct fvector3_s {
	float x, y, z;
} fvector3_t;

typedef struct vertex3_s {
	fvector3_t pos;
	unsigned int color;
} vertex3_t;

typedef struct vertex2_s {
	vector2_t pos;
	unsigned int color;
} vertex2_t;

typedef struct matrix2_s {
	fvector3_t x, y, z;
} matrix2_t;

typedef struct color_s {
	int a, r, g, b;
} color_t;

typedef struct list_s {
	char *str;
	struct list_s *next;
} list_t;

typedef struct ftl_s {
	mlx_instance_t mlx;
	vector2_t dim;
	vertex3_t **arr;
	int mouse_down;
} ftl_t;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void draw_line(vertex2_t p1, vertex2_t p2, mlx_instance_t mlx, t_data *img);
fvector3_t mul_matrix(fvector3_t vec, matrix2_t mat);
vertex2_t project_point(vertex3_t point);
matrix2_t init_m(fvector3_t x, fvector3_t y, fvector3_t z);
fvector3_t init_v(float x, float y, float z);
int open_file(char *filename);
list_t *parse_file(int fd);
list_t	*new_node(char *str);
void	free_list_t(list_t **head);
vertex3_t **convert_to_coords(list_t *head);
size_t list_len(list_t *head);
int draw_fdf(ftl_t *vars_ig);
void draw_x(mlx_instance_t mlx, vertex3_t **arr, vector2_t dim, t_data *img);
void draw_y(mlx_instance_t mlx, vertex3_t **arr, vector2_t dim, t_data *img);
int mouse_motion(int x, int y, ftl_t *vars);
int mouse_down(int b, int x, int y, ftl_t *vars);
int mouse_up(int b, int x, int y, ftl_t *vars);
fvector3_t rotate_yaw(fvector3_t point, float angle);
fvector3_t rotate_pitch(fvector3_t point, float angle);
fvector3_t rotate_roll(fvector3_t point, float angle);
void rotate_model(vertex3_t ***arr, float angle, fvector3_t (*f)(fvector3_t, float), vector2_t dim);
vertex3_t **adjust_model(vertex3_t **arr, vector2_t dim, int *size);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int max(int a, int b);

#endif