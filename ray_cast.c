/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:56:05 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 20:08:30 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"
#include <math.h>

#include <stdio.h>
static int	check_hor_intesect(t_ray *ray, t_map *map)
{
	int		x_a;
	int		y_a;
	int		found;
	t_vec2i	pos;

	pos.y = (ray->origin.y / map->grid_len) * map->grid_len - 1;
	pos.x = ray->origin.x + (ray->origin.y - pos.y) * tan(ray->angle);
	x_a = map->grid_len / tan((double)ray->angle);
	y_a = map->grid_len;
	//printf("%d, %d, %lf, %d, %d\n", x_a, y_a, tan((double)ray->angle), pos.x, pos.y);
	found = 0;
	while ((found = check_grid(map, pos)) == 0)
	{
		pos.x += x_a;
		pos.y += y_a;
	}
	//printf("pos: %d, %d\n", pos.x, pos.y);
	ray->dist = sqrt((ray->origin.x - pos.x) * (ray->origin.x - pos.x)
		+ (ray->origin.y - pos.y) * (ray->origin.y - pos.y));
	ray->pos = pos;
	return (found);
}

static int	check_ver_intesect(t_ray *ray, t_map *map)
{
	int		x_a;
	int		y_a;
	int		found;
	t_vec2i	pos;

	pos.x = (ray->origin.x / map->grid_len) * map->grid_len - 1;
	pos.x = ray->origin.y + (ray->origin.x - pos.x) * tan(ray->angle);
	x_a = map->grid_len;
	y_a = map->grid_len * tan((double)ray->angle);
	//printf("%d, %d, %lf, %d, %d\n", x_a, y_a, tan((double)ray->angle), pos.x, pos.y);
	found = 0;
	while ((found = check_grid(map, pos)) == 0)
	{
		pos.x += x_a;
		pos.y += y_a;
	}
	//printf("pos: %d, %d\n", pos.x, pos.y);
	ray->dist = sqrt((ray->origin.x - pos.x) * (ray->origin.x - pos.x)
		+ (ray->origin.y - pos.y) * (ray->origin.y - pos.y));
	ray->pos = pos;
	return (found);
}

static int	send_one_ray(t_ray *ray, t_map *map)
{
	t_ray	ray_hor;
	t_ray	ray_ver;
	int		found_hor;
	int		found_ver;

	ray_hor = *ray;
	ray_ver = *ray;
	if (ray->angle > 0.1 || ray->angle < -0.1)
		found_hor = check_hor_intesect(&ray_hor, map);
	found_ver = check_ver_intesect(&ray_ver, map);
	if (ray_ver.dist < ray_hor.dist)
	{
		*ray = ray_ver;
		return (found_ver);
	}
	else
	{
		*ray = ray_hor;
		return (found_hor);
	}
	return (0);
}

static void	draw_unicolor_slice(t_wolf *wolf, t_ray ray, int col, Uint32 color)
{
	int	height;
	int	y_slice;
	int	y;

	height = (128.0 / ray.dist) * 255;
	y_slice = 0;
	y = wolf->display.height / 2 - height / 2;
	//printf("%d %d\n", ray.dist, height);
	while (y_slice < height)
	{
		wolf->display.pixels[col + y * wolf->display.width] = color;
		//printf("%d\n", col + y * wolf->display.width);
		y_slice++;
		y++;
	}
}

void		ray_cast(t_wolf *wolf)
{
	int		col;
	float	teta_cur;
	float	teta_add;
	t_ray	ray;

	col = 0;
	teta_cur = wolf->player.cam.angle - wolf->player.cam.fov;
	teta_add = wolf->player.cam.fov / (float)wolf->display.width;
	while (col < wolf->display.width)
	{
		ray.origin = wolf->player.cam.pos;
		ray.angle = teta_cur;
		ray.dist = 0;
		if (send_one_ray(&ray, &wolf->map))
		{
			draw_unicolor_slice(wolf, ray, col, 0x00FF00);
		}
		teta_cur += teta_add;
		col++;
	}
}
