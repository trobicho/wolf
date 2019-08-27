/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 13:22:16 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 13:28:42 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"

t_vec2i	calc_step(t_ray *ray, t_map *map, t_vec2i *delta_dist, t_vec2i *step)
{
	int		x_a;
	int		y_a;
	t_vec2i	pos;
	t_vec2i	side_dist;

	pos.y = (int)(ray->origin.y / 64) * 64 - 1;
	if (ray->angle > M_PI)
		pos.y = (int)(ray->origin.y / 64) * 64 + 64;
	pos.x = (ray->origin.x / 64) * 64 + 64;
	if (ray->angle > M_PI / 2.0 && ray->angle < M_PI + M_PI / 2.0)
		pos.x = (ray->origin.x / 64) * 64 - 1;
	side_dist.y = pos.y - ray->origin.y;
	if (side_dist.y < 0)
		side_dist.y = -side_dist.y;
	side_dist.x = pos.x - ray->origin.x;
	if (side_dist.x < 0)
		side_dist.x = -side_dist.x;
	step->y = -64;
	if (ray->angle > M_PI)
		step->y = 64;
	step->x = 64;
	if (ray->angle > M_PI / 2.0 && ray->angle < M_PI + M_PI / 2.0)
		step->x = -64;
	delta_dist->x = (int)(64.0f * ray->tan_calc);
	delta_dist->y = (int)(64.0f / ray->tan_calc);
	delta_dist->x = sqrt(delta_dist->x * delta_dist->x + step->x * step->x);
	delta_dist->y = sqrt(delta_dist->y * delta_dist->y + step->y * step->y);
	side_dist.x = delta_dist->x * (side_dist.x / 64.0f);
	side_dist.y = delta_dist->y * (side_dist.y / 64.0f);
	return (side_dist);
}
