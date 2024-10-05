/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:36:21 by omansour          #+#    #+#             */
/*   Updated: 2023/07/31 13:37:54 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	exit(1);
}

char	*expand_str(char *str)
{
	char	*tmp_str;
	int		j;

	tmp_str = ft_strdup("");
	j = 0;
	while (str[j])
	{
		if (str[j] == '$')
		{
			j++;
			if (key_expansion(&tmp_str, str, &j, 0))
				continue ;
		}
		else
			tmp_str = add_char(tmp_str, str[j]);
		j++;
	}
	free(str);
	return (tmp_str);
}

void	heredoc_parent(t_args *cmds, t_files *curr, int fd_zero, int *status)
{
	char	*real_input;

	wait(status);
	g_minishell.exit_code = WEXITSTATUS(*status);
	real_input = get_real_input(curr);
	if (real_input)
		close (fd_zero);
	else
		cmds->infile = fd_zero;
	free(real_input);
}

void	write_content(t_files *curr, int fd, int fd_zero)
{
	char	*str;

	signal(SIGINT, handle);
	while (1)
	{
		close(fd_zero);
		str = readline(">");
		if (!str || cmp_str(str, curr->word))
		{
			free(str);
			break ;
		}
		if (curr->expand_heredoc)
			str = expand_str(str);
		ft_putendl_fd(str, fd);
		free(str);
	}
	exit(0);
}

int	exec_heredoc(t_args *cmds)
{
	int		fd[2];
	t_files	*curr;
	int		status;

	while (cmds)
	{
		cmds->infile = 0;
		curr = cmds->file;
		while (curr)
		{
			if (curr->type == HERE_DOC)
			{
				pipe(fd);
				if (fork() == 0)
					write_content(curr, fd[1], fd[0]);
				heredoc_parent(cmds, curr, fd[0], &status);
				close(fd[1]);
				if (g_minishell.exit_code)
					return (1);
			}
			curr = curr->next;
		}
		cmds = cmds->next;
	}
	return (0);
}
