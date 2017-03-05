/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fct1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 10:55:49 by bbetz             #+#    #+#             */
/*   Updated: 2016/09/20 10:55:50 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_value(t_list_env *env, char *name, char *value)
{
	t_list_env	*tmp;
	int			i;

	i = 0;
	if (!name[i])
		return ;
	tmp = env;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->title, name)))
		{
			tmp->content = value;
			return ;
		}
		tmp = tmp->next;
	}
}

char	**convert_env_to_tab(t_all *all)
{
	char		**ret;
	t_list_env	*tmp;
	int			i;

	i = 0;
	tmp = all->env;
	ret = malloc(sizeof(char *) * (all->env_size + 1));
	while (tmp)
	{
		ret[i] = ft_strdup(tmp->title);
		ret[i] = ft_strjoin(ret[i], ft_strdup("="));
		ret[i] = ft_strjoin(ret[i], tmp->content);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*get_env_value(t_list_env *env, char *name)
{
	t_list_env *tmp;

	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp && (ft_strcmp(tmp->title, name)) != 0)
		tmp = tmp->next;
	if (tmp)
		return (ft_strdup(tmp->content));
	else
		return (NULL);
}

void	get_title_content(char **env, t_init *i)
{
	while (env[i->i][i->y + 1] && env[i->i][++i->y] != '=')
	{
		i->title_tmp[i->z] = env[i->i][i->y];
		i->z++;
	}
	i->title_tmp[i->z] = '\0';
	i->z = 0;
	while (env[i->i][++i->y] != '\0')
	{
		i->content_tmp[i->z] = env[i->i][i->y];
		i->z++;
	}
	i->content_tmp[i->z] = '\0';
	i->y = -1;
}

void	get_env(char **env, t_list_env **e, t_all *all)
{
	t_init	*i;

	i = malloc(sizeof(t_init));
	i->i = -1;
	i->y = -1;
	while (env && env[++i->i])
	{
		i->z = 0;
		i->title_tmp = malloc(sizeof(char) * (ft_strlen(env[i->i]) + 1));
		i->content_tmp = malloc(sizeof(char) * (ft_strlen(env[i->i]) + 1));
		get_title_content(env, i);
		add_maillon_env(e, i->title_tmp, i->content_tmp);
		free(i->title_tmp);
		free(i->content_tmp);
	}
	all->env_size = i->i;
}
