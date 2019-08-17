/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:04:35 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 21:50:26 by trobicho         ###   ########.fr       */
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
				if (wolf->player.cam.angle <= 0.0)
					wolf->player.cam.angle = M_PI * 2.0 - 0.1;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				wolf->player.cam.angle += 0.1;
				if (wolf->player.cam.angle >= M_PI * 2.0)
					wolf->player.cam.angle = 0.0;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_W)
			{
				wolf->player.cam.pos.y -= 1;
				printf("pos (%d, %d)\n", wolf->player.cam.pos.x, wolf->player.cam.pos.y);
				printf("pos (%d, %d)\n", wolf->player.cam.pos.x / 64, wolf->player.cam.pos.y / 64);
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S)
			{
				wolf->player.cam.pos.y += 1;
				printf("pos (%d, %d)\n", wolf->player.cam.pos.x, wolf->player.cam.pos.y);
				printf("pos (%d, %d)\n", wolf->player.cam.pos.x / 64, wolf->player.cam.pos.y / 64);
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_A)
			{
				wolf->player.cam.pos.x -= 1;
				printf("pos (%d, %d)\n", wolf->player.cam.pos.x, wolf->player.cam.pos.y);
				printf("pos (%d, %d)\n", wolf->player.cam.pos.x / 64, wolf->player.cam.pos.y / 64);
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_D)
			{
				wolf->player.cam.pos.x += 1;
				printf("pos (%d, %d)\n", wolf->player.cam.pos.x, wolf->player.cam.pos.y);
				printf("pos (%d, %d)\n", wolf->player.cam.pos.x / 64, wolf->player.cam.pos.y / 64);
			}
		}
	}
	return (0);
}
