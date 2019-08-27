/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 14:31:29 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 11:58:37 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include "editor_hud.h"
#include "draw.h"

static void	display_panel(t_wolf *wolf, t_editor_inf *edit)
{
	int			i;
	SDL_Rect	rect;

	rect = edit->panel;
	rect.w = 32;
	rect.h = 32;
	i = 0;
	while (i < 59)
	{
		if (rect.x + rect.w > wolf->display.width || i == 55)
		{
			rect.x = edit->panel.x;
			rect.y += rect.h;
		}
		if (i == 55)
			rect.y = edit->panel.y + edit->panel.h - rect.h;
		if (i == 54)
			draw_tex(wolf, rect, 110);
		else if (i >= 55)
			draw_tex(wolf, rect, 111 + (i - 55));
		else
			draw_tex(wolf, rect, i * 2 + 1);
		rect.x += rect.w;
		i++;
	}
}

void		editor_display_reset(t_wolf *wolf)
{
	int			p;

	p = 0;
	while (p < wolf->display.width * wolf->display.height)
	{
		wolf->display.pixels[p] = 0x909090;
		p++;
	}
}

void		editor_display_hud(t_wolf *wolf, t_editor_inf *edit)
{
	int			i;
	SDL_Rect	rect;

	display_panel(wolf, edit);
	edit->save_button = edit->panel;
	edit->save_button.y += edit->panel.h + 20;
	edit->save_button.h = 50;
	if (edit->save_select)
	{
		draw_full_rect(&wolf->display, edit->save_button, 0x225500);
		draw_border(&wolf->display, edit->save_button, 0x0, 3);
	}
	else
	{
		draw_full_rect(&wolf->display, edit->save_button, 0x00AA00);
		draw_border(&wolf->display, edit->save_button, 0x0, 3);
	}
}
