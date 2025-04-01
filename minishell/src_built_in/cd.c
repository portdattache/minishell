/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:59:27 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/21 09:02:39 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **args, t_shell *shell)
{
	(void)shell;
	if (!args[1])
	{
		write(2, "cd: missing argument\n", 21);
		return (1);
	}
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
