/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 06:29:17 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/23 08:58:34 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "menu.h"
#include "render.h"
#include "libft.h"

static void	menu_draw_border(t_wolf *wolf, Uint32 color, int w)
{
	int		i;
	t_vec2i	pos;
	t_vec2i	pos_cur;

	pos.x = wolf->display.width / 2 - wolf->menu.w / 2;
	pos.y = wolf->display.height / 2 - wolf->menu.h / 2;
	pos_cur = (t_vec2i){0, 0};
	while (pos_cur.x < wolf->menu.w)
	{
		i = 0;
		while (i < w)
		{
			wolf->display.pixels[pos_cur.x + pos.x + (pos.y + i)
					* wolf->display.width] = color;
			wolf->display.pixels[pos_cur.x + pos.x
					+ (pos.y + (wolf->menu.h - 1) - i)
					* wolf->display.width] = color;
			i++;
		}
		pos_cur.x++;
	}
	pos_cur = (t_vec2i){0, 0};
	while (pos_cur.y < wolf->menu.h)
	{
		i = 0;
		while (i < w)
		{
			wolf->display.pixels[pos.x + i + (pos.y + pos_cur.y)
					* wolf->display.width] = color;
			wolf->display.pixels[pos.x + (wolf->menu.w - 1) - i
					+ (pos.y + pos_cur.y) * wolf->display.width] = color;
			i++;
		}
		pos_cur.y++;
	}
}

static void	menu_place_text(t_wolf *wolf, const char *str, int id)
{
	int			tex_w;
	int			tex_h;
	SDL_Rect	dst_rect;
	SDL_Surface	*surface;
	SDL_Color	color;
	SDL_Texture	*texture;
	int			space_h_per_text;

	color = (SDL_Color){255, 255, 255};
	surface = TTF_RenderText_Solid(wolf->menu.font, str, color);
	texture = SDL_CreateTextureFromSurface(wolf->display.renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &tex_w, &tex_h);
	dst_rect = (SDL_Rect){0 , 0, tex_w, tex_h};
	space_h_per_text = (wolf->menu.h / wolf->menu.nb_entrie) - tex_h;
	dst_rect.x = wolf->display.width / 2 - tex_w / 2;
	dst_rect.y = wolf->display.height / 2 - wolf->menu.h / 2
		+ (id + 1) * space_h_per_text / 2;
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
	int	p;

	p = 0;
	while (p < wolf->display.width * wolf->display.height)
	{
		wolf->display.pixels[p] = 0xFF0000;
		p++;
	}
	menu_draw_border(wolf, 0x0, 10);
	render_texture_apply(wolf);
	menu_place_text(wolf, "Game", 0);
	menu_place_text(wolf, "Editor", 0);
	menu_place_text(wolf, "Quit", 0);
	SDL_RenderPresent(wolf->display.renderer);
}
