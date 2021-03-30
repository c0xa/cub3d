/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblink <tblink@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 19:55:30 by tblink            #+#    #+#             */
/*   Updated: 2021/03/26 20:32:42 by tblink           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "stdio.h"
# include "fcntl.h"
# include "math.h"
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# define BUFFER_SIZE 7

typedef struct	s_sprite {
	int	x;
	int	y;
}				t_sprite;

typedef struct	s_params {
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
	int		height_map;
	int		width_map;
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

typedef struct	s_button {
	int		w;
	int		a;
	int		s;
	int		d;
	int		space_for_mini_map;
	int		left;
	int		right;
}				t_button;

typedef struct	s_tab {
	void			*mlx_p;
	void			*win_p;
	int				map_size;
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

int				get_next_line(int fd, char **line);
int				writefile(int fd, char **line, char **bufs);
int				main(int argc, char **argv);
int				check_params(char *name_map, char *save_flag, t_params *params);
int				parse_file(char *map, t_params *params);
void			init_params(t_params *params);
void			init_button(t_button *button);
void			init_sprite (t_tab *tab);
void			init_textures(t_tab *tab);
int				parse_parameter(int fd, t_params *params, int flag, int i);
int				set_resolution(char **buf, t_params *params);
int				set_texture(int flag, char **buf, t_params *params);
int				convert_map(int fd, char **line, t_params *params, int flag);
int				set_color(int flag, char **buf, t_params *params);
void			calculate_pos_wall(t_tab *tab, t_raycasting *rayc, int height);
int				check_error_map(t_params *params, int count_position,
				int i, int j);
void			draw_and_inital(t_tab *tab);
int				check_button_release(int but, t_tab *tab);
int				check_button_press(int but, t_tab *tab);
int				exit_game(void *arg);
void			engine_main(t_raycasting *rayc, int x, int width);
void			where_is_playes(t_tab *tab, int i, int j);
void			add_texture(t_tab *tab);
void			hit_to_wall(t_raycasting *rayc, char **map);
void			calculate_draw(t_raycasting *rayc, int height);
void			calculate_wall(t_raycasting *rayc, t_tab *tab, int height);
void			change_position_and_camera(t_tab *tab);
void			motion_right(t_tab *tab);
void			motion_left(t_tab *tab);
void			motion_w_s(t_tab *tab, int direction);
void			motion_a_d(t_tab *tab, int direction);
void			main_sprite(t_tab *tab, double *zbuffer);
void			color_set(t_tab *tab, int y, int stripe);
void			my_mlx_pixel_put(t_img *frame_buf, int x, int y, int color);
int				exit_game(void *arg);
int				draw_block(int x, int y, t_tab *tab, int color);
int				convert_rgb_mlx(int r, int g, int b);
void			save(t_tab *tab, int x, int y, int bit);
void			clean_tab(t_tab *tab);

#endif
