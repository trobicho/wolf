/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:04:35 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/25 13:46:18 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "player.h"

int	game_event(t_wolf *wolf)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			wolf->quit = 1;
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
	if (event.type == SDL_QUIT)
		wolf->quit = 1;
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

int	editor_event(t_wolf *wolf, t_edit_cursor *cursor)
{
	SDL_Event	event;

	SDL_WaitEvent(&event);
	if (event.type == SDL_QUIT)
		wolf->quit = 1;
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			wolf->state = state_menu;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_RIGHT)
			cursor->state = cur_state_right_click;
		else if (event.button.button == SDL_BUTTON_LEFT)
			cursor->state = cur_state_left_click;
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
		cursor->state = cur_state_none;
	else if (event.type == SDL_MOUSEMOTION)
	{
		cursor->x = event.button.x;
		cursor->y = event.button.y;
	}
	return (0);
}
