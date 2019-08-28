#ifndef RAY_CAST_H
# define RAY_CAST_H

# include "wolf.h"
# include "vector.h"

typedef struct	s_ray
{
	t_vec2f	origin;
	t_vec2i	pos;
	t_vec2f	vec;
	t_vec2f	delta_dist;
	t_vec2f	side_dist;
	t_vec2f	plane;
	t_vec2i	step;
	float	dist;
	float	wall_col;
}				t_ray;

void			ray_cast(t_wolf *wolf);
t_vec2i			calc_step(t_ray *ray, t_map *map, t_vec2i *delta_dist
	, t_vec2i *step);
#endif
