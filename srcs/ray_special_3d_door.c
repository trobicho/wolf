/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_special_3d_door.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 02:03:52 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/07 02:16:26 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_utils.h"
#include <math.h>

static int	check_if_pass_through_door(t_ray *ray, float perp_dist)
{
	float	factor;
	float	d_proj;

	if (ray->side == 0)
		factor = ft_abs(ray->vec.x);
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

static int	calc_if_pass_through_secret_door(t_ray *ray, t_secret_door *sdoor
	, float timer)
{
	float	d_proj;
	float	factor;
	float	perp_dist;

	if (ray->side == 0)
		factor = ft_abs(ray->vec.x);
	else
		factor = ft_abs(ray->vec.y);
	if (ray->side == 0 && ray->step.y == sdoor->dir.y)
		perp_dist = ft_abs(ray->delta_dist.y * (timer - ray->wall_col));
	else if (ray->side == 1 && ray->step.x == sdoor->dir.x)
		perp_dist = ft_abs(ray->delta_dist.x * (timer - ray->wall_col));
	else
		return (1);
	d_proj = factor * perp_dist;
	if (d_proj < 1.0)
	{
		ray->dist += perp_dist;
		ray->side = 1 - ray->side;
		ray->wall_col = d_proj;
		return (0);
	}
	return (1);
}

static int	check_if_pass_through_secret_door(t_ray *ray, t_secret_door *sdoor)
{
	float	timer;
	int		invert_wall_col;

	if ((ray->side == 0 && ray->step.x * sdoor->dir.y < 0)
		|| (ray->side == 1 && ray->step.y * sdoor->dir.x > 0))
	{
		timer = sdoor->timer / 64.0;
		invert_wall_col = 0;
		if (ray->wall_col < timer)
			return (0);
	}
	else
	{
		timer = 1.0 - sdoor->timer / 64.0;
		invert_wall_col = 1;
		if (ray->wall_col > timer)
			return (0);
	}
	if (calc_if_pass_through_secret_door(ray, sdoor, timer) == 0)
	{
		if (invert_wall_col)
			ray->wall_col = 1.0 - ray->wall_col;
		return (0);
	}
	return (1);
}

int			ray_special_3d_door(t_wolf *wolf, t_ray *ray, t_map *map
	, float timer)
{
	float	perp_dist;
	int		found;

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
	if ((found = map->pixels[ray->pos.x + ray->pos.y * map->w]) == 101)
		found = 99;
	return (found);
}

int			handle_secret_door_ray(t_ray *ray, t_map *map
	, t_secret_door *sdoor)
{
	int		found;
	int		side_save;
	float	timer;

	timer = 1.0 - sdoor->timer / 64.0;
	side_save = ray->side;
	found = map->pixels[ray->pos.x + ray->pos.y * map->w];
	if ((ray->side == 0 && sdoor->dir.x != 0)
		|| (ray->side == 1 && sdoor->dir.y != 0))
	{
		if ((ray->side == 0 && sdoor->dir.x == ray->step.x)
			|| (ray->side == 1 && sdoor->dir.y == ray->step.y))
		{
			launch_div_ray(ray, 1.0 - sdoor->timer / 64.0);
			found = map->pixels[ray->pos.x + ray->pos.y * map->w];
		}
	}
	else
	{
		calc_dist(ray);
		if (check_if_pass_through_secret_door(ray, sdoor))
			return ((int)(ray->dist = 0));
	}
	return (found);
}
