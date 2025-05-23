/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:20:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/23 13:50:24 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_data *data)
{
	t_token	*first;

	if (!data->input)
		return (1);
	data->token = ft_lexer(data);
	if (!data->token)
		return (1);
	first = data->token;
	if (data->token)
	{
		if (first->type == 1 || first->type == 2 || first->type == 3
			|| first->type == 4 || first->type == 5)
			return (1);
	}
	while (first && first->next)
		first = first->next;
	if (first && first->type == 1)
	{
		g_status = 2;
		printf("minishell: syntax error near unexpected token `|`\n");
		return (1);
	}
	data->cmd_list = parse_tokens(data);
	if (!data->cmd_list)
		return (1);
	return (0);
}
