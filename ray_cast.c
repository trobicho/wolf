/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_redo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 18:10:55 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/18 21:11:24 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"

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

static void	put_in_radar(t_vec2i pos, t_map *map, int c)
{
	if (radar[pos.x / map->grid_len + (pos.y / map->grid_len) * 10] != c
		&& radar[pos.x / map->grid_len + (pos.y / map->grid_len) * 10] != 0)
	{
		radar[pos.x / map->grid_len + (pos.y / map->grid_len) * 10] = 6;
	}
	else
		radar[pos.x / map->grid_len + (pos.y / map->grid_len) * 10] = c;
}

static t_vec2i	calc_step(t_ray *ray, t_map *map, t_vec2i *delta_dist, t_vec2i *step)
{
	int		x_a;
	int		y_a;
	t_vec2i	pos;
	t_vec2i	side_dist;

	pos.y = (int)(ray->origin.y / map->grid_len) * map->grid_len - 1;
	if (ray->angle > M_PI)
		pos.y = (int)(ray->origin.y / map->grid_len) * map->grid_len + map->grid_len;
	side_dist.y = pos.y - ray->origin.y;
	if (side_dist.y < 0)
		side_dist.y = -side_dist.y;

	pos.x = (ray->origin.x / map->grid_len) * map->grid_len + map->grid_len;
	if (ray->angle > M_PI / 2.0 && ray->angle < M_PI + M_PI / 2.0)
		pos.x = (ray->origin.x / map->grid_len) * map->grid_len - 1;
	side_dist.x = pos.x - ray->origin.x;
	if (side_dist.x < 0)
		side_dist.x = -side_dist.x;
	
	delta_dist->x = (int)(map->grid_len / tan((double)ray->angle));
	step->y = -map->grid_len;
	if (ray->angle > M_PI)
		step->y = map->grid_len;
	delta_dist->y = (int)(map->grid_len * tan((double)ray->angle));
	step->x = map->grid_len;
	if (ray->angle > M_PI / 2.0 && ray->angle < M_PI + M_PI / 2.0)
		step->x = -map->grid_len;
	delta_dist->x = sqrt(delta_dist->x * delta_dist->x + step->y * step->y);
	delta_dist->y = sqrt(delta_dist->y * delta_dist->y + step->x * step->x);
	return (side_dist);
}

static int	send_one_ray(t_ray *ray, t_map *map)
{
	t_vec2i	pos;
	t_vec2i	step;
	t_vec2i	delta_dist;
	t_vec2i	side_dist;
	int		found;
	int		side;

	side_dist = calc_step(ray, map, &delta_dist, &step);
	pos = ray->origin;
	found = 0;
	while (1)
	{
		if (pos.x < 0 || pos.x >= map->w * map->grid_len
			|| pos.y < 0 || pos.y >= map->h * map->grid_len)
		{
			ray->dist = 1000;
			return (-1);
		}
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			pos.x += step.x;
			side = 1;
		}
		else
		{
			side_dist.y += delta_dist.y;
			pos.y += step.y;
			side = 2;
		}
		//printf("side_dist {%d, %d}\n", side_dist.x, side_dist.y);
		if ((found = check_grid(map, pos)))
			break;
		put_in_radar(pos, map, 1);
	}
	ray->dist = sqrt((ray->origin.x - pos.x) * (ray->origin.x - pos.x)
		+ (ray->origin.y - pos.y) * (ray->origin.y - pos.y));
	found = (found == -1) ? found : side;
	return (found);
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
				draw_unicolor_slice(wolf, ray, col, 0x000FF);
			else if (found == 2)
				draw_unicolor_slice(wolf, ray, col, 0x0FF00);
		}
		teta_cur += teta_add;
		col++;
	}
	print_radar();
}
