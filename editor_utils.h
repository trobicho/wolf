/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:18:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/25 13:21:45 by trobicho         ###   ########.fr       */
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
}				t_editor_inf;

void	draw_tex(t_wolf *wolf, SDL_Rect rect, int tex_index);
void	editor_draw_grid(t_wolf *wolf, t_editor_inf *edit);
void	editor_map_display(t_wolf *wolf, t_editor_inf *edit);
void	place_to_map(t_editor_inf *edit);
#endif
