/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 10:26:47 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/24 19:18:37 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "input.h"
#include "render.h"
#include "libft.h"
#include "editor_utils.h"

static void	editor_display(t_wolf *wolf)
{
	int			p;
	int			i;
	SDL_Rect	rect;
	SDL_Rect	panel;

	p = 0;
	while (p < wolf->display.width * wolf->display.height)
	{
		wolf->display.pixels[p] = 0x909090;
		if ((p / wolf->display.width) / 10 > 0
			&& (p / wolf->display.width) % 10 == 0)
			wolf->display.pixels[p] = 0x0;
		else if ((p % wolf->display.width) / 10 > 0
			&& (p % wolf->display.width) % 10 == 0)
			wolf->display.pixels[p] = 0x0;
		p++;
	}
	panel.x = wolf->display.width - 128;
	panel.y = 10;
	rect = panel;
	rect.w = 32;
	rect.h = 32;
	i = 0;
	while (i < 55)
	{
		if (rect.x + rect.w > wolf->display.width)
		{
			rect.x = panel.x;
			rect.y += rect.h;
		}
		if (i == 54)
			draw_tex(wolf, rect, 109);
		else
			draw_tex(wolf, rect, i * 2);
		rect.x += rect.w;
		i++;
	}
}

static int	editor(t_wolf *wolf, t_map *map, t_edit_cursor *cursor)
{
	SDL_Rect		rect;
	int				ret;

	rect.w = 640;
	rect.h = 640;
	rect.x = (wolf->display.width - rect.w) / 2;
	rect.y = (wolf->display.height - rect.h) / 2;
	ret = 0;
	if (cursor->state == cur_state_left_click
		|| cursor->state == cur_state_right_click)
	{
		ret = place_to_map(map, rect, cursor);
	}
	if (ret)
	{
		editor_display(wolf);
		editor_map_display(wolf, map, rect);
	}
	return (ret);
}

void		editor_state(t_wolf *wolf)
{
	t_edit_cursor	cursor;
	t_map			map;

	map_alloc(&map, 64, 64);
	ft_memset(map.pixels, 10, map.w * map.h);
	cursor = (t_edit_cursor){0, 0, 0, 0};
	while (!wolf->quit && wolf->state == state_editor)
	{
		editor_event(wolf, &cursor);
		if (editor(wolf, &map, &cursor) == 1)
		{
			render_texture_apply(wolf);
			SDL_RenderPresent(wolf->display.renderer);
		}
	}
	free(map.pixels);
}
