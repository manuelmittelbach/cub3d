/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:38:25 by jnieders          #+#    #+#             */
/*   Updated: 2026/04/28 14:42:50 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "libft.h"
#include "mlx.h"

// #define WIDTH 1920
// #define HEIGHT 1080
#define WIDTH 1280
#define HEIGHT 720
// #define WIDTH 640
// #define HEIGHT 480

#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_M 109
#define KEY_T 116
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

#define MOVE_SPEED 0.03
#define ROT_SPEED 0.04
#define MOUSE_SENS 0.0007

typedef struct s_list {
  char *string;
  struct s_list *next;
} t_list;

typedef struct s_mapinfo {
  char *NO;
  char *SO;
  char *WE;
  char *EA;

  int F[3];
  int C[3];

  bool all_elements_found;

  t_list *map_list;
  char **map_arr;
} t_mapinfo;

typedef struct s_img {
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
  int width;
  int height;
} t_img;

typedef enum e_side {
  HIT_VERTICAL = 0,
  HIT_HORIZONTAL = 1
} t_side;

typedef struct s_ray {
  double	ray_dir_x;
  double	ray_dir_y;
  double	delta_dist_x;
  double	delta_dist_y;
  double	side_dist_x;
  double	side_dist_y;
  int		map_x;
  int		map_y;
  int		step_x;
  int		step_y;
  t_side	hit;
  double	wall_dist;
} t_ray;

typedef struct s_wall {
	double	height;
	int		start;
	int		end;
	int		tex_col;
	double	step;
	double	tex_pos;
}	t_wall;

typedef struct s_data {
  void *mlx;
  void *win;
  t_img screen; // Das Hauptbild zum Anzeigen
  t_img tex[4]; // NO, SO, WE, EA Texturen

  // Array fuer Tastenstatus
  bool  keys[65536];
  bool  show_minimap;
  bool  mouse_active;

  // Parsing Informationen
  t_mapinfo map;

  // Spieler-Status
  double pos_x;
  double pos_y;
  double dir_x; // Richtungsvektor
  double dir_y;
  double plane_x; // Kamera-Ebene (FOV)
  double plane_y;
} t_data;

/* ============= Utils =============*/
void free_str_arr(char **str_arr);
void	free_map_and_list(t_mapinfo *map);
int get_rgb_color(int rgb[3]);

/* ============= MLX =============*/
int init_mlx(t_data *data);
int load_textures(t_data *data, t_mapinfo *map);

/* ============= Events =============*/
int handle_keypress(int keycode, t_data *data);
int	handle_keyrelease(int keycode, t_data *d);
int handle_close(t_data *data);
int handle_mouse_move(int x, int y, t_data *d);

/* ============= Player Movements =============*/
void	move_player(t_data *d, double move_x, double move_y);
void	rotate_player(t_data *d, double rot_speed);

/* ============= MLX Utils =============*/
void cleanup(t_data *data);
void ft_mlx_pixel_put(t_img *img, int x, int y, int color);

/* ============= Raycaster =============*/
int render_frame(t_data *d);
void cast_rays(t_data *d);
void draw_floor_and_ceiling(t_data *d);
void render_wall_strip(t_data *d, t_ray *r, int x);

/* ============= DDA =============*/
void init_ray(t_data *d, t_ray *r, int x);
void run_dda(t_data *d, t_ray *r);

#endif
