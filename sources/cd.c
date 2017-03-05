/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 17:06:39 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/05 16:04:56 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*cut_last_file_to_path(char *path)
{
	int		i;
	int		y;
	char	*new_path;

	y = 0;
	i = ft_strlen(path) - 1;
	while (path[i] > 0 && path[i] != '/')
		i--;
	new_path = malloc(sizeof(char) * (i + 1));
	while (y < i)
	{
		new_path[y] = path[y];
		y++;
	}
	new_path[y] = '\0';
	return (new_path);
}

static void	cd_part3(t_all *all, t_list_cmd *cmd, char **path)
{
	int fd;

	fd = 0;
	if (chdir(*path) == -1)
	{
		if ((fd = open(*path, O_RDONLY)) > 0)
		{
			ft_putstr("cd: not a directory: ");
			ft_putendl(cmd->cmd_args[0]);
			close(fd);
		}
		else
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(cmd->cmd_args[0]);
		}
	}
	else
	{
		change_env_value(all->env, "OLDPWD", get_env_value(all->env, "PWD"));
		change_env_value(all->env, "PWD", ft_strdup(*path));
	}
}

static void	cd_part2(t_all *all, t_list_cmd *cmd, char cwd[1024], char **path)
{
	if (cmd->cmd_args[0][0] == '-')
	{
		*path = get_env_value(all->env, "OLDPWD");
		ft_putendl(*path);
	}
	else
	{
		*path = ft_strdup(cwd);
		*path = ft_strjoin(*path, "/");
		*path = ft_strjoin(*path, cmd->cmd_args[0]);
	}
}

static int	cd_part1(t_all *all, t_list_cmd *cmd, char cwd[1024], char **path)
{
	if (!cmd->cmd_args[0])
	{
		*path = get_env_value(all->env, "HOME");
		if (path == NULL)
			return (2);
		return (1);
	}
	else if (cmd->cmd_args[1])
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(cmd->cmd_args[0]);
		return (2);
	}
	else if (ft_strcmp(cmd->cmd_args[0], "..") == 0)
	{
		*path = ft_strdup(cwd);
		*path = cut_last_file_to_path(*path);
		return (1);
	}
	else if (cmd->cmd_args[0][0] == '/')
	{
		*path = ft_strdup(cmd->cmd_args[0]);
		return (1);
	}
	return (0);
}

void		cmd_cd(t_all *all, t_list_cmd *cmd)
{
	char	cwd[1024];
	char	*path;
	int		ret;

	path = NULL;
	if (((getcwd(cwd, sizeof(cwd))) == NULL) && cmd->cmd_args[0])
	{
		if (ft_strcmp(cmd->cmd_args[0], ".") == 0)
			ft_putendl("cd: no such file or directory: .");
		if (ft_strcmp(cmd->cmd_args[0], "..") == 0)
			ft_putendl("cd: no such file or directory: .");
		if (ft_strcmp(cmd->cmd_args[0], "..") == 0 ||
			ft_strcmp(cmd->cmd_args[0], ".") == 0)
			return ;
	}
	if ((ret = cd_part1(all, cmd, cwd, &path)) == 2)
	{
		ft_strdel(&path);
		return ;
	}
	else if (ret == 0)
		cd_part2(all, cmd, cwd, &path);
	cd_part3(all, cmd, &path);
	ft_strdel(&path);
}
