/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 17:50:34 by bbetz             #+#    #+#             */
/*   Updated: 2016/09/15 11:00:40 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <../libft/include/libft.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <dirent.h>

typedef struct	s_init
{
	int						i;
	int						y;
	int						z;
	char					*title_tmp;
	char					*content_tmp;
}				t_init;

typedef struct	s_list_cmd
{
	char					*cmd_name;
	char					**cmd_args;
	struct s_list_cmd		*next;
}				t_list_cmd;

typedef struct	s_list_env
{
	char					*title;
	char					*content;
	struct s_list_env		*next;
}				t_list_env;

typedef struct	s_list_history
{
	char					*cmd;
	int						place;
	struct s_list_history	*next;
}				t_list_history;

typedef struct	s_all
{
	pid_t					root_fork;

	t_list_history			*history;
	int						history_place;

	char					*str;
	int						gnl_ret;

	t_list_cmd				*cmd;

	t_list_env				*env;

	int						env_size;
	size_t					rd_ret;

}				t_all;

/*
**	===========  **
**	 CHECK_FCT   **
**	===========  **
*/
int				is_my_cmd(char *name);
char			*is_existing_cmd(t_all *all, char *name);
int				check_rights(char *cmd_name);
/*
**	===========  **
**	  LIST_FCT   **
**	===========  **
*/
t_list_env		*create_maillon_env(char *title, char *content);
void			add_maillon_env(t_list_env **env, char *title, char *content);
t_list_cmd		*create_maillon_cmd(char *name, char **tab);
void			add_maillon_cmd(t_list_cmd **cmd, char *name, char **args);
t_list_history	*create_maillon_history(char *cmd, int place);
void			add_maillon_history(t_all *all, t_list_history **h, char *cmd);
/*
**	===========  **
**	  ENV_FCT    **
**	===========  **
*/
void			change_env_value(t_list_env *env, char *name, char *value);
void			get_env(char **env, t_list_env **e, t_all *all);
char			**convert_env_to_tab(t_all *all);
char			*get_env_value(t_list_env *env, char *name);
/*
**	===========  **
**	  CMD_FCT    **
**	===========  **
*/
void			get_cmd(t_list_cmd **cmd, char *str, t_all *all);
void			exec_cmd(t_all *e);
/*
**	===========  **
**	 CLEAR_FCT   **
**	===========  **
*/
void			free_cmd(t_list_cmd **cmd);
/*
**	===========  **
**	  BUILTINS   **
**	===========  **
*/
void			cmd_cd(t_all *all, t_list_cmd *cmd);
void			cmd_setenv(t_all *all, t_list_env **env, t_list_cmd *cmd);
void			cmd_unsetenv(t_list_cmd *cmd, t_list_env **env);
void			cmd_env(t_list_env *env, t_list_cmd *cmd);
void			cmd_echo(t_list_cmd *cmd);
void			cmd_exit(t_all *all);
void			cmd_history(t_list_history *history);
void			cmd_hclear(t_all *all, t_list_history **history);

void			print_prompt(t_list_env *env);
char			**get_search_path(t_all *all);
#endif
