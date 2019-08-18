/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:55:07 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/18 00:44:41 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "vector.h"

void	walk(t_wolf *wolf, int x, int y)
{
	float	teta;
	t_vec2i	d;

	teta = wolf->player.cam.angle;
	d.x = cos(teta) * y + sin(teta) * x;
	d.y = cos(teta) * -x + sin(teta) * -y;
	wolf->player.cam.pos.x += d.x;
	wolf->player.cam.pos.y += d.y;
}
