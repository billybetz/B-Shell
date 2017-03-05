/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 17:48:54 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/03 19:43:47 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_search_path(t_all *all)
{
	char		**str;
	t_list_env	*tmp;

	tmp = all->env;
	while (tmp && (ft_strcmp(tmp->title, "PATH") != 0))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	str = ft_strsplit(tmp->content, ':');
	str = ft_strtabadd(str, ".");
	return (str);
}

static void	incremente_shlvl(t_all *all)
{
	int		lvl;
	char	*test;

	test = get_env_value(all->env, "SHLVL");
	if (!test)
		return ;
	lvl = ft_atoi(get_env_value(all->env, "SHLVL"));
	lvl++;
	change_env_value(all->env, "SHLVL", ft_itoa(lvl));
	ft_strdel(&test);
}

int			main(int ac, char **av, char **env)
{
	t_all	*all;

	(void)ac;
	(void)av;
	all = NULL;
	all = malloc(sizeof(t_all));
	all->cmd = NULL;
	all->env = NULL;
	all->history = NULL;
	all->history_place = 0;
	get_env(env, &(all->env), all);
	incremente_shlvl(all);
	print_prompt(all->env);
	while ((all->gnl_ret = get_next_line(0, &(all->str))))
	{
		get_cmd(&(all->cmd), all->str, all);
		exec_cmd(all);
		free_cmd(&(all->cmd));
		print_prompt(all->env);
	}
	return (0);
}
