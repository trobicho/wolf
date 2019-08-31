/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 06:29:17 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/31 21:14:57 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "menu.h"
#include "render.h"
#include "libft.h"
#include "draw.h"

static SDL_Texture	*menu_give_me_the_rect_for_the_text(t_wolf *wolf
	, SDL_Surface *surface, int id, SDL_Rect *dst_rect)
{
	int			space_h_per_text;
	SDL_Texture	*texture;
	int			win_w;
	int			win_h;

	SDL_GetWindowSize(wolf->display.win, &win_w, &win_h);
	space_h_per_text = (wolf->menu.h / wolf->menu.nb_entrie);
	texture = SDL_CreateTextureFromSurface(wolf->display.renderer, surface);
	*dst_rect = (SDL_Rect){0, 0, surface->w, surface->h};
	dst_rect->x = wolf->display.width / 2 - surface->w / 2
		+ (win_w - wolf->display.width) / 2;
	dst_rect->y = wolf->display.height / 2 - wolf->menu.h / 2
		+ (win_h - wolf->display.height) / 2
		+ id * space_h_per_text + space_h_per_text / 2 - surface->h / 2;
	return (texture);
}

static void			menu_place_text(t_wolf *wolf, const char *str, int id)
{
	SDL_Rect	dst_rect;
	SDL_Surface	*surface;
	SDL_Color	color;
	SDL_Texture	*texture;

	if (id == wolf->menu.select)
		color = (SDL_Color){200, 200, 200};
	else
		color = (SDL_Color){130, 130, 130};
	surface = TTF_RenderText_Solid(wolf->menu.font, str, color);
	texture = menu_give_me_the_rect_for_the_text(wolf, surface, id, &dst_rect);
	SDL_RenderCopy(wolf->display.renderer, texture, NULL, &dst_rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void				menu_state(t_wolf *wolf)
{
	while (!wolf->quit && wolf->state == state_menu)
	{
		menu_display(wolf);
		menu_event(wolf);
	}
}

void				menu_display(t_wolf *wolf)
{
	int			p;
	SDL_Rect	menu_border;

	p = 0;
	while (p < wolf->display.width * wolf->display.height)
	{
		wolf->display.pixels[p] = 0xFF0000;
		p++;
	}
	menu_border.x = wolf->display.width / 2 - wolf->menu.w / 2;
	menu_border.y = wolf->display.height / 2 - wolf->menu.h / 2;
	menu_border.w = wolf->menu.w;
	menu_border.h = wolf->menu.h;
	draw_border(&wolf->display, menu_border, 0x0, 10);
	render_texture_apply(wolf);
	menu_place_text(wolf, "Game", 0);
	menu_place_text(wolf, "Editor", 1);
	menu_place_text(wolf, "Quit", 2);
	SDL_RenderPresent(wolf->display.renderer);
}
