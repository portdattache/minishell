/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:47:48 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/04 22:34:38 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_whitespace(const char *input, int *i)
{
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
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

int	is_skippable_char(char c)
{
	return (c && c != '|' && c != '<' && c != '>' && c != ' ' && c != '\t'
		&& c != '\'' && c != '\"' && c != '$');
}

int	is_token_char(char c)
{
	return (c && c != '|' && c != '<' && c != '>' && c != ' ' && c != '\t');
}

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}
