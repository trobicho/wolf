/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:45:23 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 14:39:24 by trobicho         ###   ########.fr       */
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
	display->renderer = SDL_CreateRenderer(display->win, -1
		, SDL_RENDERER_PRESENTVSYNC);
	if (display->renderer == NULL)
		return (1);
	display->texture = SDL_CreateTexture(display->renderer
		, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING
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
	wolf->display.height = 700;
	if (wolf_init_display(&wolf->display))
		return (1);
	TTF_Init();
	if ((wolf->menu.font = TTF_OpenFont("texture/long_shot.ttf", 35)) == NULL)
		return (1);
	wolf->player.fov = 1.3472;
	wolf->quit = 0;
	wolf->tiles_wall.blend = 0xFF00FF;
	if (ppm_load_4bpp("./texture/tile.pbm", &wolf->tiles_wall))
		return (1);
	wolf->state = state_menu;
	wolf->menu.nb_entrie = 3;
	wolf->menu.select = 0;
	wolf->menu.w = 200;
	wolf->menu.h = 300;
	return (0);
}

int			wolf_quit(t_wolf *wolf)
{
	SDL_DestroyTexture(wolf->display.texture);
	SDL_DestroyRenderer(wolf->display.renderer);
	SDL_DestroyWindow(wolf->display.win);
	TTF_CloseFont(wolf->menu.font);
	TTF_Quit();
	SDL_Quit();
	free(wolf->display.pixels);
	free(wolf->map.pixels);
	free(wolf->tiles_wall.pixels);
	return (0);
}
