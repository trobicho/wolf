/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:55:07 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 00:05:54 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "vector.h"

void	player_walk(t_wolf *wolf, int x, int y)
{
	float	teta;
	t_vec2i	d;

	teta = wolf->player.angle;
	d.x = cos(teta) * y + sin(teta) * x;
	d.y = cos(teta) * x + sin(teta) * -y;
	wolf->player.pos.x += d.x;
	wolf->player.pos.y += d.y;
}

void	player_rotate(t_player *player, float teta)
{
	player->angle += teta;
	if (player->angle >= M_PI * 2.0)
		player->angle -= M_PI * 2.0;
	if (player->angle <= 0.0)
		player->angle += M_PI * 2.0;
}
