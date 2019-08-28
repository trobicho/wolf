#include "ray_cast_new.h"
#include "draw.h"
#include "libft.h"

static void	create_ray(t_ray *ray, t_vec2f dir, float col, t_vec2f pos)
{
	ray->vec.x = dir.x + ray->plane.x * (2.0 * col -1.0);
	ray->vec.y = dir.y + ray->plane.y * (2.0 * col -1.0);
	ray->dist = 0;
	ray->delta_dist.x = ft_abs(1.0 / ray->vec.x);
	ray->delta_dist.y = ft_abs(1.0 / ray->vec.y);
	ray->origin = pos;
	ray->wall_col = 0;
	if (ray->vec.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (pos.x - (int)pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = ((int)pos.x + 1.0 - pos.x) * ray->delta_dist.x;
	}
	if (ray->vec.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (pos.y - (int)pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = ((int)pos.y + 1.0 - pos.y) * ray->delta_dist.y;
	}
}

static int	launch_one_ray(t_ray *ray, t_map *map)
{
	int		found;
	int		side;
	t_vec2i	pos;

	pos = (t_vec2i){(int)ray->origin.x, (int)ray->origin.y};
	if ((found = (map->pixels[pos.x + pos.y * map->w])) > 0)
	{
		ray->dist = 0.015;
		return (found);
	}
	while (1)
	{
        if (ray->side_dist.x < ray->side_dist.y)
        {
          ray->side_dist.x += ray->delta_dist.x;
          pos.x += ray->step.x;
          side = 0;
        }
        else
        {
          ray->side_dist.y += ray->delta_dist.y;
          pos.y += ray->step.y;
          side = 1;
        }
		if ((found = (map->pixels[pos.x + pos.y * map->w])) > 0)
			break;
	}
	if (side == 0)
	{	
		ray->dist = (pos.x - ray->origin.x + (1 - ray->step.x) / 2.0) / ray->vec.x;
		ray->wall_col = ray->origin.y + ray->dist * ray->vec.y;
	}
	else
	{
		ray->dist = (pos.y - ray->origin.y + (1 - ray->step.y) / 2.0) / ray->vec.y;
		ray->wall_col = ray->origin.x + ray->dist * ray->vec.x;
	}
	found = (found == -1) ? -1 : found + side;
	ray->wall_col -= (int)ray->wall_col;
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
	printf("dir = {%f, %f}\n", dir.x, dir.y);
	ray.plane.x = (dir.x * cos(M_PI / 2.0) + dir.y * -sin(M_PI / 2.0)) * (wolf->player.fov / M_PI);
	ray.plane.y = (dir.y * cos(M_PI / 2.0) + dir.x * sin(M_PI / 2.0)) * (wolf->player.fov / M_PI);
	printf("plane = {%f, %f}\n\n", ray.plane.x, ray.plane.y);
	while (col < wolf->display.width)
	{
		create_ray(&ray, dir, col / (float)wolf->display.width
			, (t_vec2f){wolf->player.pos.x / 64.0, wolf->player.pos.y / 64.0});
		if ((found = launch_one_ray(&ray, &wolf->map)))
		{
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
