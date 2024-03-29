/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:18:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/01 23:12:28 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_UTILS_H
# define EDITOR_UTILS_H

# include <SDL2/SDL.h>
# include "wolf.h"
# include "input.h"

typedef struct	s_editor_inf
{
	t_edit_cursor	cursor;
	t_map			map;
	SDL_Rect		map_box;
	SDL_Rect		map_pos;
	SDL_Rect		panel;
	SDL_Rect		save_button;
	SDL_Rect		erase_button;
	int				button_select;
	int				max_id;
}				t_editor_inf;

void			draw_tex(t_wolf *wolf, SDL_Rect rect, int tex_index);
void			editor_draw_grid(t_wolf *wolf, t_editor_inf *edit);
void			editor_map_display(t_wolf *wolf, t_editor_inf *edit);
void			place_to_map(t_editor_inf *edit);
int				cursor_in_rect(t_edit_cursor *cursor, SDL_Rect rect);
void			place_to_map(t_editor_inf *edit);
int				handle_button_click(t_editor_inf *edit, SDL_Rect button
	, int state, int (*f)(t_map *map));
#endif
