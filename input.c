/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:04:35 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/29 05:43:42 by trobicho         ###   ########.fr       */
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
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				wolf->state = state_menu;
			else
				player_handle_event_keydown(wolf, &event);
		}
		if (event.type == SDL_KEYUP)
		{
			player_handle_event_keydup(wolf, &event);
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
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE
			&& event.key.repeat == 0)
			wolf->quit = 1;
		else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			wolf->menu.select++;
		else if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			wolf->menu.select--;
		else if (event.key.keysym.sym == SDLK_RETURN
			&& event.key.repeat == 0)
		{
			if (wolf->menu.select == 0)
				wolf->state = state_game;
			else if (wolf->menu.select == 1)
				wolf->state = state_editor;
			else if (wolf->menu.select == 2)
				wolf->quit = 1;
		}
		if (wolf->menu.select < 0)
			wolf->menu.select = wolf->menu.nb_entrie - 1;
		else if (wolf->menu.select >= wolf->menu.nb_entrie)
			wolf->menu.select = 0;
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
