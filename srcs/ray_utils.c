/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 01:35:54 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/03 06:12:06 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "map.h"
#include "vector.h"
#include "ray_utils.h"

void	calc_dist(t_ray *ray)
{
	t_vec2f	pos;

	pos = (t_vec2f){(float)ray->pos.x, (float)ray->pos.y};
	if (ray->side == 0)
	{
		pos.x += ray->add_float_step_to_dist;
		ray->dist = (pos.x - ray->origin.x + (1 - ray->step.x) / 2.0)
			/ ray->vec.x;
		ray->wall_col = ray->origin.y + ray->dist * ray->vec.y;
		ray->wall_col -= (int)ray->wall_col;
		if (ray->step.x < 0)
			ray->wall_col = 1.0 - ray->wall_col;
	}
	else
	{
		pos.y += ray->add_float_step_to_dist;
		ray->dist = (pos.y - ray->origin.y + (1 - ray->step.y) / 2.0)
			/ ray->vec.y;
		ray->wall_col = ray->origin.x + ray->dist * ray->vec.x;
		ray->wall_col -= (int)ray->wall_col;
		if (ray->step.y > 0)
			ray->wall_col = 1.0 - ray->wall_col;
	}
}

void	ray_step(t_ray *ray)
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

int		handle_ray_search(t_wolf *wolf, t_ray *ray, t_map *map)
{
	int		found;
	t_door	*door;

	door = NULL;
	if ((found = map->pixels[ray->pos.x + ray->pos.y * map->w]) == 0)
		return (0);
	if (found < 0)
		return (-1);
	if (is_found_door(found))
	{
		found = handle_door_ray(wolf, ray, map);
	}
	return (found);
}

t_vec2f	calc_ray_plane(t_wolf *wolf, t_ray *ray)
{
	t_vec2f	dir;

	dir.x = cos(wolf->player.angle);
	dir.y = -sin(wolf->player.angle);
	ray->plane.x = (dir.x * cos(M_PI / 2.0) + dir.y * -sin(M_PI / 2.0))
		* (wolf->player.fov / M_PI);
	ray->plane.y = (dir.y * cos(M_PI / 2.0) + dir.x * sin(M_PI / 2.0))
		* (wolf->player.fov / M_PI);
	return (dir);
}
