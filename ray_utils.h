/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 01:36:11 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/30 02:21:19 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_UTILS_H
# define RAY_UTILS_H

# include "ray_cast.h"

void	ray_step(t_ray *ray);
int		handle_ray_search(t_ray *ray, t_map *map);
#endif
