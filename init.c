/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:45:23 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 16:17:53 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static int	wolf_init_display(t_display *display)
{
	display->win = SDL_CreateWindow("Wolf"
		, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
		, 800, 600, SDL_WINDOW_OPENGL);
		//SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
	if (display->win == NULL)
		return (1);
	display->renderer = SDL_CreateRenderer(display->win, -1, 0);
	if (display->renderer == NULL)
		return (1);
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
	SDL_RenderClear(display->renderer);
	SDL_RenderPresent(display->renderer);
	return (0);
}

int			wolf_init(t_wolf *wolf)
{
	if (wolf_init_display(&wolf->display))
		return (1);
	wolf->quit = 0;
	return (0);
}
