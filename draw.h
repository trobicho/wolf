/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 00:11:34 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 00:23:53 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "wolf.h"

void	draw_full_rect(t_display *display, SDL_Rect rect, Uint32 color);
void	draw_border(t_display *display, SDL_Rect border, Uint32 color, int w);
#endif
