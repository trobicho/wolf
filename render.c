/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:55:42 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 16:56:20 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	test_tex(Uint32 *pix, int w, int h)
{
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			pix[x + y * w] = 0xFF00FF;
			if (x > w / 2)
				pix[x + y * w] = 0xFFFF00;
			x++;
		}
		y++;
	}
}

void	render_one_frame(t_wolf *wolf)
{
	test_tex(wolf->display.pixels, wolf->display.width, wolf->display.height);
	SDL_UpdateTexture(wolf->display.texture, NULL, wolf->display.pixels, wolf->display.width * sizeof (Uint32));
	SDL_RenderClear(wolf->display.renderer);
	SDL_RenderCopy(wolf->display.renderer, wolf->display.texture, NULL, NULL);
	SDL_RenderPresent(wolf->display.renderer);
}
