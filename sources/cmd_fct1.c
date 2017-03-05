/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fct1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 10:57:15 by bbetz             #+#    #+#             */
/*   Updated: 2017/02/03 19:37:28 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static int	count_cmd(char **tab, int place)
{
	int nb;

	nb = 0;
	while (tab[place] && ft_strcmp(tab[place], ";"))
	{
		place++;
		nb++;
	}
	return (nb);
}

static int	get_cmd_init(char **name, char ***args, int i[3], char **str)
{
	*name = NULL;
	*args = NULL;
	i[0] = 0;
	if (!(*str))
		return (0);
	*str = ft_str_spacearround(*str, ';');
	return (1);
}

static void	get_cmd2(char **name, char ***args, int i[3], t_list_cmd **cmd)
{
	(*args)[i[1]] = NULL;
	if (*name)
	{
		add_maillon_cmd(cmd, *name, *args);
		ft_strdel(name);
	}
	i[2] = -1;
	while ((*args)[++i[2]])
		ft_strdel(args[i[2]]);
	free(*args);
	*args = NULL;
}

void		get_cmd(t_list_cmd **cmd, char *str, t_all *all)
{
	char	**tab;
	char	*name;
	char	**args;
	int		i[3];

	if ((get_cmd_init(&name, &args, i, &str)) == 0)
		return ;
	tab = ft_str_to_tab(str);
	while ((i[1] = 0) || (tab && tab[i[0]]))
	{
		while ((tab[i[0]] && ft_strcmp(tab[i[0]], ";") == 0))
			i[0]++;
		args = malloc(sizeof(char *) * (count_cmd(tab, i[0]) + 1));
		if (tab[i[0]])
			name = ft_strdup(tab[i[0]++]);
		while (tab[i[0]] && (ft_strcmp(tab[i[0]], ";")))
		{
			args[i[1]] = (ft_strcmp(tab[i[0]], "~") == 0) ? ft_strdup(
				get_env_value(all->env, "HOME")) : ft_strdup(tab[i[0]]);
			i[1]++;
			i[0]++;
		}
		get_cmd2(&name, &args, i, cmd);
	}
	ft_free_double_pointer((void ***)&tab);
}
