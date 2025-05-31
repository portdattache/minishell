/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parce_util_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:19:03 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/31 12:18:09 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*parse_tokens(t_data *data)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_token	*token;

	head = NULL;
	curr = NULL;
	token = data->token;
	while (token)
	{
		init_cmd_node(&curr, &head);
		if (token->type == WORD)
			add_arg(curr, token->value);
		else if (token->type == REDIRECTION_IN && token->next)
			add_redir(&curr->infile, token->next->value, REDIRECTION_IN);
		else if (token->type == REDIRECTION_OUT && token->next)
			add_redir(&curr->outfile, token->next->value, REDIRECTION_OUT);
		else if (token->type == APPEND && token->next)
			add_redir(&curr->outfile, token->next->value, APPEND);
		else if (token->type == HEREDOC && token->next)
			add_redir(&curr->infile, token->next->value, HEREDOC);
		else if (token->type == PIPE)
			add_pipe_node(&curr);
		token = token->next;
	}
	return (head);
}

void	add_pipe_node(t_cmd **curr)
{
	(*curr)->next = new_cmd_node();
	*curr = (*curr)->next;
}

void	init_cmd_node(t_cmd **curr, t_cmd **head)
{
	if (!*curr)
	{
		*curr = new_cmd_node();
		if (!*head)
			*head = *curr;
	}
}
