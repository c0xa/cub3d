/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:30 by tblink            #+#    #+#             */
/*   Updated: 2021/02/12 19:56:30 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#define BUFFER_SIZE 7
//# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/errno.h>
# include "../libft/libft.h"

typedef struct	s_sprite {
	int	x;
	int	y;
}				t_sprite;

typedef struct	s_params { //структура для окна
	int		save_flag;
	int		width;
	int		height;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		floor;
	int		ceiling;
	char	**map;
	int		number_of_sprites;
}				t_params;

typedef struct	s_tex {
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_tex;

typedef struct	s_raycasting {
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	t_tex		*tex;
	int			tex_x;
	int			tex_y;
	double		tex_step;
	double		tex_pos;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;
}				t_raycasting;

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;


typedef struct	s_button { //структура для клавиш
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}				t_button;


typedef struct	s_point // структура для точки
{
	int			x;
	int			y;
}				  t_point;

typedef struct	s_tab {
	void			*mlx_p;
	void			*win_p;
	t_params		*params;
	t_button		*button;
	t_raycasting	*rayc;
	t_img			*frame_buf;
	t_tex			*n_tex;
	t_tex			*w_tex;
	t_tex			*s_tex;
	t_tex			*e_tex;
	t_tex			*sprite;
	t_sprite		*sprite_arr;
}				t_tab;

int		get_next_line(int fd, char **line);
int		writefile(int fd, char **line, char **bufs);
void	init_sprite (t_sprite *sprite);
void	init_button(t_button *button);
void	init_params(t_params *params);
int		game_start(t_tab *tab, char *map);
int		check_params(char *name_map, char *save_flag, t_params *params);
int		parse_file(char *name_file, t_params *params);
void	free_string_arr(char **string_arr);
int		parse_map(int fd, char **line, t_params *params);
int		main(int argc, char **argv);

#endif