/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 00:07:27 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 00:38:48 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_full_rect(t_display *display, SDL_Rect rect, Uint32 color)
{
	int	x;
	int	y;

	y = rect.y;
	while (y < rect.y + rect.h)
	{
		x = rect.x;
		while (x < rect.x + rect.w)
		{
			display->pixels[x + y * display->width] = color;
			x++;
		}
		y++;
	}
}

void	draw_border(t_display *display, SDL_Rect border, Uint32 color, int w)
{
	SDL_Rect	rect;

	rect = (SDL_Rect){border.x, border.y, border.w, w};
	draw_full_rect(display, rect, color);
	rect = (SDL_Rect){border.x, border.y + border.h - w, border.w, w};
	draw_full_rect(display, rect, color);
	rect = (SDL_Rect){border.x, border.y, w, border.h};
	draw_full_rect(display, rect, color);
	rect = (SDL_Rect){border.x + border.w - w, border.y, w, border.h};
	draw_full_rect(display, rect, color);
}
