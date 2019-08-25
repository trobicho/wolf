/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 14:31:29 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/25 15:09:34 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_hud.h"
#include <SDL2/SDL.h>

void	draw_button(t_wolf *wolf, SDL_Rect button, Uint32 color)
{
	int			x;
	int			y;

	y = button.y;
	while (y < button.h + button.y)
	{
		x = button.x;
		while (x < button.w + button.x)
		{
			wolf->display.pixels[x + y * wolf->display.width] = color;
			x++;
		}
		y++;
	}
}

void	editor_display_reset(t_wolf *wolf)
{
	int			p;

	p = 0;
	while (p < wolf->display.width * wolf->display.height)
	{
		wolf->display.pixels[p] = 0x909090;
		p++;
	}
}

void	editor_display_hud(t_wolf *wolf, t_editor_inf *edit)
{
	int			i;
	SDL_Rect	rect;

	rect = edit->panel;
	rect.w = 32;
	rect.h = 32;
	edit->save_button = edit->panel;
	edit->save_button.y += edit->panel.h + 20;
	edit->save_button.h = 50;
	i = 0;
	while (i < 55)
	{
		if (rect.x + rect.w > wolf->display.width)
		{
			rect.x = edit->panel.x;
			rect.y += rect.h;
		}
		if (i == 54)
			draw_tex(wolf, rect, 109);
		else
			draw_tex(wolf, rect, i * 2 + 1);
		rect.x += rect.w;
		i++;
	}
	if (edit->save_select)
		draw_button(wolf, edit->save_button, 0x225500);
	else
		draw_button(wolf, edit->save_button, 0x00AA00);
}
