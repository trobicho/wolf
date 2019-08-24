/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:59:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/23 13:50:58 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include "map.h"
# include "vector.h"
# include "ppm.h"

typedef enum	s_state
{
	state_game,
	state_menu,
	state_dead,
	state_editor,
	state_option,
}				t_state;

typedef struct	s_player
{
	t_vec2i			pos;
	float			angle;
	float			fov;
	unsigned int	health;
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
	int				quit;
}				t_wolf;

int				state_loop(t_wolf *wolf);
#endif
