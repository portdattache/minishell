/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:45:23 by garside           #+#    #+#             */
/*   Updated: 2025/06/04 22:34:15 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_get_cmd(t_data *data)
{
	t_token	*i;
	char	**cmd;
	int		len;
	int		j;

	len = 0;
	i = data->token;
	while (i && i->type == WORD)
	{
		len++;
		i = i->next;
	}
	cmd = malloc(sizeof(char *) * (len + 1));
	i = data->token;
	j = 0;
	while (i && i->type == WORD)
	{
		cmd[j++] = ft_strdup(i->value);
		i = i->next;
	}
	cmd[j] = NULL;
	return (cmd);
}
