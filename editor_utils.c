/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:19:27 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/29 01:45:00 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_utils.h"

void	draw_tex(t_wolf *wolf, SDL_Rect rect, int tex_index)
{
	int		x;
	int		y;
	Uint32	color;
	t_vec2i	offset;

	offset.x = ((tex_index - 1) % 6) * 64;
	offset.y = ((tex_index - 1) / 6) * 64;
	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			if (tex_index > 0)
			{
				color = wolf->tiles_wall.pixels[
						offset.x + (int)(((float)x / rect.w) * 64.0)
						+ (offset.y + (int)(((float)y / rect.h) * 64.0))
						* wolf->tiles_wall.w];
			}
			else
				color = 0x909090;
			wolf->display.pixels[rect.x + x
					+ (rect.y + y) * wolf->display.width] = color;
			x++;
		}
		y++;
	}
}

void	editor_draw_grid(t_wolf *wolf, t_editor_inf *edit)
{
	int	x;
	int	y;

	y = edit->map_box.y;
	while (y <= edit->map_box.y + edit->map_box.h)
	{
		x = edit->map_box.x;
		while (x < edit->map_box.x + edit->map_box.w + 1)
		{
			wolf->display.pixels[x + y * wolf->display.width] = 0x0;
			x++;
		}
		y += edit->map_box.h / (float)edit->map_pos.h;
	}
	x = edit->map_box.x;
	while (x <= edit->map_box.x + edit->map_box.w)
	{
		y = edit->map_box.y;
		while (y < edit->map_box.y + edit->map_box.h)
		{
			wolf->display.pixels[x + y * wolf->display.width] = 0x0;
			y++;
		}
		x += edit->map_box.w / (float)edit->map_pos.w;
	}
}

void	editor_map_display(t_wolf *wolf, t_editor_inf *edit)
{
	SDL_Rect	tex_rect;
	int			x;
	int			y;

	tex_rect = edit->map_box;
	tex_rect.w /= edit->map_pos.w;
	tex_rect.h /= edit->map_pos.h;
	y = edit->map_pos.y;
	while (y < edit->map_pos.y + edit->map_pos.h)
	{
		x = edit->map_pos.x;
		tex_rect.x = edit->map_box.x;
		while (x < edit->map_pos.x + edit->map_pos.w)
		{
			draw_tex(wolf, tex_rect,
				edit->map.pixels[x + y * edit->map.w]);
			tex_rect.x += tex_rect.w;
			x++;
		}
		tex_rect.y += tex_rect.h;
		y++;
	}
}

int			cursor_in_rect(t_edit_cursor *cursor, SDL_Rect rect)
{
	if (cursor->x >= rect.x && cursor->x < rect.x + rect.w
		&& cursor->y >= rect.y && cursor->y < rect.y + rect.h)
		return (1);
	return (0);
}
