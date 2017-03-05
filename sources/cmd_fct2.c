/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fct2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 21:55:13 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/14 21:55:14 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_my_cmd(t_all *all, t_list_cmd *cmd)
{
	add_maillon_history(all, &(all->history), cmd->cmd_name);
	if (ft_strcmp(cmd->cmd_name, "exit") == 0)
		cmd_exit(all);
	else if (ft_strcmp(cmd->cmd_name, "env") == 0)
	{
		cmd_env(all->env, cmd);
	}
	else if (ft_strcmp(cmd->cmd_name, "setenv") == 0)
		cmd_setenv(all, &(all->env), cmd);
	else if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		cmd_cd(all, cmd);
	else if (ft_strcmp(cmd->cmd_name, "unsetenv") == 0)
		cmd_unsetenv(cmd, &(all->env));
	else if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		cmd_echo(cmd);
	else if (ft_strcmp(cmd->cmd_name, "history") == 0)
		cmd_history(all->history);
	else if (ft_strcmp(cmd->cmd_name, "hclear") == 0)
		cmd_hclear(all, &(all->history));
}

static char	**create_args_execve(char *path, char **src)
{
	int		i;
	char	**dest;

	i = 0;
	while (src && src[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 2));
	dest[0] = ft_strdup(path);
	i = 0;
	while (src[i])
	{
		dest[i + 1] = ft_strdup(src[i]);
		i++;
	}
	dest[i + 1] = NULL;
	return (dest);
}

void		exec_others_cmd(char ***ex_a, t_list_cmd *tmp, t_all *all)
{
	if (fork() == 0)
	{
		if (!(*ex_a))
			*ex_a = create_args_execve(tmp->cmd_name, tmp->cmd_args);
		if (execve(tmp->cmd_name, *ex_a, convert_env_to_tab(all)) == -1)
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(tmp->cmd_name);
			exit(0);
		}
	}
	else
		wait(NULL);
}

void		exec_existing_cmd(t_list_cmd *tmp, char ***ex_a, t_all *a, char **p)
{
	if (check_rights(tmp->cmd_name) == 0)
		return ;
	if (fork() == 0)
	{
		*ex_a = create_args_execve(*p, tmp->cmd_args);
		if (execve(*p, *ex_a, convert_env_to_tab(a)) == -1)
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(tmp->cmd_name);
			exit(0);
		}
	}
	else
		wait(NULL);
	add_maillon_history(a, &(a->history), tmp->cmd_name);
	ft_strdel(p);
}

void		exec_cmd(t_all *all)
{
	char		*path;
	t_list_cmd	*tmp;
	char		**ex_a;

	tmp = all->cmd;
	ex_a = NULL;
	while (tmp)
	{
		if (is_my_cmd(tmp->cmd_name) == 1)
			exec_my_cmd(all, tmp);
		else if ((path = is_existing_cmd(all, tmp->cmd_name)) != NULL)
			exec_existing_cmd(tmp, &ex_a, all, &path);
		else
			exec_others_cmd(&ex_a, tmp, all);
		tmp = tmp->next;
		ft_free_double_pointer((void ***)&ex_a);
	}
}
