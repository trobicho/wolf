/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:56:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/21 01:51:37 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_H
# define RAY_CAST_H

#include "wolf.h"
#include "vector.h"

typedef struct	s_ray
{
	t_vec2i	origin;
	t_vec2i	pos;
	float	angle;
	int		dist;
	int		wall_w;
}				t_ray;

void			ray_cast(t_wolf *wolf);
# endif
