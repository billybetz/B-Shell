/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fct2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 14:51:06 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/05 14:51:08 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_history	*create_maillon_history(char *cmd, int place)
{
	t_list_history	*maillon;

	maillon = malloc(sizeof(t_list_history));
	maillon->cmd = ft_strdup(cmd);
	maillon->place = place;
	maillon->next = NULL;
	return (maillon);
}

void			add_maillon_history(t_all *all, t_list_history **hi, char *cmd)
{
	t_list_history	*tmp;

	all->history_place++;
	tmp = *hi;
	if (!tmp)
		*hi = create_maillon_history(cmd, all->history_place);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_maillon_history(cmd, all->history_place);
	}
}
