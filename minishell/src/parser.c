/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:13:50 by garside           #+#    #+#             */
/*   Updated: 2025/06/05 13:10:15 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_next_token(t_data *data, int *i)
{
	if (data->input[*i] == '>' || data->input[*i] == '<')
		return (handle_redirection(data->input, i));
	if (data->input[*i] == '|')
		return (handle_pipe(i));
	return (handle_cmd_or_arg(data, i));
}

int	valid_parse(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type != WORD && !tmp->next && tmp->type != PIPE)
		{
			data->last_status = 2;
			return (printf("%s `newline`\n", ERR_SYNT), 1);
		}
		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
		{
			data->last_status = 2;
			return (printf("%s `|`\n", ERR_SYNT), 1);
		}
		if ((tmp->type != WORD && tmp->type != PIPE) && (tmp->next
				&& tmp->next->type != WORD))
		{
			data->last_status = 2;
			return (printf("%s `%s`\n", ERR_SYNT, tmp->next->value), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	print_pipe_error(t_data *data)
{
	data->last_status = 2;
	printf("%s `|'\n", ERR_SYNT);
}

// int	parse(t_data *data)
// {
// 	t_token	*token;

// 	if (!data->input)
// 		return (1);
// 	data->token = ft_lexer(data);
// 	if (!data->token)
// 		return (1);
// 	token = data->token;
// 	if (valid_parse(data) == 1)
// 		return (1);
// 	if (token->type == PIPE)
// 		return (printf("%s `|'\n", ERR_SYNT), 1);
// 	while (token && token->next)
// 		token = token->next;
// 	if (token->type == PIPE)
// 	{
// 		print_pipe_error(data);
// 		return (1);
// 	}
// 	data->cmd_list = parse_tokens(data);
// 	if (!data->cmd_list)
// 		return (1);
// 	if (!data->cmd_list->args && !data->cmd_list->outfile
// 		&& !data->cmd_list->infile)
// 		return (1);
// 	return (0);
// }

int	check_token_errors(t_data *data, t_token *token)
{
	if (valid_parse(data) == 1)
		return (1);
	if (token->type == PIPE)
		return (printf("%s `|'\n", ERR_SYNT), 1);
	while (token && token->next)
		token = token->next;
	if (token->type == PIPE)
	{
		print_pipe_error(data);
		return (1);
	}
	return (0);
}

int	parse(t_data *data)
{
	t_token	*token;

	if (!data->input)
		return (1);
	data->token = ft_lexer(data);
	if (!data->token)
		return (1);
	token = data->token;
	if (check_token_errors(data, token))
		return (1);
	data->cmd_list = parse_tokens(data);
	if (!data->cmd_list)
		return (1);
	if (!data->cmd_list->args && !data->cmd_list->outfile
		&& !data->cmd_list->infile)
		return (1);
	return (0);
}
