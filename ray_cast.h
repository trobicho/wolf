/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:56:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 14:48:26 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_H
# define RAY_CAST_H

# include "wolf.h"
# include "vector.h"

typedef struct	s_ray
{
	t_vec2i	origin;
	t_vec2i	pos;
	float	angle;
	float	dist;
	int		wall_w;
	float	tan_calc;
	float	beta;
}				t_ray;

void			ray_cast(t_wolf *wolf);
t_vec2i			calc_step(t_ray *ray, t_map *map, t_vec2i *delta_dist
	, t_vec2i *step);
#endif
