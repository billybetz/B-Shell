/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 19:38:13 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/03 19:38:14 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_list_cmd **cmd)
{
	int			i;
	t_list_cmd	*elem;
	t_list_cmd	*tmp;

	elem = *cmd;
	while (elem != NULL)
	{
		i = 0;
		tmp = elem->next;
		ft_strdel(&elem->cmd_name);
		while (elem->cmd_args && elem->cmd_args[i])
			i++;
		i = 0;
		while (elem->cmd_args && elem->cmd_args[i])
		{
			ft_strdel(&(elem->cmd_args[i]));
			i++;
		}
		free(elem->cmd_args);
		elem->cmd_args = NULL;
		free(elem);
		elem = NULL;
		elem = tmp;
	}
	*cmd = NULL;
}
