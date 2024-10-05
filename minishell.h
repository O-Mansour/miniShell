/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:50:32 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 20:53:06 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BASIC 0
# define RED_IN 1
# define RED_OUT 2
# define HERE_DOC 3
# define APPEND 4

typedef struct s_files
{
	int				type;
	int				is_expanded;
	int				expand_heredoc;
	char			*word;
	struct s_files	*next;
}					t_files;

typedef struct s_args
{
	int				infile;
	int				outfile;
	int				exec;
	char			**cmd;
	t_files			*file;
	struct s_args	*next;
}					t_args;

// -------------------
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_global
{
	int				exit_code;
	int				expand_value;
	t_env			*env;
}					t_global;

extern t_global			g_minishell;
// --------------------
void		*ft_calloc(size_t count, size_t size);
char		**split_ignore_quotes(char *s, char c);
char		*str_join(char *s1, char *s2);
char		**split_proc(char *s);
int			ft_isspace(char c);
void		ft_free(char **str_p);
int			cmp_str(char *s1, char *s2);
int			second_quote(char *str, int i, int c);
t_args		*ft_lstnew(char **tmp_cmd, t_files *tmp_file);
void		ft_lstadd_back(t_args **lst, t_args *new);
t_files		*new_lstfile(int type, char *word);
void		lstfile_addback(t_files **lst, t_files *new);
int			exec_heredoc(t_args *cmds);
int			open_files(t_args *data, int in, int out);
char		*get_real_input(t_files *curr);
int			key_expansion(char **tmp_str, char *cmd, int *j, int in_double);
char		*add_char(char *str, char c);
int			nothing_before_pipe(char *str, int i);
int			nothing_after_pipe(char *str, int i);
int			syntax_err(char *str);
int			nb_procs(char *str);
t_args		*split_line(char *str);
void		expand_data(t_args *curr);
void		remove_quotes(t_args *data);
char		*put_value(char *tmp_str, char *value);
void		rl_replace_line(const char *s, int i);
void		ft_fill_help(char *str, int *x, int *y);
void		ft_nwords_help(char *str, int *i, int *n);

//--------------------------------------------

void		execute(t_args *cmds);
void		get_env(char **env);
t_env		*ft_lstneew(char *key, char *value);
void		ft_lstadd_backk(t_env **lst, t_env *new);
int			ft_lstsize_args(t_args *lst);
int			ft_strcmp(char *s1, char *s2);
int			ft_lstsize_env(t_env *lst);
void		ft_env(t_args *cmd);
void		ft_echo(t_args *cmd);
void		ft_exit(t_args *cmmd);
void		ft_pwd(t_args *cmmd);
void		ft_unset(char **cmd);
void		ft_error(char *arg1, char *arg2, int ex);
void		ft_cd(t_args *cmds);
void		ft_export(t_args *cmd);
void		oldpwdd(t_args *cmds);
char		*ft_check_env(char *str);
void		change_pwd_oldpwd(void);
void		chdirtest(t_args *cmds);
void		swap(t_env *x, t_env *y);
void		soirt_exp(void);
void		print_export(t_args *cmd);
void		addenv(char *key, char *value);
void		addenv(char *key, char *value);
void		ft_add(char *cmd);
void		app_new_value(char *key, char *value);
void		ft_error(char *arg1, char *arg2, int ex);
char		*check_path(void);
char		**full_path(void);
char		**full_env(void);
void		get_env(char **env);
int			ft_strcmp(char *s1, char *s2);
int			searsh_path(char *key);
int			ft_check(char *str, char c);
void		ft_get_path_(char *cmd, char **path);
char		*ft_get_pth(char **path, char *cmd);
int			execute_builtins(t_args *cmds);
char		*cmdispath(char *cmd);
void		chaild_pros(t_args *temp, int *fd);
char		*setup_exec(t_args *temp, int *fd, char **pth);
int			close_file(t_args *temp, int *fd);
void		wait_pros(int pid1);
void		dup_file(t_args *temp);
void		setup_eport(t_args *cmd, t_env *it);
void		close_after_use(t_args *cmds);

#endif
