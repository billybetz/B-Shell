/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 17:34:38 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/03 19:42:31 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_env	*create_maillon_env(char *title, char *content)
{
	t_list_env	*maillon;

	maillon = malloc(sizeof(t_list_env));
	maillon->title = ft_strdup(title);
	maillon->content = ft_strdup(content);
	maillon->next = NULL;
	return (maillon);
}

void		add_maillon_env(t_list_env **env, char *title, char *content)
{
	t_list_env *tmp;

	tmp = *env;
	if (!tmp)
		*env = create_maillon_env(title, content);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_maillon_env(title, content);
	}
}

t_list_cmd	*create_maillon_cmd(char *name, char **tab)
{
	t_list_cmd	*maillon;
	char		**tab2;

	tab2 = ft_strtabdup((const char **)tab);
	maillon = malloc(sizeof(t_list_cmd));
	maillon->cmd_name = ft_strdup(name);
	maillon->cmd_args = tab2;
	maillon->next = NULL;
	return (maillon);
}

void		add_maillon_cmd(t_list_cmd **cmd, char *cmd_name, char **cmd_args)
{
	t_list_cmd *tmp;

	tmp = *cmd;
	if (!tmp)
		*cmd = create_maillon_cmd(cmd_name, cmd_args);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_maillon_cmd(cmd_name, cmd_args);
	}
}
