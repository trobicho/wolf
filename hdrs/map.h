/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:57:50 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/01 23:12:59 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "vector.h"
# include "ppm.h"

typedef t_ppm_tex_1bpp	t_map;

int		map_alloc(t_map *map, int w, int h, int add_border);
int		map_copy_crop(t_map *map, t_map *cpy, t_vec2i pos, SDL_Rect rect);
int		map_copy(t_map *map, t_map *cpy);
int		init_map(t_map *map);
int		check_grid(t_map *map, t_vec2i v);
int		save_map(t_map *map);
int		erase_map(t_map *map);
int		map_id_add(t_map *map, int x, int y, Uint8 id);
#endif
