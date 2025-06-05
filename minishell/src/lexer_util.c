/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:49:50 by garside           #+#    #+#             */
/*   Updated: 2025/06/04 22:34:16 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_error_code(t_data *data, char *value, int *i)
{
	char	*tmp;
	char	*temp;

	(void)data;
	(*i) += 2;
	tmp = ft_itoa(data->last_status);
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

char	*handle_env_value(t_data *data, int *i, char *value)
{
	char	*tmp;
	char	*temp;

	if (data->input[*i + 1] == '?')
		return (handle_error_code(data, value, i));
	tmp = change_env(data, i);
	temp = ft_strjoin(value, tmp);
	free(tmp);
	free(value);
	return (temp);
}

char	*handle_plain_text(t_data *data, int *i, char *value)
{
	int		start;
	int		len;
	char	*tmp;
	char	*temp;

	start = *i;
	while (is_skippable_char(data->input[*i]))
		(*i)++;
	len = *i - start;
	tmp = ft_substr(data->input, start, len);
	temp = ft_strjoin(value, tmp);
	free(tmp);
	free(value);
	return (temp);
}

t_token	*handle_pipe(int *i)
{
	char	*value;
	t_token	*token;

	value = ft_strdup("|");
	if (!value)
		return (NULL);
	token = new_token(value, PIPE);
	(*i)++;
	free(value);
	return (token);
}
