/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:18:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/24 19:13:23 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_UTILS_H
# define EDITOR_UTILS_H

# include <SDL2/SDL.h>
# include "wolf.h"
# include "input.h"

void	draw_tex(t_wolf *wolf, SDL_Rect rect, int tex_index);
void	editor_map_display(t_wolf *wolf, t_map *map, SDL_Rect rect);
int		place_to_map(t_map *map, SDL_Rect rect, const t_edit_cursor *cursor);
#endif
