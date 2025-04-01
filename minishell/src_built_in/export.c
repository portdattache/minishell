/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:00:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/21 10:05:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(char **args, t_shell *shell)
{
	int		i;
	char	*equal;

	i = 1;
	if (!args[i])
		return (ft_env(shell));
	while (args[i])
	{
		equal = ft_strchr(args[i], '=');
		if (equal)
		{
			*equal = '\0';
			add_or_update_env(shell, args[i], equal + 1);
			*equal = '=';
		}
		i++;
	}
	return (0);
}
