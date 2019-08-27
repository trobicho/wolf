/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:05:36 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/27 14:06:25 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PPM_UTILS_H
# define PPM_UTILS_H

ssize_t	read_unsigned_nb_until_space(int fd, ssize_t max);
int		ppm_parse_header(int fd, ssize_t *w, ssize_t *h);
#endif
