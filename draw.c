/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 00:07:27 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/29 02:10:16 by trobicho         ###   ########.fr       */
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

void	draw_unicolor_slice(t_wolf *wolf, t_ray ray, int col, Uint32 color)
{
	int	height;
	int	y_slice;
	int	y;

	height = (128.0 / ray.dist) * 255;
	if (height > wolf->display.height)
		height = wolf->display.height;
	y_slice = 0;
	y = wolf->display.height / 2 - height / 2;
	while (y_slice < height)
	{
		wolf->display.pixels[col + y * wolf->display.width] = color;
		y_slice++;
		y++;
	}
}

void	draw_textured_slice(t_wolf *wolf, t_ray *ray, int col, int tex_index)
{
	int		height;
	int		y_slice;
	int		y;
	Uint32	color;
	int		offset;

	offset = (tex_index % 6) * 64 + (int)(ray->wall_col * 64)
		+ (tex_index / 6) * 64 * wolf->tiles_wall.w;
	height = (128.0 / ray->dist) * wolf->display.height * 0.5;
	y_slice = 0;
	y = wolf->display.height / 2.0 - height / 2.0;
	if (height > wolf->display.height)
	{
		y_slice = (height - wolf->display.height) / 2;
		y = 0;
	}
	while (y_slice < height && y < wolf->display.height)
	{
		color = wolf->tiles_wall.pixels[offset
			+ (int)((y_slice << 6) / height) * wolf->tiles_wall.w];
		wolf->display.pixels[col + y * wolf->display.width] = color;
		y_slice++;
		y++;
	}
}
