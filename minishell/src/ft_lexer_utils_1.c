/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:49:50 by garside           #+#    #+#             */
/*   Updated: 2025/05/28 17:50:36 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_error_code(t_data *data, char *value, int *i)
{
	char	*tmp;
	char	*temp;

	(void)data;
	(*i) += 2;
	tmp = ft_itoa(g_status);
	temp = ft_strjoin(value, tmp);
	free(tmp);
	if (value)
		free(value);
	value = temp;
	return (value);
}

void	add_token_to_list(t_token **head, t_token **last, t_token *new_token)
{
	if (!*head)
		*head = new_token;
	else
		(*last)->next = new_token;
	*last = new_token;
}
