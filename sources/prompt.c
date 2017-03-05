/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/16 15:50:23 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/03 19:44:00 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_last_dir(char *path)
{
	int		i;
	int		y;
	char	*new_path;

	i = 0;
	y = 0;
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	if (i != 0)
		i--;
	while (i > 0 && path[i] != '/')
		i--;
	if (path[i] == '/' && path[i + 1])
		i++;
	new_path = malloc(sizeof(char) * (ft_strlen(path) - i) + 1);
	while (path[i])
	{
		new_path[y] = path[i];
		i++;
		y++;
	}
	new_path[y] = '\0';
	return (new_path);
}

void		print_prompt(t_list_env *env)
{
	char *path;

	path = NULL;
	path = getcwd(path, PATH_MAX);
	if (!path)
		path = get_env_value(env, "PWD");
	path = get_last_dir(path);
	ft_putcolor(" BILLY ", GREY);
	ft_putcolor("[", GREY);
	if (path)
		ft_putcolor(path, LIGHT_RED);
	ft_putcolor("]$> ", GREY);
}
