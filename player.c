/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:55:07 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/28 14:06:38 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "vector.h"

void	player_move(t_player *player)
{
	int		x;
	int		y;
	t_vec2i	d;

	y = 0;
	x = 0;
	if (player->state & P_FORWARD)
		y += player->speed;
	if (player->state & P_BACKWARD)
		y += -player->speed;
	if (player->state & P_STRAFE_R)
		x += player->strafe_speed;
	if (player->state & P_STRAFE_L)
		x -= player->strafe_speed;
	if (player->state & P_ROTATE_L)
		player_rotate(player, 0.06);
	if (player->state & P_ROTATE_R)
		player_rotate(player, -0.06);
	d.x = cos(player->angle) * y + sin(player->angle) * x;
	d.y = cos(player->angle) * x + sin(player->angle) * -y;
	player->pos.x += d.x;
	player->pos.y += d.y;
}

void	player_rotate(t_player *player, float teta)
{
	player->angle += teta;
	if (player->angle >= M_PI * 2.0)
		player->angle -= M_PI * 2.0;
	if (player->angle <= 0.0)
		player->angle += M_PI * 2.0;
}
