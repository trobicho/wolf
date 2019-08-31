/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:55:12 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/29 05:40:09 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "wolf.h"

void	player_move(t_player *player);
void	player_rotate(t_player *player, float teta);
int		player_handle_event_keydown(t_wolf *wolf, SDL_Event *event);
int		player_handle_event_keydup(t_wolf *wolf, SDL_Event *event);
#endif
