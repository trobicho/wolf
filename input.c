/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:04:35 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/23 09:18:19 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "player.h"

int	game_event(t_wolf *wolf)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				wolf->state = state_menu;
			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				player_rotate(&wolf->player, 0.1);
			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				player_rotate(&wolf->player, -0.1);
			else if (event.key.keysym.scancode == SDL_SCANCODE_W)
				player_walk(wolf, 0, 6);
			else if (event.key.keysym.scancode == SDL_SCANCODE_S)
				player_walk(wolf, 0, -6);
			else if (event.key.keysym.scancode == SDL_SCANCODE_A)
				player_walk(wolf, -6, 0);
			else if (event.key.keysym.scancode == SDL_SCANCODE_D)
				player_walk(wolf, 6, 0);
		}
	}
	return (0);
}

int	menu_event(t_wolf *wolf)
{
	SDL_Event	event;

	SDL_WaitEvent(&event);
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			wolf->quit = 1;
		if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
			wolf->menu.select++;
			if (wolf->menu.select >= wolf->menu.nb_entrie)
				wolf->menu.select = 0;
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_UP)
		{
			wolf->menu.select--;
			if (wolf->menu.select < 0)
				wolf->menu.select = wolf->menu.nb_entrie-1;
		}
		if (event.key.keysym.sym == SDLK_RETURN)
		{
			printf("test\n");
			if (wolf->menu.select == 0)
				wolf->state = state_game;
			else if (wolf->menu.select == 1)
				wolf->state = state_editor;
			else if (wolf->menu.select == 2)
				wolf->quit = 1;
		}
	}
	return (0);
}
