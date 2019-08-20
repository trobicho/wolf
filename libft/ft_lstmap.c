/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:39:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/08 14:36:22 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*ft_lstfree(t_list *lst)
{
	t_list	*lstsave;

	while (lst != NULL)
	{
		free(lst->content);
		lstsave = lst;
		lst = lst->next;
		free(lstsave);
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*ret_elem;
	t_list	*new_elem;
	t_list	*new_elem_save;
	int		first;

	first = 1;
	new_lst = NULL;
	if (f != NULL)
		while (lst != NULL)
		{
			ret_elem = f(lst);
			if (ret_elem == NULL)
				return (first ? NULL : ft_lstfree(new_lst));
			new_elem = ft_lstnew(ret_elem->content, ret_elem->content_size);
			if (new_elem == NULL)
				return (first ? NULL : ft_lstfree(new_lst));
			if (first && (new_lst = new_elem))
				first = 0;
			else
				new_elem_save->next = new_elem;
			new_elem_save = new_elem;
			lst = lst->next;
		}
	return (new_lst);
}
