/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 13:24:11 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/30 06:17:22 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		side;
	float	dist;
	float	wall_col;
}				t_ray;

void			ray_cast(t_wolf *wolf);
int				launch_one_ray(t_wolf *wolf, t_ray *ray, t_map *map);
#endif
