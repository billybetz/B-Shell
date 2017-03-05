/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 17:07:56 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/03 19:33:12 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_new(char *name, t_list_env **env, int i)
{
	t_list_env	*tmp;
	t_list_env	*tmp2;
	char		*str;
	char		*value;

	while (name && name[i] && name[i] != '=')
		i++;
	if (!name[i])
		return ;
	str = ft_strdup_f_t(name, 0, i - 1);
	if (name[i + 1])
		value = ft_strdup_f_t(name, i + 1, ft_strlen(name) - 1);
	else
		value = ft_strdup("");
	tmp = *env;
	if (!tmp)
		add_maillon_env(env, str, value);
	if (!tmp)
		return ;
	while (tmp && tmp->next && tmp->next->next)
		tmp = tmp->next;
	tmp2 = create_maillon_env(str, value);
	tmp2->next = tmp->next;
	tmp->next = tmp2;
}

static int	name_exist(char *name, t_list_env *env)
{
	t_list_env	*tmp;
	char		*str;
	int			i;

	i = 0;
	tmp = env;
	if (!tmp)
		return (0);
	while (name[i] && name[i] != '=')
		i++;
	if (!name[i])
		str = ft_strdup(name);
	else
		str = ft_strdup_f_t(name, 0, i - 1);
	while (tmp)
	{
		if (!(ft_strcmp(tmp->title, str)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	replace_env_value(char *name, t_list_env *env)
{
	t_list_env	*tmp;
	char		*str;
	char		*value;
	int			i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	if (!name[i])
		return ;
	else
	{
		str = ft_strdup_f_t(name, 0, i - 1);
		value = ft_strdup_f_t(name, i + 1, ft_strlen(name) - 1);
	}
	tmp = env;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->title, str)))
		{
			tmp->content = value;
			return ;
		}
		tmp = tmp->next;
	}
}

static char	*check_validity(t_list_cmd *cmd)
{
	char	*msg;
	int		i;
	int		y;

	i = 0;
	while (cmd->cmd_args[i])
	{
		y = 0;
		while (cmd->cmd_args[i][y] && cmd->cmd_args[i][y] != '=')
			y++;
		if (y == 0 && cmd->cmd_args[i][0] && !cmd->cmd_args[i][1])
			return (ft_strdup("zsh: bad assignment"));
		if (y == 0 && cmd->cmd_args[i][0])
		{
			msg = ft_strdup("zsh: ");
			msg = ft_strjoin(msg, ft_strdup_f_t(cmd->cmd_args[i],
						1, ft_strlen(cmd->cmd_args[i]) - 1));
			msg = ft_strjoin(msg, " not found");
			return (msg);
		}
		i++;
	}
	return (NULL);
}

void		cmd_setenv(t_all *all, t_list_env **env, t_list_cmd *cmd)
{
	char	*str;
	int		i;

	i = 0;
	if (!(cmd->cmd_args[0]))
	{
		cmd_env(all->env, cmd);
		return ;
	}
	if ((str = check_validity(cmd)) != NULL)
	{
		ft_putendl_fd(str, 2);
		return ;
	}
	while (cmd->cmd_args[i])
	{
		if (name_exist(cmd->cmd_args[i], *env))
			replace_env_value(cmd->cmd_args[i], *env);
		else
			add_new(cmd->cmd_args[i], env, 0);
		i++;
	}
}
