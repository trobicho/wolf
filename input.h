/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:04:17 by trobicho          #+#    #+#             */
/*   Updated: 2019/08/24 18:53:24 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "wolf.h"
# include "vector.h"

typedef enum	s_cursor_state
{
	cur_state_none = 0,
	cur_state_left_click,
	cur_state_right_click,
}				t_cursor_state;

typedef	struct	s_edit_cursor
{
	int				x;
	int				y;
	t_cursor_state	state;
	int				tex_select;
}				t_edit_cursor;

int				game_event(t_wolf *wolf);
int				menu_event(t_wolf *wolf);
int				editor_event(t_wolf *wolf, t_edit_cursor *cursor);
#endif
