/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 20:25:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/30 21:08:51 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_utils.h"

int	lauch_door_ray(t_ray *ray)
{
	if (ray->side == 0 && ray->side_dist.x - ray->delta_dist.x / 1.8
		< ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x - ray->delta_dist.x / 1.8;
		ray->origin.x -= ray->step.x / 1.8;
		ray->side = 0;
	}
	else if (ray->side == 0)
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->pos.y += ray->step.y;
		ray->side = 1;
	}
}

int	handle_door_ray(t_wolf *wolf, t_ray *ray, t_map *map)
{
	t_door	*door;

	if ((door = find_that_door(wolf, ray->pos)) != NULL
		&& door->state == door_state_open)
		return (launch_one_ray(wolf, ray, map));
	else
		lauch_door_ray(ray);
	/*
	if (door && door->state != door_state_close && side_save == ray->side)
	{
		calc_dist(ray);
		float timer;
		if (door->state == door_state_opening)
			timer =  1.0 - door->timer / 64.0;
		else if (door->state == door_state_closing)
			timer =  door->timer / 64.0;
		if (ray->wall_col < timer)
		{
			*ray = ray_copy;
			return (launch_one_ray(wolf, ray, map));
		}
		else
			ray->wall_col -= timer;
	}
	*/
	return (99);
}
