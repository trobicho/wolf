/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 20:25:10 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/06 21:45:13 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_utils.h"

static int	search_perpendicular_to_ray(t_ray *ray, t_map *map)
{
	t_vec2i	pos_perp;

	pos_perp = ray->pos;
	if (ray->side == 0)
		pos_perp.x -= ray->step.x * 2;
	else
		pos_perp.y -= ray->step.y * 2;
	return (map->pixels[pos_perp.x + pos_perp.y * map->w]);
}

void		launch_div_ray(t_ray *ray, float div)
{
	if (ray->side == 0)
	{
		if (ray->side_dist.x - ray->delta_dist.x * (1.0 - div)
			< ray->side_dist.y)
			ray->add_float_step_to_dist = ray->step.x * div;
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->pos.y += ray->step.y;
			ray->side = 1;
		}
	}
	else if (ray->side == 1)
	{
		if (ray->side_dist.x < ray->side_dist.y
			- ray->delta_dist.y * (1.0 -  div))
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos.x += ray->step.x;
			ray->side = 0;
		}
		else
			ray->add_float_step_to_dist = ray->step.y * div;
	}
}

int			send_ray_through_door(t_wolf *wolf, t_ray *ray, t_map *map)
{
	int		found;
	int		side_save;
	t_vec2i	pos;

	pos = ray->pos;
	side_save = ray->side;
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

int			handle_door_ray(t_wolf *wolf, t_ray *ray, t_map *map)
{
	t_door	*door;
	int		side_save;
	float	timer;
	int		found;

	side_save = ray->side;
	door = find_that_door(wolf, ray->pos);
	launch_div_ray(ray, 0.45);
	calc_dist(ray);
	if ((ray->side == 0 && ray->side == side_save && ray->step.x < 0)
		|| (ray->side == 1 && ray->side == side_save && ray->step.y > 0))
		ray->wall_col = 1.0 - ray->wall_col;
	if (door && door->state != door_state_close && side_save == ray->side)
	{
		if (door->state == door_state_opening)
			timer = 1.0 - door->timer / 64.0;
		else if (door->state == door_state_closing)
			timer = door->timer / 64.0;
		else if (door->state == door_state_open
			|| door->state == door_state_waiting_for_player_to_move_is_ass)
			timer = 1.0;
		return (ray_special_3d_door(wolf, ray, map, timer));
	}
	if ((found = map->pixels[ray->pos.x + ray->pos.y * map->w]) == 101)
		found = 99;
	return ((side_save != ray->side ? 101 : found));
}

int			handle_ray_in_door(t_wolf *wolf, t_ray *ray, t_map *map)
{
	int		found;

	if (is_found_door(map->pixels[ray->pos.x + ray->pos.y * map->w]))
	{
		ray_step(ray);
		if ((found = map->pixels[ray->pos.x + ray->pos.y * map->w]) > 0
			&& is_found_door(found) == 0)
		{
			calc_dist(ray);
			if (search_perpendicular_to_ray(ray, map))
				return (101);
			return (found);
		}
		else if (is_found_door(found))
			return (handle_door_ray(wolf, ray, map));
		return (found);
	}
	return (0);
}
