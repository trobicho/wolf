/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:59:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 18:28:40 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <SDL2/SDL.h>
# include "map.h"
# include "vector.h"

typedef struct	s_camera
{
	t_vec2i	pos;
	float	angle;
	float	fov;
}				t_camera;

typedef struct	s_player
{
	t_camera		cam;
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

typedef struct	s_wolf
{
	t_player	player;
	t_map		map;
	t_display	display;
	int			quit;
}				t_wolf;

int				game_loop(t_wolf *wolf);
#endif
