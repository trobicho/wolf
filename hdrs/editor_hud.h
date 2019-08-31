/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hud.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 14:31:23 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/25 15:07:17 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_HUD_H
# define EDITOR_HUD_H

# include "wolf.h"
# include "input.h"
# include "editor_utils.h"

void	draw_button(t_wolf *wolf, SDL_Rect button, Uint32 color);
void	editor_display_reset(t_wolf *wolf);
void	editor_display_hud(t_wolf *wolf, t_editor_inf *edit);
#endif
