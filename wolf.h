/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:59:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 14:47:39 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

typedef struct	s_camera
{
	t_vec2i	pos;
	float	angle;
}				t_camera;

typedef struct	s_player
{
	t_camera		cam;
	unsigned int	health;
}

typedef struct	s_display
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
}				t_display;

typedef struct	s_wolf
{
	t_display
}				t_wolf;

int		wolf_init(t_wolf *wolf);
#endif
