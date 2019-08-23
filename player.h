/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:55:12 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/23 06:37:53 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

#include "wolf.h"

void	player_walk(t_wolf *wolf, int x, int y); //float ? <=(1/frame)
void	player_rotate(t_player *player, float teta);
# endif
