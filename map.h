/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:57:50 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/24 17:41:15 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP
# define MAP

# include "vector.h"
# include "ppm.h"

typedef t_ppm_tex_1bpp
		t_map;

int		map_alloc(t_map *map, int w, int h);
int		init_map(t_map *map);
int		check_grid(t_map *map, t_vec2i v);
#endif
