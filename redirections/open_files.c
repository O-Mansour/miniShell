/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:54:29 by omansour          #+#    #+#             */
/*   Updated: 2023/07/31 12:57:30 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambiguous(char *str, int nb)
{
	int	i;

	if (nb == 0)
		return (1);
	if (!str || !str[0])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		g_minishell.exit_code = 1;
		return (0);
	}
	i = -1;
	while (str[++i])
	{
		if (ft_isspace(str[i]))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			g_minishell.exit_code = 1;
			return (0);
		}
	}
	return (1);
}

int	open_in(t_files *curr, int *in)
{
	char	*real_input;

	real_input = get_real_input(curr);
	if (!real_input)
		return (0);
	free(real_input);
	if (*in)
		close(*in);
	if (check_ambiguous(curr->word, curr->is_expanded))
		*in = open(curr->word, O_RDONLY);
	else
		return (1);
	return (0);
}

int	check_err(t_args *data, t_files *curr, int *in, int *out)
{
	if (*in == -1 || *out == -1)
	{
		perror(curr->word);
		g_minishell.exit_code = 1;
		data->exec = 1;
		return (1);
	}
	return (0);
}

int	get_in_out(t_args *data, t_files *curr, int *in, int *out)
{
	if (curr->type == RED_IN)
	{
		if (open_in(curr, in))
			return (data->exec = 1, 1);
	}
	else if (curr->type == RED_OUT)
	{
		if (*out != 1)
			close(*out);
		if (check_ambiguous(curr->word, curr->is_expanded))
			*out = open(curr->word, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else
			return (data->exec = 1, 1);
	}
	else if (curr->type == APPEND)
	{
		if (*out != 1)
			close(*out);
		if (check_ambiguous(curr->word, curr->is_expanded))
			*out = open(curr->word, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			return (data->exec = 1, 1);
	}
	return (check_err(data, curr, in, out));
}

int	open_files(t_args *data, int in, int out)
{
	t_files	*curr;
	char	*real_input;

	if (exec_heredoc(data))
		return (1);
	while (data)
	{
		in = 0;
		out = 1;
		curr = data->file;
		real_input = get_real_input(curr);
		while (curr)
		{
			if (get_in_out(data, curr, &in, &out))
				break ;
			if (real_input && cmp_str(real_input, curr->word))
				data->infile = in;
			curr = curr->next;
		}
		if (real_input)
			free(real_input);
		data->outfile = out;
		data = data->next;
	}
	return (0);
}
