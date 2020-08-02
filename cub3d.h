/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 09:50:55 by rde-vrie      #+#    #+#                 */
/*   Updated: 2020/07/30 16:34:26 by rde-vrie      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>

# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define CLOSE_WINDOW 17

typedef struct	s_map
{
	char		**map;
	int			height;
	int			width;
	int			map_begin;
}				t_map;

typedef struct	s_ivector
{
	int			x;
	int			y;
}				t_ivector;

typedef struct	s_dvector
{
	double		x;
	double		y;
}				t_dvector;

typedef struct	s_player
{
	int			x;
	int			y;
	double		speed;
	double		rot_speed;
	int			health;
}				t_player;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_keys
{
	char		w;
	char		a;
	char		s;
	char		d;
	char		left;
	char		right;
}				t_keys;

typedef struct	s_texture
{
	char		*path;
	t_data		img;
	int			width;
	int			height;
	int			present;
}				t_texture;

typedef struct	s_sprite_data
{
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_height;
	int			sprite_width;
	int			sprite_start;
	int			sprite_end;
	int			sprite_screen_x;
}				t_sprite_data;

typedef struct	s_calc
{
	int			side;
	int			hit;
	double		perpwalldist;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			wall_height;
	int			draw_start;
	int			draw_end;
}				t_calc;

typedef struct	s_cub
{
	int			screenwidth;
	int			screenheight;
	t_texture	wall_n;
	t_texture	wall_e;
	t_texture	wall_s;
	t_texture	wall_w;
	t_texture	sprite;
	int			floor;
	int			ceiling;
	char		**plan;
}				t_cub;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	char		save;
	t_data		img1;
	t_data		img2;
	int			active;
	t_player	player;
	t_keys		key;
	t_dvector	pos;
	t_dvector	dir;
	t_dvector	plane;
	t_dvector	side_dist;
	t_ivector	step;
	t_map		map;
	t_cub		cub;
	t_calc		calc;
	int			sprite_count;
	int			move;
	t_dvector	*sprite_array;
	double		*z_buffer;
}				t_vars;

/*
** map.c
*/
void			free_array(char **array);
int				more_options(t_vars *vars, char *line);
void			divide_function(t_vars *vars, int fd);
void			check_complete(t_vars *vars);
void			read_cubfile(char **argv, t_vars *vars);

/*
** map_2.c
*/
void			player_north(t_vars *vars, char *line, int i, int j);
void			player_east(t_vars *vars, char *line, int i, int j);
void			player_south(t_vars *vars, char *line, int i, int j);
void			player_west(t_vars *vars, char *line, int i, int j);
void			make_sprite_array(t_vars *vars, int i, int j);

/*
** map_3.c
*/
void			ceiling_floor(char *line, t_vars *vars);
void			ceiling_floor_2(t_vars *vars, char **array, int *rgb,
				char *line);
void			parse_floor(t_vars *vars, int *rgb);
void			parse_ceiling(t_vars *vars, int *rgb);

/*
** map_4.c
*/
void			map_size(char *line, t_vars *vars);
void			read_line(char *line, t_vars *vars, int i);
void			check_line_of_map(t_vars *vars, char *line, int i);
void			make_map(t_vars *vars, int fd);
void			read_map(t_vars *vars, int result, int fd);

/*
** map_5.c
*/
void			valid_chars(char **array, char *line);
void			resolution(char *line, t_vars *vars);
void			path_to_png(char *line, t_vars *vars);
int				go_to_map(t_vars *vars, int result, int fd, char *line);

/*
** textures.c
*/
void			my_mlx_pixel_put(t_data *data, int x, int y, int colour);
unsigned int	my_mlx_pixel_get(t_texture texture, t_data *data, int x, int y);
t_texture		texture_on_side(t_vars *vars, int side);
void			textured_line(int x, t_data *img, t_vars *vars, t_calc *calc);
int				draw_ceiling(t_vars *vars, t_data *img, t_calc *calc, int x);

/*
** raycast.c
*/
int				is_hit(t_vars *vars, t_dvector *delta_dist, t_ivector *map,
				t_calc *calc);
double			where_hit(t_vars *vars, t_dvector *raydir, t_ivector *map,
				t_calc *calc);
void			draw_start_end(t_calc *calc, int screenheight);
void			draw_column(t_vars *vars, int x, t_calc *calc);
int				render_next_frame(t_vars *vars);

/*
** raycast_2.c
*/
int				create_trgb(int r, int g, int b);
void			calc_step_dist(t_vars *vars, t_dvector *raydir, t_dvector
				*delta_dist, t_ivector *map);
t_data			*get_new_image(t_vars *vars);
void			set_new_image(t_vars *vars);

/*
** cubed.c
*/
int				draw(int keycode);
int				close_window();
void			open_window(t_vars *vars);
void			run_game(t_vars *vars);

/*
** start.c
*/
void			start_cub(t_vars *vars);
void			start_conditions(t_vars *vars);
void			set_screensize(t_vars *vars);
void			initialize_image(t_vars *vars);

/*
** keys.c
*/
void			forward(t_vars *vars);
void			backward(t_vars *vars);
void			left(t_vars *vars);
void			right(t_vars *vars);

/*
** key_release.c
*/
void			check_keys(t_vars *vars);
int				keypress(int keycode, t_vars *vars);
int				keyrelease(int keycode, t_vars *vars);
void			rotate_left(t_vars *vars);
void			rotate_right(t_vars *vars);

/*
** sprites.c
*/
void			next_last_sprite(t_vars *vars, int i, double *next,
				double *last);
int				sprite_translate(t_sprite_data *info, t_vars *vars);
void			sprite_column(int x, t_sprite_data *info, t_vars *vars,
				t_data *img);
void			sprites(t_vars *vars, t_data *img);

/*
** sort_sprites.c
*/
void			swap(t_dvector *a, t_dvector *b);
void			sprite_sort(t_vars *vars);

/*
** screenshot.c
*/
void			bit_converter(unsigned char *header, int value);
unsigned int	my_mlx_pixel_get_screenshot(t_data *data, int x, int y);
void			image_body(t_vars *vars, int fd);
void			image_header(t_vars *vars, int fd);
void			make_screenshot(t_vars *vars);

/*
** error.c
*/
void			print_error(int e_type, char *line);
void			print_error_2(int e_type);
void			print_error_3(int e_type);

/*
** import_textures.c
*/
int				file_extension(char *filename, char *filetype);
t_texture		*pick_texture(t_vars *vars, int id);
void			import_images(t_vars *vars);
void			import_image(t_vars *vars, t_texture *tex);

/*
** floodfill.c
*/
void			floodfill(t_map map, int x, int y);
void			empty_out(t_map map, t_vars *vars);

/*
** LIBFT Functions
*/
int				ft_atoi(const char *str);
char			**ft_split(char const *s, char c);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *str);
int				ft_atoi_colour(const char *str, int *index);
char			*ft_strdup(const char *src);
#endif
