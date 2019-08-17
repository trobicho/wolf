/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:18:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 16:53:15 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "input.h"
#include "render.h"

int		game_loop(t_wolf *wolf)
{
	while (!wolf->quit)
	{
		user_event(wolf);
		render_one_frame(wolf);
	}
	return (0);
}
