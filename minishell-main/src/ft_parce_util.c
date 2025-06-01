/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parce_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 08:47:16 by garside           #+#    #+#             */
/*   Updated: 2025/06/01 23:56:49 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_arg(t_cmd *cmd, char *value)
{
	int		i;
	char	**new_args;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
			i++;
	}
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			new_args[i] = ft_strdup(cmd->args[i]);
			i++;
		}
		free_split(cmd->args);
	}
	new_args[i++] = ft_strdup(value);
	new_args[i] = NULL;
	cmd->args = new_args;
}

void	add_redir(t_redir **redir_list, char *filename, int type)
{
	t_redir	*new_node;
	t_redir	*tmp;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return ;
	if (type == HEREDOC)
		new_node->file = get_here_doc(filename);
	else
		new_node->file = ft_strdup(filename);
	new_node->type = type;
	new_node->next = NULL;
	if (*redir_list == NULL)
		*redir_list = new_node;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

t_cmd	*parse_tokens(t_data *data)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_token	*token;
	int		skip_next_word;

	head = NULL;
	curr = NULL;
	token = data->token;
	skip_next_word = 0;
	while (token)
	{
		if (!curr)
		{
			curr = new_cmd_node();
			if (!head)
				head = curr;
		}
		if (skip_next_word)
		{
			skip_next_word = 0;
			token = token->next;
			continue ;
		}
		if (token->type == WORD)
			add_arg(curr, token->value);
		else if (token->type == REDIRECTION_IN && token->next)
		{
			add_redir(&curr->infile, token->next->value, REDIRECTION_IN);
			skip_next_word = 1;
		}
		else if (token->type == REDIRECTION_OUT && token->next)
		{
			add_redir(&curr->outfile, token->next->value, REDIRECTION_OUT);
			skip_next_word = 1;
		}
		else if (token->type == APPEND && token->next)
		{
			add_redir(&curr->outfile, token->next->value, APPEND);
			skip_next_word = 1;
		}
		else if (token->type == HEREDOC && token->next)
		{
			add_redir(&curr->infile, token->next->value, HEREDOC);
			skip_next_word = 1;
		}
		else if (token->type == PIPE)
		{
			curr->next = new_cmd_node();
			curr = curr->next;
		}
		token = token->next;
	}
	return (head);
}
