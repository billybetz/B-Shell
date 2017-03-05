/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 21:13:40 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/03 19:44:39 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_and_free(t_list_env **tmp, t_list_env **tmp2)
{
	*tmp2 = (*tmp)->next;
	(*tmp)->next = (*tmp2)->next;
	ft_strdel(&((*tmp2)->title));
	ft_strdel(&((*tmp2)->content));
	free(*tmp2);
}

static void	unset_if_exist(char *name, t_list_env **env)
{
	t_list_env	*tmp;
	t_list_env	*tmp2;

	tmp = *env;
	if (!tmp)
		return ;
	if (!ft_strcmp(tmp->title, name))
	{
		ft_strdel(&(tmp->title));
		ft_strdel(&(tmp->content));
		if (tmp->next)
			*env = tmp->next;
		else
		{
			free(*env);
			*env = NULL;
		}
		return ;
	}
	while (tmp->next && ft_strcmp(tmp->next->title, name))
		tmp = tmp->next;
	if (tmp->next)
		swap_and_free(&tmp, &tmp2);
}

void		cmd_unsetenv(t_list_cmd *cmd, t_list_env **env)
{
	int	i;

	i = 0;
	if (!cmd->cmd_args[i])
	{
		ft_putendl_fd("unsetenv: not enought arguments", 2);
	}
	while (cmd->cmd_args[i] && env)
	{
		unset_if_exist(cmd->cmd_args[i], env);
		i++;
	}
}
