/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:00:55 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 18:01:28 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_limits(char *str, int *limits)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	limits[0] = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = second_quote(str, i, str[i]);
		else if (str[i] == '|')
		{
			limits[j] = i;
			j++;
		}
	}
	limits[j] = i;
}

char	**split_by_pipe(char *str)
{
	char	**processes;
	int		*lts;
	int		i;

	i = -1;
	lts = malloc((nb_procs(str) + 1) * sizeof(int));
	if (!lts)
		exit (1);
	set_limits(str, lts);
	processes = malloc((nb_procs(str) + 1) * sizeof(char *));
	if (!processes)
		exit (1);
	while (++i < (nb_procs(str)))
		processes[i] = ft_substr(str, lts[i] + 1, lts[i + 1] - lts[i] - 1);
	processes[i] = NULL;
	free(lts);
	return (processes);
}

int	ret_type(char *str)
{
	if (cmp_str(str, "<"))
		return (RED_IN);
	else if (cmp_str(str, ">"))
		return (RED_OUT);
	else if (cmp_str(str, "<<"))
		return (HERE_DOC);
	else if (cmp_str(str, ">>"))
		return (APPEND);
	return (BASIC);
}

void	fill_struct(t_args **data, char *process)
{
	int		type;
	char	*tmp_cmd;
	t_files	*file;
	char	**splitted_proc;
	int		i;

	tmp_cmd = NULL;
	file = NULL;
	splitted_proc = split_proc(process);
	i = -1;
	while (splitted_proc[++i])
	{
		type = ret_type(splitted_proc[i]);
		if (type != BASIC)
			lstfile_addback(&file, new_lstfile(type, splitted_proc[++i]));
		else
			tmp_cmd = str_join(tmp_cmd, splitted_proc[i]);
	}
	ft_lstadd_back(data, ft_lstnew(split_ignore_quotes(tmp_cmd, ' '), file));
	if (tmp_cmd)
		free(tmp_cmd);
	ft_free(splitted_proc);
}

t_args	*split_line(char *str)
{
	char	**processes;
	int		j;
	t_args	*data;

	if (!str || !str[0])
		return (NULL);
	processes = split_by_pipe(str);
	data = NULL;
	j = -1;
	while (processes[++j])
		fill_struct(&data, processes[j]);
	ft_free(processes);
	return (data);
}
