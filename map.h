/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:57:50 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 16:37:27 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "vector.h"
# include "ppm.h"

typedef t_ppm_tex_1bpp
		t_map;

int		map_alloc(t_map *map, int w, int h);
int		init_map(t_map *map);
int		check_grid(t_map *map, t_vec2i v);
int		save_map(t_map *map);
#endif
