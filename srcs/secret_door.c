/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secret_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 04:39:14 by trobicho          #+#    #+#             */
/*   Updated: 2019/09/07 01:53:20 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "map.h"
#include "vector.h"
#include "libft.h"

static t_secret_door	*add_secret_door_to_list(t_wolf *wolf, t_vec2i pos
	, t_vec2i dir)
{
	t_secret_door	sdoor;
	t_list			*ptr;

	sdoor.pos = pos;
	sdoor.state = secret_door_state_moving;
	sdoor.timer = 64;
	sdoor.dir = dir;
	if (wolf->secret_door_list == NULL)
	{
		wolf->secret_door_list =
			ft_lstnew((void*)&sdoor, sizeof(t_secret_door));
		ptr = wolf->secret_door_list;
	}
	else
	{
		ptr = wolf->secret_door_list;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = ft_lstnew((void*)&sdoor, sizeof(t_secret_door));
	}
	if (ptr != NULL)
		return ((t_secret_door*)ptr->content);
	return (NULL);
}

static t_list			*del_a_secret_door(t_wolf *wolf, t_list *ptr
	, t_list *ptr_last)
{
	if (ptr_last == NULL)
	{
		wolf->secret_door_list = ptr->next;
		ptr_last = ptr->next;
	}
	else
		ptr_last->next = ptr->next;
	free(ptr->content);
	free(ptr);
	return (ptr_last);
}

void					open_secret_door(t_wolf *wolf, t_vec2i pos, t_vec2i dir)
{
	t_secret_door	*sdoor_ptr;
	t_list			lptr;

	pos.x /= 64;
	pos.y /= 64;
	if (dir.x)
		dir.x /= ft_abs(dir.x);
	if (dir.y)
		dir.y /= ft_abs(dir.y);
	if (pos.x == 0 || pos.y == 0
		|| pos.x == wolf->map.w - 1 || pos.y == wolf->map.h - 1)
		return ;
	if ((sdoor_ptr = find_that_secret_door(wolf, pos)) == NULL)
	{
		if (wolf->map.pixels[(pos.x + dir.x) + (pos.y + dir.y) * wolf->map.w])
			return ;
		if ((sdoor_ptr = add_secret_door_to_list(wolf, pos, dir)) == NULL)
			return ;
	}
}

static void				secret_door_move(t_wolf *wolf, t_secret_door *sdoor)
{
	t_vec2i	pos;

	pos = (t_vec2i){sdoor->pos.x + sdoor->dir.x, sdoor->pos.y + sdoor->dir.y};
	if ((pos.x <= 0 || pos.y <= 0
		|| pos.x >= wolf->map.w - 1 || pos.y >= wolf->map.h - 1)
			|| wolf->map.pixels[pos.x + pos.y * wolf->map.w] > 0)
	{
		if (sdoor->timer == 64)
			sdoor->state = secret_door_state_block;
		sdoor->timer++;
	}
	else if (pos.x == (int)wolf->player.pos.x / 64
		&& pos.y == (int)wolf->player.pos.y / 64)
	{
		sdoor->state = secret_door_state_block_by_player;
		sdoor->timer += (sdoor->timer < 64) ? 1 : 0;
	}
	else if (--sdoor->timer <= 0)
	{
		wolf->map.pixels[pos.x + pos.y * wolf->map.w] =
			wolf->map.pixels[sdoor->pos.x + sdoor->pos.y * wolf->map.w];
		wolf->map.pixels[sdoor->pos.x + sdoor->pos.y * wolf->map.w] = 0;
		sdoor->pos = pos;
		sdoor->timer = 64;
	}
}

void					handle_secret_door_state(t_wolf *wolf)
{
	t_list			*ptr;
	t_list			*ptr_last;
	t_secret_door	*sdoor;

	ptr = wolf->secret_door_list;
	ptr_last = NULL;
	while (ptr != NULL && (sdoor = (t_secret_door*)ptr->content) != NULL)
	{
		secret_door_move(wolf, sdoor);
		if (sdoor->state == secret_door_state_block)
		{
			ptr = del_a_secret_door(wolf, ptr, ptr_last);
			continue;
		}
		ptr_last = ptr;
		ptr = ptr->next;
	}
}
