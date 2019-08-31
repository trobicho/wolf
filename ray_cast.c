/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 13:24:06 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/31 00:05:33 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_cast.h"
#include "ray_utils.h"
#include "draw.h"
#include "libft.h"

static void	create_ray(t_ray *ray, t_vec2f dir, float col, t_vec2f pos)
{
	ray->vec.x = dir.x + ray->plane.x * (2.0 * col - 1.0);
	ray->vec.y = dir.y + ray->plane.y * (2.0 * col - 1.0);
	ray->dist = 0;
	ray->delta_dist.x = ft_abs(1.0 / ray->vec.x);
	ray->delta_dist.y = ft_abs(1.0 / ray->vec.y);
	ray->origin = pos;
	ray->wall_col = 0;
	ray->step.x = 1.0;
	ray->step.y = 1.0;
	ray->add_float_step_to_dist = 0.0;
	ray->pos = (t_vec2i){(int)ray->origin.x, (int)ray->origin.y};
	if (ray->vec.x < 0)
	{
		ray->step.x = -1.0;
		ray->side_dist.x = (pos.x - (int)pos.x) * ray->delta_dist.x;
	}
	else
		ray->side_dist.x = ((int)pos.x + 1.0 - pos.x) * ray->delta_dist.x;
	if (ray->vec.y < 0)
	{
		ray->step.y = -1.0;
		ray->side_dist.y = (pos.y - (int)pos.y) * ray->delta_dist.y;
	}
	else
		ray->side_dist.y = ((int)pos.y + 1.0 - pos.y) * ray->delta_dist.y;
}

int	launch_one_ray(t_wolf *wolf, t_ray *ray, t_map *map)
{
	int		found;

	while (1)
	{
		ray_step(ray);
		if ((found = handle_ray_search(wolf, ray, map)) > 0)
		{
			break ;
		}
	}
	if (ray->dist <= 0.0)
	calc_dist(ray);
	return (found);
}

void		ray_cast(t_wolf *wolf)
{
	int		col;
	float	teta_cur;
	float	teta_add;
	int		found;
	t_ray	ray;
	t_vec2f	dir;

	col = 0;
	dir.x = cos(wolf->player.angle);
	dir.y = -sin(wolf->player.angle);
	ray.plane.x = (dir.x * cos(M_PI / 2.0) + dir.y * -sin(M_PI / 2.0))
		* (wolf->player.fov / M_PI);
	ray.plane.y = (dir.y * cos(M_PI / 2.0) + dir.x * sin(M_PI / 2.0))
		* (wolf->player.fov / M_PI);
	while (col < wolf->display.width)
	{
		create_ray(&ray, dir, col / (float)wolf->display.width
			, (t_vec2f){wolf->player.pos.x / 64.0, wolf->player.pos.y / 64.0});
		if ((found = launch_one_ray(wolf, &ray, &wolf->map)))
		{
			found += 1 - ray.side;
			ray.dist *= 64.0;
			if (found == -1)
				draw_unicolor_slice(wolf, ray, col, 0x0);
			else
				draw_textured_slice(wolf, &ray, col, found - 1);
		}
		teta_cur += teta_add;
		col++;
	}
}
