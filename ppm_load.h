/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_load.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:02:12 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/29 19:45:17 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PPM_LOADER_H
# define PPM_LOADER_H

int	ppm_4bbp_load_error(int fd, t_ppm_tex_4bpp *tex);
int	map_load_error(int fd, t_ppm_tex_1bpp *map);
int	get_next_byte(int fd, Uint8 *byte);
#endif
