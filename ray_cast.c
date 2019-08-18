/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:56:05 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/18 02:09:40 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"
#include <math.h>

#include <stdio.h>

static int	radar[100] = {0};

static void print_radar(void)
{
	printf("\n\n\n\n------------------------\n");
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (radar[x + y * 10] == 0)
				printf(". ");
			else
				printf("%d ", radar[x + y * 10] % 10);
			radar[x + y * 10] = 0;
		}
		printf("\n");
	}
	printf("------------------------\n");
}

static int	check_hor_intesect(t_ray *ray, t_map *map)
{
	int		x_a;
	int		y_a;
	int		found;
	t_vec2i	pos;

	pos.y = (int)(ray->origin.y / map->grid_len) * map->grid_len - 1;
	if (ray->angle > M_PI)
		pos.y = (int)(ray->origin.y / map->grid_len) * map->grid_len + map->grid_len;
	pos.x = (int)(ray->origin.x + (ray->origin.y - pos.y) / tan(ray->angle));

	x_a = (int)(map->grid_len / tan((double)ray->angle));
	y_a = -map->grid_len;
	if (ray->angle > M_PI)
		y_a = map->grid_len;

	//printf("%d, %d, %lf, %d, %d\n", x_a, y_a, tan((double)ray->angle), pos.x, pos.y);
	found = 0;
	while ((found = check_grid(map, pos)) == 0)
	{
		pos.x += x_a;
		pos.y += y_a;
		if (pos.x < 0 || pos.x > map->w * map->grid_len
			|| pos.y < 0 || pos.y > map->h * map->grid_len)
		{
			ray->dist = 1000;
			return (-1);
		}
		radar[pos.x / map->grid_len + (pos.y / map->grid_len) * 10] = 1;
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

	pos.x = (ray->origin.x / map->grid_len) * map->grid_len + map->grid_len;
	if (ray->angle > M_PI / 2.0 && ray->angle < M_PI + M_PI / 2.0)
		pos.x = (ray->origin.x / map->grid_len) * map->grid_len - 1;
	pos.y = (int)(ray->origin.y + (ray->origin.x - pos.x) * tan(ray->angle));

	x_a = map->grid_len;
	if (ray->angle > M_PI / 2.0 && ray->angle < M_PI + M_PI / 2.0)
		x_a = -map->grid_len;
	y_a = (int)(map->grid_len * tan((double)ray->angle));

	//printf("%d, %d, %lf, %d, %d\n", x_a, y_a, tan((double)ray->angle), pos.x, pos.y);
	found = 0;
	while (1)
	{
		if (pos.x < 0 || pos.x > map->w * map->grid_len
			|| pos.y < 0 || pos.y > map->h * map->grid_len)
		{
			ray->dist = 1000;
			return (-1);
		}
		if ((found = check_grid(map, pos)))
			break;
		if (radar[pos.x / map->grid_len + (pos.y / map->grid_len) * 10] == 1
			|| radar[pos.x / map->grid_len + (pos.y / map->grid_len) * 10] == 6)
			radar[pos.x / map->grid_len + (pos.y / map->grid_len) * 10] = 6;
		else
			radar[pos.x / map->grid_len + (pos.y / map->grid_len) * 10] = 5;
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
	found_ver = check_ver_intesect(&ray_ver, map);
	found_hor = check_hor_intesect(&ray_hor, map);
	if (ray_ver.dist < ray_hor.dist)
	{
		*ray = ray_ver;
		if (found_ver == -1)
			return (found_ver);
		else
			return (1);
	}
	else
	{
		*ray = ray_hor;
		if (found_hor == -1)
			return (found_hor);
		else
			return (2);
	}
	return (0);
}

static void	draw_unicolor_slice(t_wolf *wolf, t_ray ray, int col, Uint32 color)
{
	int	height;
	int	y_slice;
	int	y;

	height = (128.0 / ray.dist) * 255;
	if (height > wolf->display.height)
		height = wolf->display.height;
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
	int		found;
	t_ray	ray;

	col = 0;
	teta_cur = wolf->player.cam.angle - wolf->player.cam.fov / 2.0;
	teta_add = wolf->player.cam.fov / (float)wolf->display.width;
	while (col < wolf->display.width)
	{
		if (teta_cur < -0.0)
			teta_cur += M_PI * 2.0;
		else if (teta_cur > M_PI * 2.0)
			teta_cur -= M_PI * 2.0;
		ray.origin = wolf->player.cam.pos;
		ray.angle = teta_cur;
		ray.dist = 0;
		if ((found = send_one_ray(&ray, &wolf->map)))
		{
			if (found == -1)
				draw_unicolor_slice(wolf, ray, col, 0x0);
			else if (found == 1)
				draw_unicolor_slice(wolf, ray, col, 0x0FF00);
			else if (found == 2)
				draw_unicolor_slice(wolf, ray, col, 0x000FF);
		}
		teta_cur += teta_add;
		col++;
	}
	print_radar();
}
