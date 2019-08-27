/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 18:10:55 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 14:27:20 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"
#include "draw.h"

static int	send_one_ray(t_ray *ray, t_map *map)
{
	t_vec2i	pos;
	t_vec2i	step;
	t_vec2i	delta_dist;
	t_vec2i	side_dist;
	int		found;
	int		side;
	int		dx, dy;

	side_dist = calc_step(ray, map, &delta_dist, &step);
	pos = ray->origin;
	if ((found = check_grid(map, pos)))
	{
		ray->dist = 1;
		return (1);
	}
	found = 0;
	int iter = 0;
	while (1)
	{
		if (pos.x < 0 || pos.x >= map->w * 64
			|| pos.y < 0 || pos.y >= map->h * 64)
		{
			ray->dist = 1000;
			return (-1);
		}
		if ((unsigned int)(side_dist.x)
			< (unsigned int)(side_dist.y))
		{
			side_dist.x += delta_dist.x;
			pos.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			pos.y += step.y;
			side = 1;
		}
		if ((found = check_grid(map, pos)))
			break;
		iter++;
	}
	if (side == 0)
	{
		ray->dist = side_dist.x - delta_dist.x;
		ray->dist *= cos(ray->beta);
		if (pos.x - ray->origin.x < 0)
			dx = ray->origin.x - (pos.x / 64) * 64 - 63;
		else
			dx = ray->origin.x - (pos.x / 64) * 64;
		pos.y = ray->origin.y + dx * ray->tan_calc;
		ray->wall_w = pos.y % 64;
		if (ray->wall_w < 0)
			ray->wall_w = -ray->wall_w;
	}
	else
	{
		ray->dist = side_dist.y - delta_dist.y;
		ray->dist *= cos(ray->beta);
		if (pos.y - ray->origin.y < 0)
			dy = ray->origin.y - (pos.y / 64) * 64 - 63;
		else
			dy = ray->origin.y - (pos.y / 64) * 64;
		pos.x = ray->origin.x + dy / ray->tan_calc;
		ray->wall_w = pos.x % 64;
		if (ray->wall_w < 0)
			ray->wall_w = -ray->wall_w;
	}
	found = (found == -1) ? -1 : found + side;
	return (found);
}

void		ray_cast(t_wolf *wolf)
{
	int		col;
	float	teta_cur;
	float	teta_add;
	int		found;
	t_ray	ray;
	int		wider;

	col = 0;
	ray.beta = wolf->player.fov / 2.0;
	teta_cur = wolf->player.angle + wolf->player.fov / 2.0;
	teta_add = -wolf->player.fov / (float)wolf->display.width;
	while (col < wolf->display.width)
	{
		if (teta_cur <= 0.001)
			teta_cur = (M_PI * 2.0 ) + teta_cur;
		else if (teta_cur >= M_PI * 2.0)
			teta_cur -= M_PI * 2.0;
		ray.origin = wolf->player.pos;
		ray.angle = teta_cur;
		ray.dist = 0;
		ray.tan_calc = tan(teta_cur);
		wider = (wolf->map.w > wolf->map.h ? wolf->map.w : wolf->map.h) * 64;
		if (ray.tan_calc < 1.0 / wider && ray.tan_calc > -1.0 / wider)
			ray.tan_calc = (ray.tan_calc < -0.0) ? -1.0 / wider : 1.0 / wider;
		if (ray.tan_calc > wider || ray.tan_calc < -wider)
			ray.tan_calc = (ray.tan_calc < -0.0) ? -wider : wider;
		if ((found = send_one_ray(&ray, &wolf->map)))
		{
			if (found == -1)
				draw_unicolor_slice(wolf, ray, col, 0x0);
			else
				draw_textured_slice(wolf, &ray, col, found - 1);
		}
		ray.beta += teta_add;
		teta_cur += teta_add;
		col++;
	}
}
