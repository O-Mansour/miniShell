/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:31:28 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 18:30:14 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	chaild_pros(t_args *temp, int *fd)
{
	char	**env;
	char	**pth;
	char	*cmd_path;

	env = full_env();
	pth = full_path();
	cmd_path = setup_exec(temp, fd, pth);
	if (temp->cmd)
		execve(cmd_path, temp->cmd, env);
	else
		exit(0);
	perror("execve");
	exit(1);
}

char	*setup_exec(t_args *temp, int *fd, char **pth)
{
	char	*cmd_path;

	cmd_path = NULL;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (fd[0] != 0)
		close(fd[0]);
	if (temp->infile == -1 || temp->outfile == -1)
		exit(1);
	if (execute_builtins(temp))
		exit(g_minishell.exit_code);
	dup_file(temp);
	if (!temp->cmd || !temp->cmd[0])
		exit(0);
	if (temp->cmd && ft_strchr(temp->cmd[0], '/'))
		cmd_path = cmdispath(temp->cmd[0]);
	else if (temp->cmd)
		cmd_path = ft_get_pth(pth, temp->cmd[0]);
	return (cmd_path);
}

int	close_file(t_args *temp, int *fd)
{
	int	infile;

	infile = 0;
	if (temp->infile)
		close(temp->infile);
	if (temp->outfile != 1)
		close(temp->outfile);
	if (fd[1] != 1)
		close(fd[1]);
	if (infile != 0)
		close(infile);
	infile = fd[0];
	fd[0] = 0;
	return (infile);
}

void	wait_pros(int pid1)
{
	int	status;

	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		g_minishell.exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_minishell.exit_code = WTERMSIG(status) + 128;
	while (waitpid(-1, NULL, 0) != -1)
		;
}
