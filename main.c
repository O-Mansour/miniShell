/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:55:37 by omansour          #+#    #+#             */
/*   Updated: 2023/08/04 07:29:42 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global			g_minishell;

void	sigint_handler(int s)
{
	if (s == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_minishell.exit_code = 1;
	}
}

void	free_file(t_files *file)
{
	if (file)
	{
		free_file(file->next);
		free(file->word);
		free(file);
	}
}

void	free_args(t_args *data)
{
	if (data)
	{
		free_args(data->next);
		ft_free(data->cmd);
		free_file(data->file);
		free(data);
	}
}

char	*receive_cmds(void)
{
	char	*str;

	signal(SIGINT, sigint_handler);
	str = readline("miniShell-1.0$ ");
	signal(SIGINT, SIG_IGN);
	if (!str)
		exit(g_minishell.exit_code);
	if (str[0])
		add_history(str);
	if (syntax_err(str))
	{
		ft_putendl_fd("syntax error near unexpected token", 2);
		g_minishell.exit_code = 258;
		free(str);
		return (NULL);
	}
	return (str);
}

int	main(int ac, char *av[], char *ev[])
{
	t_args	*data;
	char	*str;

	(void) av;
	(void) ac;
	get_env(ev);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = receive_cmds();
		if (!str)
			continue ;
		data = split_line(str);
		if (!data)
		{
			free(str);
			continue ;
		}
		expand_data(data);
		remove_quotes(data);
		execute(data);
		free(str);
		free_args(data);
	}
	return (g_minishell.exit_code);
}
