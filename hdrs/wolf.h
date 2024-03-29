/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:59:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/03 06:40:31 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include "map.h"
# include "vector.h"
# include "ppm.h"
# include "libft.h"

# define P_FORWARD		1
# define P_BACKWARD		2
# define P_STRAFE_R		4
# define P_STRAFE_L		8
# define P_ROTATE_R		16
# define P_ROTATE_L		32

typedef enum	e_state
{
	state_game,
	state_menu,
	state_dead,
	state_editor,
	state_option,
}				t_state;

typedef enum	e_door_state
{
	door_state_close = 0,
	door_state_open = 1,
	door_state_opening,
	door_state_closing,
	door_state_waiting_for_player_to_move_is_ass,
}				t_door_state;

typedef enum	e_secret_door_state
{
	secret_door_state_block = 0,
	secret_door_state_moving,
	secret_door_state_block_by_player,
}				t_secret_door_state;

typedef struct	s_door
{
	t_vec2i			pos;
	t_door_state	state;
	float			w;
	int				timer;
}				t_door;

typedef struct	s_secret_door
{
	t_vec2i				pos;
	t_vec2i				dir;
	t_secret_door_state	state;
	int					timer;
}				t_secret_door;

typedef struct	s_player
{
	t_vec2i			pos;
	float			angle;
	float			fov;
	unsigned int	health;
	int				state;
	int				speed;
	int				strafe_speed;
	int				hb;
}				t_player;

typedef struct	s_display
{
	int				width;
	int				height;
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	Uint32			*pixels;
}				t_display;

typedef struct	s_menu
{
	int			nb_entrie;
	int			select;
	TTF_Font	*font;
	int			w;
	int			h;
}				t_menu;

typedef struct	s_wolf
{
	t_player		player;
	t_map			map;
	t_display		display;
	t_ppm_tex_4bpp	tiles_wall;
	t_state			state;
	t_menu			menu;
	t_list			*door_list;
	t_list			*secret_door_list;
	int				quit;
}				t_wolf;

int				state_loop(t_wolf *wolf);
int				is_found_door(int id);
t_door			*find_that_door(t_wolf *wolf, t_vec2i pos);
t_secret_door	*find_that_secret_door(t_wolf *wolf, t_vec2i pos);
int				handle_action_event(t_wolf *wolf);
void			handle_door_state(t_wolf *wolf);
void			handle_secret_door_state(t_wolf *wolf);
void			open_secret_door(t_wolf *wolf, t_vec2i pos, t_vec2i dir);
#endif
