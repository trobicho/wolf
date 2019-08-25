/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 14:31:29 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/25 14:34:23 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_hud.h"
#include <SDL2/SDL.h>

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
}
