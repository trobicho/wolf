/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:01:52 by trobicho          #+#    #+#             */
/*   Updated: 2019/04/08 12:01:31 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_lstdelthat(t_list *alst, void (*del)(void*, size_t))
{
	if (del != NULL)
		del(alst->content, alst->content_size);
	if (alst->next != NULL)
		ft_lstdelthat(alst->next, del);
	free(alst);
}

void		ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	if (alst != NULL && *alst != NULL)
	{
		ft_lstdelthat(*alst, del);
		*alst = NULL;
	}
}
