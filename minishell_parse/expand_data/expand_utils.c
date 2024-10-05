/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:45:18 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 20:54:01 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	joinable_char(char c)
{
	if (c == 95)
		return (0);
	if ((c == 9) || (c >= 32 && c <= 47) || (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
		return (1);
	return (0);
}

char	*get_key(char *str, int i)
{
	int		len;
	char	*key;

	len = i;
	if (!str || !str[i])
		return (NULL);
	while (str[len])
	{
		if (joinable_char(str[len]))
			break ;
		len++;
	}
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	len = 0;
	while (str[i] && !joinable_char(str[i]))
		key[len++] = str[i++];
	key[len] = '\0';
	return (key);
}

char	*get_full_key(char *str, int i)
{
	int		len;
	char	*key;

	len = i;
	if (!str || !str[i])
		return (NULL);
	while (str[len])
	{
		if (joinable_char(str[len]))
			break ;
		len++;
	}
	key = malloc(sizeof(char) * (len - i + 1));
	if (!key)
		return (NULL);
	len = 0;
	while (str[i] && (!joinable_char(str[i]) || ft_isalnum(str[i])))
		key[len++] = str[i++];
	key[len] = '\0';
	return (key);
}

void	expansion_helper(char **tmp_str, char *cmd, int *j)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	value = NULL;
	tmp = g_minishell.env;
	key = get_key(cmd, *j);
	if (!key)
		return ;
	while (tmp)
	{
		if (cmp_str(key, tmp->key))
		{
			if (tmp->value)
				value = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
	if (value)
		*tmp_str = put_value(*tmp_str, value);
	*j += ft_strlen(key) - 1;
	free(key);
}

int	key_expansion(char **tmp_str, char *cmd, int *j, int in_double)
{
	char	*key;

	key = NULL;
	if (cmd[*j] == '?' && !g_minishell.expand_value)
		*tmp_str = put_value(*tmp_str, ft_itoa(g_minishell.exit_code));
	else if (cmd[*j] == '?' && g_minishell.expand_value)
		*tmp_str = put_value(*tmp_str, ft_itoa(0));
	else if (cmd[*j] == '@' || cmd[*j] == '*' || ft_isdigit(cmd[*j]))
	{
		(*j)++;
		key = get_full_key(cmd, *j);
		*j += ft_strlen(key) - 1;
		*tmp_str = put_value(*tmp_str, key);
	}
	else if (cmd[*j] && !joinable_char(cmd[*j]))
		expansion_helper(tmp_str, cmd, j);
	else if (!(in_double % 2) && (cmd[*j] == '"' || cmd[*j] == '\''))
		return (1);
	else
	{
		*tmp_str = add_char(*tmp_str, cmd[--(*j)]);
		if (cmd[*j + 1] == '$')
			*tmp_str = add_char(*tmp_str, cmd[(*j)++]);
	}
	return (0);
}
