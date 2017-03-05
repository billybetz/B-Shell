/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 17:28:20 by bbetz             #+#    #+#             */
/*   Updated: 2017/01/06 17:28:21 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(t_list_env *env, t_list_cmd *cmd)
{
	t_list_env *tmp;

	if (cmd->cmd_args[0])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->cmd_args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return ;
	}
	tmp = env;
	while (tmp)
	{
		ft_putstr(tmp->title);
		ft_putchar('=');
		ft_putstr(tmp->content);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}
