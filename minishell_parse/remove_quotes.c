/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:48:56 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 17:51:51 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_char(char *str, char c)
{
	char	*new_str;
	int		i;

	new_str = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	if (str)
		free(str);
	return (new_str);
}

char	*remove_cmd_quotes(char *cmd)
{
	char	*str;
	int		j;
	char	c;

	str = ft_strdup("");
	j = -1;
	while (cmd[++j])
	{
		if (cmd[j] == '"' || cmd[j] == '\'')
		{
			c = cmd[j];
			while (cmd[++j] && cmd[j] != c)
				str = add_char(str, cmd[j]);
		}
		else
			str = add_char(str, cmd[j]);
	}
	return (str);
}

char	*r_file_quotes(char *file, int type, int *expand_heredoc)
{
	char	*str;
	int		j;
	char	c;

	str = ft_strdup("");
	j = -1;
	while (file[++j])
	{
		if (file[j] == '"' || file[j] == '\'')
		{
			if (type == HERE_DOC)
				*expand_heredoc = 0;
			c = file[j];
			while (file[++j] && file[j] != c)
				str = add_char(str, file[j]);
		}
		else
			str = add_char(str, file[j]);
	}
	return (str);
}

void	remove_quotes(t_args *data)
{
	int		i;
	char	*str;
	t_files	*cur;

	while (data)
	{
		i = -1;
		while (data->cmd && data->cmd[++i])
		{
			str = remove_cmd_quotes(data->cmd[i]);
			free(data->cmd[i]);
			data->cmd[i] = str;
		}
		cur = data->file;
		while (cur && cur->word)
		{
			str = r_file_quotes(cur->word, cur->type, &(cur->expand_heredoc));
			free(cur->word);
			cur->word = str;
			cur = cur->next;
		}
		data = data->next;
	}
}
