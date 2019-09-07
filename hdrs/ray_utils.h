/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 01:36:11 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/07 02:16:19 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_UTILS_H
# define RAY_UTILS_H

# include "ray_cast.h"

void	ray_step(t_ray *ray);
int		handle_ray_search(t_wolf *wolf, t_ray *ray, t_map *map);
int		handle_door_ray(t_wolf *wolf, t_ray *ray, t_map *map);
int		handle_secret_door_ray(t_ray *ray, t_map *map , t_secret_door *sdoor);
int		handle_ray_in_door(t_wolf *wolf, t_ray *ray, t_map *map);
void	launch_div_ray(t_ray *ray, float div);
int		send_ray_through_door(t_wolf *wolf, t_ray *ray, t_map *map);
t_vec2f	calc_ray_plane(t_wolf *wolf, t_ray *ray);
void	calc_dist(t_ray *ray);
int		ray_special_3d_door(t_wolf *wolf, t_ray *ray, t_map *map, float timer);
#endif
