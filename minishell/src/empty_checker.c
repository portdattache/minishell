/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:11:44 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/06 14:19:29 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	empty_dollar(t_data *data, t_cmd *cmd)
{
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("\n", 2);
		free_cmd_list(data);
		free_data(data);
		exit(0);
	}
	return ;
}
