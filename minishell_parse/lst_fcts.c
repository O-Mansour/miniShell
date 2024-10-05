/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fcts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:09:16 by omansour          #+#    #+#             */
/*   Updated: 2023/07/24 11:16:55 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_args	*ft_lstnew(char **tmp_cmd, t_files *tmp_file)
{
	t_args	*ptr;

	ptr = (t_args *) malloc(sizeof(t_args));
	if (!ptr)
		return (NULL);
	ptr->infile = 0;
	ptr->outfile = 1;
	ptr->exec = 0;
	ptr->cmd = tmp_cmd;
	ptr->file = tmp_file;
	ptr->next = NULL;
	return (ptr);
}

void	ft_lstadd_back(t_args **lst, t_args *new)
{
	t_args	*curr;

	if (!*lst)
		*lst = new;
	else
	{
		curr = *lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

t_files	*new_lstfile(int type, char *word)
{
	t_files	*ptr;

	ptr = (t_files *) malloc(sizeof(t_files));
	if (!ptr)
		return (NULL);
	ptr->type = type;
	ptr->is_expanded = 0;
	ptr->expand_heredoc = 1;
	ptr->word = ft_strdup(word);
	ptr->next = NULL;
	return (ptr);
}

void	lstfile_addback(t_files **lst, t_files *new)
{
	t_files	*curr;

	if (!*lst)
		*lst = new;
	else
	{
		curr = *lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}
