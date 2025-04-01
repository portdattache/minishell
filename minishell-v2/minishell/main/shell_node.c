/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:44:53 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/22 14:01:15 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_node(t_shell *shell)
{
	shell = malloc(sizeof(t_shell));
	shell->exit_status = 0;
	shell->input_terminal = NULL;
	shell->cmd->cmds = NULL;
	shell->cmd->env = NULL;
	shell->cmd->next = NULL;
	shell->cmd->prev = NULL;
	shell->env->key = NULL;
	shell->env->value = NULL;
	shell->env->var = NULL;
	shell->env->next = NULL;
	shell->env->prev = NULL;
}
