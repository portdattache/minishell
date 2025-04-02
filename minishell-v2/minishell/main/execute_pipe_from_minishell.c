/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_from_minishell.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:14:06 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 07:49:43 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipex_from_minishell(t_shell *shell)
{
	t_pipex	*pipex;

	if (!shell || !shell->cmd)
	{
		ft_printf("Error: Invalid shell or command\n");
		return ;
	}
	pipex = init_minishell_pipeline(shell->cmd, shell);
	if (!pipex)
	{
		ft_printf("Error: Init pipe failed\n");
		return ;
	}
	process_pipeline(pipex);
	ft_free_pipeline(pipex);
}
