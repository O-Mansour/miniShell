/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:12:36 by omansour          #+#    #+#             */
/*   Updated: 2023/07/31 12:16:50 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inisilers(t_args *temp, int *fd, int *infile)
{
	if (temp->infile == 0)
		temp->infile = *infile;
	else if (*infile != 0)
	{
		close(*infile);
		*infile = 0;
	}
	if (temp->outfile == 1)
		temp->outfile = fd[1];
	else if (fd[1] != 1)
	{
		close(fd[1]);
		fd[1] = 1;
	}
}

void	dup_file(t_args *temp)
{
	if (temp->infile != 0)
	{
		dup2(temp->infile, 0);
		close(temp->infile);
	}
	if (temp->outfile != 1)
	{
		dup2(temp->outfile, 1);
		close(temp->outfile);
	}
}

void	ft_exec(t_args *temp, int *fd, int *pid1, int *infile)
{
	g_minishell.exit_code = 0;
	fd[1] = 1;
	if (temp->next != NULL)
	{
		if (pipe(fd) == -1)
			exit(1);
	}
	inisilers(temp, fd, infile);
	*pid1 = fork();
	if (*pid1 < 0)
	{
		write(2, "fork: Resource temporarily unavailable\n", 40);
		exit (1);
	}
	if (*pid1 == 0)
		chaild_pros(temp, fd);
	*infile = close_file(temp, fd);
}

void	execute_cmds(t_args *cmds)
{
	t_args	*temp;
	int		fd[2];
	int		pid1;
	int		infile;

	pid1 = 0;
	infile = 0;
	if (!cmds || !cmds->cmd || !cmds->cmd[0])
		return ;
	temp = cmds;
	while (temp != NULL)
	{
		ft_exec(temp, fd, &pid1, &infile);
		temp = temp->next;
	}
	wait_pros(pid1);
}

void	execute(t_args *cmds)
{
	int		size;
	int		in;
	int		out;

	in = 0;
	out = 1;
	if (!cmds)
		return ;
	if (open_files(cmds, in, out) || !cmds || !cmds->cmd || !cmds->cmd[0])
	{
		close_after_use(cmds);
		return ;
	}
	size = ft_lstsize_args(cmds);
	if (size == 1 && execute_builtins(cmds))
	{
		close_after_use(cmds);
		return ;
	}
	else
		execute_cmds(cmds);
}
