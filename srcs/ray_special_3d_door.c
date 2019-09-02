/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_special_3d_door.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 02:03:52 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/02 20:31:27 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_utils.h"
#include <math.h>

static int	check_if_pass_through_door(t_ray *ray, float perp_dist)
{
	float	factor;
	float	d_proj;

	if (ray->side == 0)
	{
		factor = ft_abs(ray->vec.x);
	}
	else
		factor = ft_abs(ray->vec.y);
	d_proj = factor * perp_dist;
	if (d_proj < 0.1)
	{
		ray->wall_col = 0.45 + d_proj;
		if (ray->wall_col > 0.546)
			ray->wall_col = 0.546;
		else if (ray->wall_col < 0.458)
			ray->wall_col = 0.458;
		return (1);
	}
	return (0);
}

int			ray_special_3d_door(t_wolf *wolf, t_ray *ray, t_map *map
	, float timer)
{
	float	perp_dist;

	if (timer == 1.0)
		return (send_ray_through_door(wolf, ray, map));
	else if (ray->wall_col < timer)
	{
		if (ray->side == 0 && ray->step.y > 0)
			perp_dist = ray->delta_dist.y * (timer - ray->wall_col);
		else if (ray->side == 1 && ray->step.x > 0)
			perp_dist = ray->delta_dist.x * (timer - ray->wall_col);
		else
			return (send_ray_through_door(wolf, ray, map));
		if (check_if_pass_through_door(ray, perp_dist))
		{
			ray->side = 1 - ray->side;
			ray->dist += perp_dist;
			return (101);
		}
		return (send_ray_through_door(wolf, ray, map));
	}
	ray->wall_col -= timer;
	return (99);
}
