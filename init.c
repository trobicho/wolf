/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:45:23 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 18:28:23 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static int	wolf_init_display(t_display *display)
{
	int	w;
	int	h;

	display->win = SDL_CreateWindow("Wolf"
		, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
		, display->width, display->height, SDL_WINDOW_OPENGL);
		//SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
	if (display->win == NULL)
		return (1);
	display->renderer = SDL_CreateRenderer(display->win, -1, 0);
	if (display->renderer == NULL)
		return (1);
	display->texture = SDL_CreateTexture(display->renderer
		, SDL_PIXELFORMAT_ARGB8888 , SDL_TEXTUREACCESS_STREAMING
		, display->width, display->height);
	if (display->texture == NULL)
		return (1);
	if ((display->pixels = malloc(sizeof(Uint32) 
					* display->width * display->height)) == NULL)
		return (1);
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
	SDL_RenderClear(display->renderer);
	SDL_RenderPresent(display->renderer);
	return (0);
}

int			wolf_init(t_wolf *wolf)
{
	wolf->display.width = 800;
	wolf->display.height = 600;
	if (wolf_init_display(&wolf->display))
		return (1);
	wolf->player.cam.fov = 1.0472;
	wolf->quit = 0;
	return (0);
}

int		wolf_quit(t_wolf *wolf)
{
	SDL_Quit();
	free(wolf->display.pixels);
	free(wolf->map.buf);
	return (0);
}
