/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_from_minishell.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:14:06 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/25 12:12:26 by bcaumont         ###   ########.fr       */
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

// void	pipe_execution(t_pipex *pipex)
// {
// 	t_pipex	*current;

// 	current = pipex;
// 	while (current)
// 	{
// 		current->pid = fork();
// 		if (current->pid == -1)
// 		{
// 			perror("fork");
// 			return ;
// 		}
// 		if (current->pid == 0)
// 		{
// 			secure_dup(current);
// 			execve(get_path(current), current->args, current->envp);
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 		current = current->next;
// 	}
// 	current = pipex;
// 	while (current)
// 	{
// 		waitpid(current->pid, NULL, 0);
// 		current = current->next;
// 	}
// }

// void	secure_dup(t_pipex *current)
// {
// 	if (current->is_first)
// 	{
// 		if (dup2(current->pipefd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 (stdout first cmd)");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (current->is_last)
// 	{
// 		if (dup2(current->prev->pipefd[0], STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 (stdin last cmd)");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{
// 		if (dup2(current->prev->pipefd[0], STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 (stdin middle cmd)");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (dup2(current->prev->pipefd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 (stdout middle cmd)");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	close(current->pipefd[0]);
// 	close(current->pipefd[1]);
// 	if (current->prev)
// 	{
// 		close(current->prev->pipefd[0]);
// 		close(current->prev->pipefd[1]);
// 	}
// }