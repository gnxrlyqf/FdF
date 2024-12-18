#include <mlx.h>

int main()
{
    void *mlx_instance = mlx_init();
    void *mlx_window = mlx_new_window(mlx_instance, 500, 500, "test");
    mlx_loop(mlx_instance);
}