/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:04:35 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 20:33:21 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	user_event(t_wolf *wolf)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				wolf->quit = 1;
			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				wolf->player.cam.angle -= 0.1;
				if (wolf->player.cam.angle <= -M_PI * 2.0)
					wolf->player.cam.angle = 0.0;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				wolf->player.cam.angle += 0.1;
				if (wolf->player.cam.angle >= M_PI * 2.0)
					wolf->player.cam.angle = 0.0;
			}
		}
	}
	return (0);
}
