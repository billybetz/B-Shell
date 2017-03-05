/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:32:26 by bbetz             #+#    #+#             */
/*   Updated: 2017/01/07 15:32:27 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(t_list_cmd *cmd)
{
	int i;

	i = 0;
	if (!cmd->cmd_args[i])
		return ;
	while (cmd->cmd_args[i + 1])
	{
		ft_putstr(cmd->cmd_args[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putendl(cmd->cmd_args[i]);
}
