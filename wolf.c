/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 14:18:33 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/20 21:00:30 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "input.h"
#include "render.h"
#include "physic.h"
#include "libft.h"

int		game_loop(t_wolf *wolf)
{
	t_ppm_tex_4bpp	tex_test;

	tex_test.blend = 0xFF00FF;
	if (ppm_load_4bpp("./texture/tile.pbm", &tex_test))
		return (-1);
	while (!wolf->quit)
	{
		user_event(wolf);
		physic_check(wolf);
		/*
		render_one_frame(wolf);
		*/
		//test-------------
		for (int y = 0; y < ((tex_test.h < wolf->display.height - 10)
				? tex_test.h : wolf->display.height - 10); y++)
		{
			ft_memcpy(&wolf->display.pixels[(y + 10) * wolf->display.width + 10], &tex_test.pixels[y * tex_test.w], tex_test.w * 4);
		}
		SDL_UpdateTexture(wolf->display.texture, NULL, wolf->display.pixels, wolf->display.width * sizeof (Uint32));
		SDL_RenderClear(wolf->display.renderer);
		SDL_RenderCopy(wolf->display.renderer, wolf->display.texture, NULL, NULL);
		SDL_RenderPresent(wolf->display.renderer);
		//test-------------
	}
	return (0);
}
