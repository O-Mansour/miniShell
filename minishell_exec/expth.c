/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:22:59 by omansour          #+#    #+#             */
/*   Updated: 2023/08/04 07:32:26 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtins(t_args *cmds)
{
	if (!cmds || !cmds->cmd || !cmds->cmd[0])
		return (0);
	if (cmds->exec)
		return (1);
	if (ft_strcmp(cmds->cmd[0], "exit") == 0)
		return (ft_exit(cmds), 1);
	g_minishell.exit_code = 0;
	if (ft_strcmp(cmds->cmd[0], "env") == 0)
		return (ft_env(cmds), 1);
	if (ft_strcmp(cmds->cmd[0], "echo") == 0)
		return (ft_echo(cmds), 1);
	if (ft_strcmp(cmds->cmd[0], "pwd") == 0)
		return (ft_pwd(cmds), 1);
	if (ft_strcmp(cmds->cmd[0], "unset") == 0)
		return (ft_unset(cmds->cmd), 1);
	if (ft_strcmp(cmds->cmd[0], "cd") == 0)
		return (ft_cd(cmds), 1);
	if (ft_strcmp(cmds->cmd[0], "export") == 0)
		return (ft_export(cmds), 1);
	return (0);
}

char	*cmdispath(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
		ft_error(cmd, ": is a directory\n", 126);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	if (access(cmd, F_OK) == 0)
		ft_error(cmd, ": permission denied\n", 126);
	ft_error(cmd, ": No such file or directory\n", 127);
	return (cmd);
}
