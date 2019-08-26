/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:04:49 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/26 14:22:21 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PPM_H
# define PPM_H

# include <SDL2/SDL.h>
# include "vector.h"
# define	READ_SIZE	65535

typedef struct	s_ppm_tex_1bpp
{
	ssize_t	w;
	ssize_t	h;
	Uint8	*pixels;
	t_vec2i	player_pos;
	int		player_dir;
}				t_ppm_tex_1bpp;

typedef struct	s_ppm_tex_4bpp
{
	ssize_t	w;
	ssize_t	h;
	Uint32	*pixels;
	Uint32	blend;
}				t_ppm_tex_4bpp;

int				ppm_load_4bpp(const char *file_path, t_ppm_tex_4bpp *tex);
int				ppm_load_1bpp(const char *file_path, t_ppm_tex_1bpp *tex
	, int max_id);
int				ppm_write_1bpp(const char *file_path, t_ppm_tex_1bpp *tex);
#endif
