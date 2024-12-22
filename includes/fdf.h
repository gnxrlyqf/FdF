#ifndef FDF_H
#define FDF_H

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

typedef struct vector3_s {
	int x, y, z;
} vector3_t;

typedef struct fvector3_s {
	float x, y, z;
} fvector3_t;

typedef struct matrix2_s {
	fvector3_t x, y, z;
} matrix2_t;

typedef struct list_s {
	char *str;
	struct list_s *next;
} list_t;

void draw_line(vector2_t p1, vector2_t p2, mlx_instance_t mlx, int color);
fvector3_t mul_matrix(fvector3_t vec, matrix2_t mat, float coeff);
vector2_t project_point(fvector3_t point);
matrix2_t init_m(fvector3_t x, fvector3_t y, fvector3_t z);
fvector3_t init_v(float x, float y, float z);
int open_file(char *filename);
list_t *parse_file(int fd);
list_t	*new_node(char *str);
void	free_list_t(list_t **head);
fvector3_t **convert_to_coords(list_t *head);
size_t list_len(list_t *head);
void draw_fdf(mlx_instance_t mlx, fvector3_t **arr, vector2_t dim);
void draw_x(mlx_instance_t mlx, fvector3_t **arr, vector2_t dim);
void draw_y(mlx_instance_t mlx, fvector3_t **arr, vector2_t dim);

#endif