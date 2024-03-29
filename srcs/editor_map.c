/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 01:38:20 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/06 23:48:05 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "editor_utils.h"
#include "map.h"

static void	apply_to_map_buffer_and_potentially_update_cursor(
	t_editor_inf *edit, int x, int y)
{
	int	apply;

	if (edit->cursor.state == cur_state_left_click)
		apply = edit->cursor.tex_select;
	else
		apply = 0;
	if (apply > 110)
	{
		if (edit->map.player_pos.x >= 0 && edit->map.player_pos.y >= 0)
		{
			edit->map.pixels[edit->map.player_pos.x
				+ edit->map.player_pos.y * edit->map.w] = 0;
		}
		edit->map.player_pos = (t_vec2i){x, y};
	}
	else if (edit->map.pixels[x + y * edit->map.w] > 110)
		edit->map.player_pos = (t_vec2i){-1, -1};
	if (apply == 109)
	{
		if (edit->map.pixels[x + y * edit->map.w] > 0)
			edit->map.pixels[x + y * edit->map.w] +=
				(edit->map.pixels[x + y * edit->map.w] % 2) * 2 - 1;
	}
	else
		edit->map.pixels[x + y * edit->map.w] = apply;
}

void		place_to_map(t_editor_inf *edit)
{
	int	x;
	int	y;

	if (cursor_in_rect(&edit->cursor, edit->map_box))
	{
		x = (edit->cursor.x - edit->map_box.x)
			/ (float)edit->map_box.w * edit->map_pos.w + edit->map_pos.x;
		y = (edit->cursor.y - edit->map_box.y)
			/ (float)edit->map_box.h * edit->map_pos.h + edit->map_pos.y;
		apply_to_map_buffer_and_potentially_update_cursor(edit, x, y);
	}
}
