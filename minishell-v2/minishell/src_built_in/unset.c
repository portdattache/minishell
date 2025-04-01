/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:16:20 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/21 10:21:43 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (!args[i])
	{
		write(2, "unset: missing argument\n", 24);
		return (1);
	}
	while (args[i])
	{
		remove_env(shell, args[i]);
		i++;
	}
	return (0);
}
