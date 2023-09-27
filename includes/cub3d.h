/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:53:47 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/27 15:27:58 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "lists.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

# define SIZE_CASE 32    // ?
# define SIZE_PLAYER 4.0 // ?
# define RENDER_DIST 32  // ?
# define ROT_SPEED 0.1
# define MOVE_SPEED 10

typedef bool	t_bool;

typedef enum e_map_value
{
	EMPTY = 0,
	WALL,
	SPACE,
	PN,
	PS,
	PW,
	PE,
	ERR,
}				t_map_value;

typedef enum e_co
{
	CO_X,
	CO_Y,
}				t_co;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bit_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct s_line
{
	double		x1;
	double		y1;
	double		x2;
	double		y2;
}				t_line;

typedef struct s_player
{
	double		x;
	double		y;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_map_data
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor;
	int			ceiling;
}				t_map_data;

typedef struct s_map
{
	t_map_value	**map;
	int			x_max;
	int			y_max;
	t_map_data	data;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			x_win;
	int			y_win;
	double		time;
	double		old_time;
	t_img_data	buffer;
	t_map		map;
	t_player	*player;
}				t_game;

// init
void			init_player(t_game *game);
void			init_game(t_game *game);
void			init_map(t_map *map);

// display utils
void			my_mlx_pixel_put(t_img_data *buffer, int x, int y, int c);
t_line			create_line(float x1, float y1, float x2, float y2);
void			my_put_line(t_game *game, t_line line, int c);
void			my_put_line_w(t_game *game, t_line line, int c, int w);

// display
void			draw_obs(t_game *game);
void			draw_player(t_game *game);
void			draw_grid(t_game *game);
void			draw_ray(t_game *game, t_bool calc);

// key input
int				close_game(t_game *game);
int				check_input(int key, t_game *game);
int				loop(t_game *game);

// parsing
t_bool			parse_cubfile(char *file, t_map *map);

// helpers
void			error_and_exit(char *str);
void			perror_and_exit(char *prefix);
// clear
void			destroy_map(t_map *map);
#endif
