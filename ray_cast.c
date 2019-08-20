/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 18:10:55 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/20 05:19:36 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"

static int	radar[100] = {0};

static void print_radar(void)
{
	printf("------------------------\n");
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (radar[x + y * 10] == 0)
				printf(". ");
			else if (radar[x + y * 10] < 10)
				printf("%d ", radar[x + y * 10] % 10);
			else
				printf("%c ", (char)radar[x + y * 10]);
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
		return ;
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
	double	tan_calc;
	int		wider;

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
	
	step->y = -map->grid_len;
	if (ray->angle > M_PI)
		step->y = map->grid_len;
	step->x = map->grid_len;
	if (ray->angle > M_PI / 2.0 && ray->angle < M_PI + M_PI / 2.0)
		step->x = -map->grid_len;
	wider = ((map->w > map->h) ? map->w : map->h) * map->grid_len;
	tan_calc = tan(ray->angle);
	if (tan_calc < 1.0 / wider && tan_calc > -1.0 / wider)
		delta_dist->y = (int)(wider + 1);
	else
		delta_dist->y = (int)(map->grid_len / tan_calc);
	if (tan_calc > wider || tan_calc < -wider)
		delta_dist->x = (int)(wider + 1);
	else
		delta_dist->x = (int)(map->grid_len * tan_calc);
	delta_dist->x = sqrt(delta_dist->x * delta_dist->x + step->x * step->x);
	delta_dist->y = sqrt(delta_dist->y * delta_dist->y + step->y * step->y);
	side_dist.x = delta_dist->x * (side_dist.x / (float)map->grid_len);
	side_dist.y = delta_dist->y * (side_dist.y / (float)map->grid_len);
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
	put_in_radar(pos, map, '*');
	if ((found = check_grid(map, pos)))
	{
		ray->dist = 1;
		return (1);
	}
	found = 0;
	int iter = 0;
	while (1)
	{
		if (pos.x < 0 || pos.x >= map->w * map->grid_len
			|| pos.y < 0 || pos.y >= map->h * map->grid_len)
		{
			ray->dist = 1000;
			return (-1);
		}
		if ((unsigned int)(side_dist.x)
			< (unsigned int)(side_dist.y))
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
		put_in_radar(pos, map, iter);
		iter++;
	}
	if (side == 1)
		ray->dist = side_dist.x - delta_dist.x;
	else
		ray->dist = side_dist.y - delta_dist.y;
		/*
	ray->dist = sqrt((ray->origin.x - pos.x) * (ray->origin.x - pos.x)
		+ (ray->origin.y - pos.y) * (ray->origin.y - pos.y));
		*/
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
	teta_cur = wolf->player.cam.angle + wolf->player.cam.fov / 2.0;
	teta_add = -wolf->player.cam.fov / (float)wolf->display.width;
	printf("\n\n\n%f\n", teta_cur);
	while (col < wolf->display.width)
	{
		if (teta_cur <= 0.001)
			teta_cur = (M_PI * 2.0 ) + teta_cur;
		else if (teta_cur >= M_PI * 2.0)
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
