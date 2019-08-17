/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 13:57:50 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/17 17:41:20 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP
# define MAP

typedef struct	s_map
{
	int		w;
	int		h;
	int		grid_len;
	char	*buf;
}				t_map;

int		init_map(t_map *map);
#endif
