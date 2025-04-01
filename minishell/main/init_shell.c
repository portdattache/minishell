/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:37:26 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/01 09:48:03 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(t_shell *shell)
{
}

void	cleanup_shell(t_shell *shell)
{
	t_env	*tmp;
	t_env	*next;

	tmp = shell->env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->var);
		free(tmp);
		tmp = next;
	}
	shell->env = NULL;
}

// void	init_shell(t_shell *shell)
// {
// 	shell->env = NULL;
// 	shell->cmd = NULL;
// 	shell->input = NULL;
// 	shell->env_array = NULL;
// 	shell->exit_status = 0;
// 	init_default_env(shell);
// }

// void	init_default_env(t_shell *shell)
// {
// 	t_env *new;
// 	new = create_env_node("PWD", getcwd(NULL,0));
// 	if(!new)
// 		exit_shell(shell, EXIT_FAILURE);
// 	add_env_node(shell,new);
// }
