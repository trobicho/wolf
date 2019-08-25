/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 10:26:47 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/25 15:22:52 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "input.h"
#include "render.h"
#include "libft.h"
#include "editor_hud.h"
#include "editor_utils.h"

static int	editor_init(t_wolf *wolf, t_editor_inf *edit_inf)
{
	if (map_alloc(&edit_inf->map, 62, 62))
		return (1);
	ft_memset(edit_inf->map.pixels, 0, edit_inf->map.w * edit_inf->map.h);
	edit_inf->cursor = (t_edit_cursor){0, 0, 0, 1};
	edit_inf->map_box.w = 620;
	edit_inf->map_box.h = 620;
	edit_inf->map_box.x = 0;
	edit_inf->map_box.y = (wolf->display.height - edit_inf->map_box.h) / 2;
	edit_inf->map_pos.x = 0;
	edit_inf->map_pos.y = 0;
	edit_inf->map_pos.w = edit_inf->map.w;
	edit_inf->map_pos.h = edit_inf->map.h;
	edit_inf->panel.x = wolf->display.width - 128;
	edit_inf->panel.y = 10;
	edit_inf->panel.w = 128;
	edit_inf->panel.h = 14 * 32;
	edit_inf->save_select = 0;
	return (0);
}

static int	editor(t_wolf *wolf, t_editor_inf *edit)
{
	SDL_Rect	rect;
	SDL_Rect	map_rect;

	if (edit->cursor.x >= edit->save_button.x
		&& edit->cursor.y >= edit->save_button.y
		&& edit->cursor.x < edit->save_button.x + edit->save_button.w
		&& edit->cursor.y < edit->save_button.y + edit->save_button.h)
	{
		if (edit->cursor.state == cur_state_none && edit->save_select)
		{
			edit->save_select = 0;
			if (ppm_write_1bpp("./maps/save_map.ppm", &edit->map))
				ft_putstr("cannot save the map\n");
		}
		else if (edit->cursor.state == cur_state_left_click)
			edit->save_select = 1;
	}
	else
		edit->save_select = 0;
	if (edit->cursor.state == cur_state_left_click
			|| edit->cursor.state == cur_state_right_click)
	{
		place_to_map(edit);
	}
	editor_map_display(wolf, edit);
	editor_draw_grid(wolf, edit);
	return (0);
}

int			editor_state(t_wolf *wolf)
{
	t_editor_inf	edit;
	int				tex_select;

	if (editor_init(wolf, &edit))
		return (1);
	editor_display_reset(wolf);
	while (!wolf->quit && wolf->state == state_editor)
	{
		editor_event(wolf, &edit.cursor);
		if (edit.cursor.state == cur_state_left_click
			&& edit.cursor.x >= edit.panel.x && edit.cursor.y >= edit.panel.y
			&& edit.cursor.x < edit.panel.x + edit.panel.w
			&& edit.cursor.y < edit.panel.y + edit.panel.h)
		{
			tex_select = (edit.cursor.x - edit.panel.x) / 32
				+ ((edit.cursor.y - edit.panel.y) / 32) * 4;
			if (tex_select < 54)
				edit.cursor.tex_select = tex_select * 2 + 1;
			printf("select = %d\n", edit.cursor.tex_select);
		}
		editor(wolf, &edit);
		editor_display_hud(wolf, &edit);
		render_texture_apply(wolf);
		SDL_RenderPresent(wolf->display.renderer);
	}
	free(edit.map.pixels);
	return (0);
}
