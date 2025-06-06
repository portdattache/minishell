/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:11:44 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/06 18:08:44 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	empty_dollar(t_data *data, t_cmd *cmd)
{
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
	{
		free_cmd_list(data);
		free_data(data);
		exit(0);
	}
	return ;
}

void	secure_dup2(int old_fd, int new_fd)
{
	if (old_fd < 0)
		perror("dup2: invalid fd");
	if (dup2(old_fd, new_fd) == -1)
		perror("dup2 failed");
}

void	secure_dup(int old_fd, int new_fd)
{
	if (old_fd < 0)
		perror("dup: invalid fd");
	if (dup(new_fd) == -1)
		perror("dup2 failed");
}
