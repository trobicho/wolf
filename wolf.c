/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:18:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/20 20:05:12 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "input.h"
#include "render.h"
#include "physic.h"

int		game_loop(t_wolf *wolf)
{
	t_ppm_tex_4bpp	tex_test;

	if (ppm_load_4bpp("./texture/tile.pbm", &tex_test))
		return (-1);
	while (!wolf->quit)
	{
		user_event(wolf);
		physic_check(wolf);
		render_one_frame(wolf);
	}
	return (0);
}
