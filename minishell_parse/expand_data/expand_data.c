/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:38:59 by omansour          #+#    #+#             */
/*   Updated: 2023/08/04 07:30:26 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*put_value(char *tmp_str, char *value)
{
	char	*new_value;
	char	*tmp;

	tmp = value;
	if (!tmp)
		return (NULL);
	if (!tmp_str)
		return (tmp);
	new_value = ft_strjoin(tmp_str, tmp);
	free(tmp);
	free(tmp_str);
	if (!new_value)
		return (NULL);
	return (new_value);
}

void	quotes_expansion(char **tmp_str, char *cmd, int *j, int *in_double)
{
	if (cmd[*j] == '"')
	{
		(*in_double)++;
		*tmp_str = add_char(*tmp_str, cmd[*j]);
	}
	else if (cmd[*j] == '\'' && !(*in_double % 2))
	{
		*tmp_str = add_char(*tmp_str, cmd[*j]);
		(*j)++;
		while (cmd[*j] != '\'')
		{
			*tmp_str = add_char(*tmp_str, cmd[*j]);
			(*j)++;
		}
		*tmp_str = add_char(*tmp_str, cmd[*j]);
	}
}

char	*expand_key(char *cmd, t_files *cur)
{
	char	*tmp_str;
	int		in_double;
	int		j;

	in_double = 0;
	j = 0;
	tmp_str = ft_strdup("");
	while (cmd[j])
	{
		if (cmd[j] == '"' || (cmd[j] == '\'' && !(in_double % 2)))
			quotes_expansion(&tmp_str, cmd, &j, &in_double);
		else if (cmd[j] == '$')
		{
			j++;
			if (cur)
				cur->is_expanded = 1;
			if (key_expansion(&tmp_str, cmd, &j, in_double))
				continue ;
		}
		else
			tmp_str = add_char(tmp_str, cmd[j]);
		j++;
	}
	return (tmp_str);
}

void	expand_n_replace(char **s1, t_files *cur)
{
	char	*tmp_str;

	tmp_str = expand_key(*s1, cur);
	free(*s1);
	*s1 = tmp_str;
}

void	expand_data(t_args *curr)
{
	int		i;
	t_files	*cur;

	g_minishell.expand_value = -1;
	while (curr)
	{
		i = -1;
		g_minishell.expand_value++;
		while (curr->cmd && curr->cmd[++i])
			expand_n_replace(&curr->cmd[i], NULL);
		cur = curr->file;
		while (cur)
		{
			if (cur->type != HERE_DOC)
				expand_n_replace(&cur->word, cur);
			cur = cur->next;
		}
		curr = curr->next;
	}
}
