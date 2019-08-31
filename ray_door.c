/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 20:25:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/31 01:39:07 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_utils.h"

int	lauch_door_ray(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->side_dist.x - ray->delta_dist.x / 1.8 < ray->side_dist.y)
			ray->add_float_step_to_dist = ray->step.x - ray->step.x / 1.8;
		else
		{
			ray->pos.y += ray->step.y;
			ray->side = 1;
		}
	}
	else if (ray->side == 1)
	{
		if (ray->side_dist.x < ray->side_dist.y - ray->delta_dist.y / 1.8)
		{
			ray->pos.x += ray->step.x;
			ray->side = 0;
		}
		else
			ray->add_float_step_to_dist = ray->step.y - ray->step.y / 1.8;
	}
}

int	handle_door_ray(t_wolf *wolf, t_ray *ray, t_map *map)
{
	t_door	*door;
	int		side_save;
	float 	timer;
	int		found;
	t_vec2i	pos;

	side_save = ray->side;
	door = find_that_door(wolf, ray->pos);
	lauch_door_ray(ray);
	calc_dist(ray);
	pos = ray->pos;
	if (ray->side == 0 && ray->step.x < 0 || ray->side == 1 && ray->step.y > 0)
		ray->wall_col = 1.0 - ray->wall_col;
	if (door && door->state != door_state_close && side_save == ray->side)
	{
		if (door->state == door_state_opening)
			timer =  1.0 - door->timer / 64.0;
		else if (door->state == door_state_closing)
			timer =  door->timer / 64.0;
		else if (door->state == door_state_open)
			timer = 1.0;
		if (ray->wall_col < timer)
		{
			ray->add_float_step_to_dist = 0.0;
			ray->dist = 0;
			found = launch_one_ray(wolf, ray, map);
			if (side_save != ray->side && ray->side == 0)
			{
				if (ray->pos.x - ray->step.x == pos.x && pos.y == ray->pos.y)
					found = 101;
			}
			else if (side_save != ray->side && ray->side == 1)
			{
				if (ray->pos.y - ray->step.y == pos.y && pos.x == ray->pos.x)
					found = 101;
			}
			return (found);
		}
		else
			ray->wall_col -= timer;
	}
	return (99 + (side_save != ray->side ? 2 : 0));
}
