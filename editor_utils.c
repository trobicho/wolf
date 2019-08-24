/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:19:27 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/24 19:13:19 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_utils.h"

void	draw_tex(t_wolf *wolf, SDL_Rect rect, int tex_index)
{
	int		x;
	int		y;
	Uint32	color;
	t_vec2i	offset;

	offset.x = (tex_index % 6) * 64;
	offset.y = (tex_index / 6) * 64;
	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			color = wolf->tiles_wall.pixels[
				offset.x + (int)(((float)x / rect.w) * 64.0)
				+ (offset.y + (int)(((float)y / rect.h) * 64.0))
				* wolf->tiles_wall.w];
			wolf->display.pixels[rect.x + x
					+ (rect.y + y) * wolf->display.width] = color;
			x++;
		}
		y++;
	}
}

void	editor_map_display(t_wolf *wolf, t_map *map, SDL_Rect map_rect)
{
	SDL_Rect	tex_rect;
	int			x;
	int			y;

	tex_rect = map_rect;
	tex_rect.w /= map->w;
	tex_rect.h /= map->h;
	y = 0;
	while (y < map->h)
	{
		x = 0;
		tex_rect.x = map_rect.x;
		while (x < map->w)
		{
			if (map->pixels[x + y * map->w])
				draw_tex(wolf, tex_rect, map->pixels[x + y * map->w] - 1);
			tex_rect.x += tex_rect.w;
			x++;
		}
		tex_rect.y += tex_rect.h;
		y++;
	}
}

int		place_to_map(t_map *map, SDL_Rect rect, const t_edit_cursor *cursor)
{
	int	x; 
	int	y; 
	int	apply;

	if (cursor->x > rect.x && cursor->x < rect.x + rect.w
		&& cursor->y > rect.x && cursor->y < rect.y + rect.h)
	{
		x = (cursor->x - rect.x) / (float)rect.w * map->w;
		y = (cursor->y - rect.y) / (float)rect.h * map->h;
		if (cursor->state == cur_state_left_click)
			apply = cursor->tex_select;
		else
			apply = 0;
		if (map->pixels[x + y * map->w] != apply)
		{
			map->pixels[x + y * map->w] = apply;
			return (1);
		}
	}
	return (0);
}
