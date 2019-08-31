/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 00:11:34 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/31 17:30:38 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "wolf.h"
# include "ray_cast.h"

void	draw_full_rect(t_display *display, SDL_Rect rect, Uint32 color);
void	draw_border(t_display *display, SDL_Rect border, Uint32 color, int w);
void	draw_unicolor_slice(t_wolf *wolf, t_ray *ray, int col, Uint32 color);
void	draw_textured_slice(t_wolf *wolf, t_ray *ray, int col, int tex_index);
#endif
