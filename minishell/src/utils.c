/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:58:27 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/30 17:00:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_skippable_char(char c)
{
	return (c && c != '|' && c != '<' && c != '>' && c != ' ' && c != '\t'
		&& c != '\'' && c != '\"' && c != '$');
}

int	is_token_char(char c)
{
	return (c && c != '|' && c != '<' && c != '>' && c != ' ' && c != '\t');
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}
