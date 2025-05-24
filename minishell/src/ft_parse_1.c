/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:20:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/24 15:45:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_data *data)
{
	if (!data->input)
		return (1);
	data->token = ft_lexer(data);
	if (!data->token)
		return (1);
	if (check_tokens_validity(data->token))
		return (1);
	data->cmd_list = parse_tokens(data);
	if (!data->cmd_list)
		return (1);
	return (0);
}

int	check_tokens_validity(t_token *token)
{
	t_token	*last;

	if (!token)
		return (1);
	if (token->type >= 1 && token->type <= 5)
		return (1);
	last = token;
	while (last->next)
		last = last->next;
	if (last && last->type == 1)
	{
		g_status = 2;
		printf("minishell: syntax error near unexpected token `|`\n");
		return (1);
	}
	return (0);
}
