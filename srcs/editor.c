/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 10:26:47 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/07 00:31:29 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "input.h"
#include "render.h"
#include "libft.h"
#include "editor_hud.h"
#include "editor_utils.h"
#include "map.h"

static int	editor_init(t_wolf *wolf, t_editor_inf *edit_inf)
{
	if (map_alloc(&edit_inf->map, 64, 64, 0))
		return (1);
	ft_memset(edit_inf->map.pixels, 0, edit_inf->map.w * edit_inf->map.h);
	map_copy(&edit_inf->map, &wolf->map);
	edit_inf->cursor = (t_edit_cursor){0, 0, 0, 1};
	edit_inf->map_box.h = wolf->display.height - 20;
	edit_inf->map_box.h -= edit_inf->map_box.h % edit_inf->map.h;
	edit_inf->map_box.w = edit_inf->map_box.h;
	edit_inf->map_box.x = (wolf->display.width - edit_inf->map_box.w - 128) / 2;
	edit_inf->map_box.y = (wolf->display.height - edit_inf->map_box.h) / 2;
	edit_inf->map_pos.x = 0;
	edit_inf->map_pos.y = 0;
	edit_inf->map_pos.w = edit_inf->map.w;
	edit_inf->map_pos.h = edit_inf->map.h;
	edit_inf->panel.x = wolf->display.width - 128;
	edit_inf->panel.y = 10;
	edit_inf->panel.w = 128;
	edit_inf->panel.h = 16 * 32;
	edit_inf->button_select = 0;
	edit_inf->max_id = 110;
	return (0);
}

static int	editor(t_wolf *wolf, t_editor_inf *edit)
{
	SDL_Rect	rect;
	SDL_Rect	map_rect;

	if (edit->cursor.state == cur_state_left_click
		|| edit->cursor.state == cur_state_right_click)
	{
		place_to_map(edit);
	}
	editor_map_display(wolf, edit);
	editor_draw_grid(wolf, edit);
	return (0);
}

static int	editor_click(t_wolf *wolf, t_editor_inf *edit)
{
	int				tex_select;

	if (edit->cursor.state == cur_state_left_click
		&& cursor_in_rect(&edit->cursor, edit->panel))
	{
		tex_select = (edit->cursor.x - edit->panel.x) / 32
			+ ((edit->cursor.y - edit->panel.y) / 32) * 4;
		if (tex_select < edit->max_id / 2)
			edit->cursor.tex_select = tex_select * 2 + 1;
		if (edit->cursor.y >= edit->panel.y + edit->panel.h - 32)
			edit->cursor.tex_select = edit->max_id
				+ (edit->cursor.x - edit->panel.x) / 32 + 1;
	}
	if (handle_button_click(edit, edit->save_button, 1, &save_map) == -1)
		return (-1);
	if (handle_button_click(edit, edit->erase_button, 2, &erase_map) == -1)
		return (-1);
	return (0);
}

int			editor_state(t_wolf *wolf)
{
	t_editor_inf	edit;

	if (editor_init(wolf, &edit))
		return (1);
	editor_display_reset(wolf);
	SDL_ShowCursor(SDL_ENABLE);
	while (!wolf->quit && wolf->state == state_editor)
	{
		editor_event(wolf, &edit.cursor);
		editor_click(wolf, &edit);
		editor(wolf, &edit);
		editor_display_hud(wolf, &edit);
		render_texture_apply(wolf);
		SDL_RenderPresent(wolf->display.renderer);
	}
	free(edit.map.pixels);
	SDL_ShowCursor(SDL_DISABLE);
	return (0);
}
