/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:59:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 16:19:33 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <SDL2/SDL.h>

typedef struct	s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;

typedef struct	s_camera
{
	t_vec2f	pos;
	float	angle;
}				t_camera;

typedef struct	s_player
{
	t_camera		cam;
	unsigned int	health;
}				t_player;

typedef struct	s_display
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
}				t_display;

typedef struct	s_wolf
{
	t_display	display;
	int			quit;
}				t_wolf;

int				game_loop(t_wolf *wolf);
#endif
