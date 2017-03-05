/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 17:32:20 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/03 19:29:33 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_my_cmd(char *name)
{
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "setenv") == 0)
		return (1);
	if (ft_strcmp(name, "unsetenv") == 0)
		return (1);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "history") == 0)
		return (1);
	if (ft_strcmp(name, "hclear") == 0)
		return (1);
	return (0);
}

char	*is_existing_cmd(t_all *all, char *name)
{
	int		ret;
	int		i;
	char	*str;
	char	**path;

	i = 0;
	path = get_search_path(all);
	if (!(path))
		return (NULL);
	while (path[i])
	{
		str = ft_strdup(path[i]);
		str = ft_strjoin(str, ft_strdup("/"));
		str = ft_strjoin(str, name);
		if ((ret = open(str, O_RDONLY)) > 0)
		{
			close(ret);
			return (str);
		}
		i++;
		free(str);
	}
	ft_free_double_pointer((void ***)&path);
	return (NULL);
}

int		check_rights(char *cmd_name)
{
	char *file_name;

	if (cmd_name[0] != '.' || cmd_name[1] != '/')
		return (1);
	file_name = ft_strdup_f_t(cmd_name, 2, (ft_strlen(cmd_name) - 1));
	if (!file_name)
		return (0);
	if (ft_isdirectory(cmd_name))
	{
		ft_putstr("Exec: ");
		ft_putstr(file_name);
		ft_putendl(": Is directory ");
	}
	else if (access(cmd_name, X_OK) == -1)
	{
		ft_putstr("minishell: permission denied: ");
		ft_putendl(file_name);
	}
	else
	{
		free(file_name);
		return (1);
	}
	free(file_name);
	return (0);
}
