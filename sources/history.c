/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 14:32:42 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/05 14:32:42 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_hclear(t_all *all, t_list_history **history)
{
	int				i;
	t_list_history	*elem;
	t_list_history	*tmp;

	elem = *history;
	all->history_place = 0;
	while (elem != NULL)
	{
		i = 0;
		tmp = elem->next;
		ft_strdel(&elem->cmd);
		free(elem);
		elem = NULL;
		elem = tmp;
	}
	*history = NULL;
}

void	cmd_history(t_list_history *history)
{
	t_list_history *tmp;

	tmp = history;
	if (!tmp)
		ft_putendl("history: the historic is Empty");
	while (tmp)
	{
		ft_putnbr(tmp->place);
		ft_putchar(' ');
		ft_putendl(tmp->cmd);
		tmp = tmp->next;
	}
}
