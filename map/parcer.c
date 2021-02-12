#include "mlx.h"

int main()
{
	void    *m = mlx_init();
	void    *vm  = mlx_new_window(m, 1000, 2000, "t");
	mlx_loop(m);
	return (0);
}