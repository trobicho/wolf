/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 06:29:17 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 00:39:11 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "menu.h"
#include "render.h"
#include "libft.h"
#include "draw.h"

static void	menu_place_text(t_wolf *wolf, const char *str, int id)
{
	int			tex_w;
	int			tex_h;
	SDL_Rect	dst_rect;
	SDL_Surface	*surface;
	SDL_Color	color;
	SDL_Texture	*texture;
	int			space_h_per_text;

	if (id == wolf->menu.select)
		color = (SDL_Color){200, 200, 200};
	else
		color = (SDL_Color){130, 130, 130};
	surface = TTF_RenderText_Solid(wolf->menu.font, str, color);
	texture = SDL_CreateTextureFromSurface(wolf->display.renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &tex_w, &tex_h);
	dst_rect = (SDL_Rect){0 , 0, tex_w, tex_h};
	space_h_per_text = (wolf->menu.h / wolf->menu.nb_entrie);
	dst_rect.x = wolf->display.width / 2 - tex_w / 2;
	dst_rect.y = wolf->display.height / 2 - wolf->menu.h / 2
		+ id * space_h_per_text + space_h_per_text / 2 - tex_h / 2;
	SDL_RenderCopy(wolf->display.renderer, texture, NULL, &dst_rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void		menu_state(t_wolf *wolf)
{
	while (!wolf->quit && wolf->state == state_menu)
	{
		menu_display(wolf);
		menu_event(wolf);
	}
}

void		menu_display(t_wolf *wolf)
{
	int			p;
	SDL_Rect	menu_border;

	p = 0;
	while (p < wolf->display.width * wolf->display.height)
	{
		wolf->display.pixels[p] = 0xFF0000;
		p++;
	}
	//menu_draw_border(wolf, 0x0, 10);
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
