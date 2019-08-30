/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 01:35:54 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/30 21:20:31 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_utils.h"

static void calc_dist(t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->dist = (ray->pos.x - ray->origin.x + (1 - ray->step.x) / 2.0)
			/ ray->vec.x;
		ray->wall_col = ray->origin.y + ray->dist * ray->vec.y;
	}
	else
	{
		ray->dist = (ray->pos.y - ray->origin.y + (1 - ray->step.y) / 2.0)
			/ ray->vec.y;
		ray->wall_col = ray->origin.x + ray->dist * ray->vec.x;
	}
	ray->wall_col -= (int)ray->wall_col;
}

void		ray_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->pos.x += ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->pos.y += ray->step.y;
		ray->side = 1;
	}
}

int			handle_ray_search(t_wolf *wolf, t_ray *ray, t_map *map)
{
	int		found;
	int		side_save;
	t_door	*door;
	t_ray	ray_copy = *ray;

	door = NULL;
	side_save = ray->side;
	if ((found = map->pixels[ray->pos.x + ray->pos.y * map->w]) == 0)
		return (0);
	if (found < 0)
		return (-1);
	if (is_found_door(found))
	{
		t_vec2i pos = ray->pos;
		if ((door = find_that_door(wolf, pos)) != NULL
			&& door->state == door_state_open)
			return (launch_one_ray(wolf, ray, map));
		else
		{
			if (ray->side == 0)
				ray->side_dist.x -= ray->delta_dist.x / 1.8;
			else
				ray->side_dist.y -= ray->delta_dist.y / 1.8;
			ray_step(ray);
			if (side_save == ray->side && ray->side == 0)
				ray->origin.x += ray->step.x / 1.8;
			if (side_save == ray->side && ray->side == 1)
				ray->origin.y += ray->step.y / 1.8;
			found = 99 + (side_save != ray->side ? 2 : 0);
		}
	}
	calc_dist(ray);
	if (door && door->state != door_state_close && side_save == ray->side)
	{
			float timer; 
		if (door->state == door_state_opening)
			timer = 1.0 - door->timer / 64.0;
		else
			timer = door->timer / 64.0;
		if (ray->wall_col < timer)
		{
			*ray = ray_copy;
			return (launch_one_ray(wolf, ray, map));
		}
		else
			ray->wall_col -= timer;
	}
	return (found + ray->side);
}
