/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:09:03 by garside           #+#    #+#             */
/*   Updated: 2025/05/28 17:16:24 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_executables(t_data *data, t_cmd *cmd, t_exec_fd *fds)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork failed\n", 2), 127);
	if (pid == 0)
		ft_execve_child(data, cmd, fds);
	waitpid(pid, &status, 0);
	return ((status >> 8) & 0xFF);
}

void	ft_execve_child(t_data *data, t_cmd *cmd, t_exec_fd *fds)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		ft_exit_with_error(data, cmd, "Error: invalid command or arguments\n",
			1);
	ft_restore_std(fds);
	ft_check_directory(data, cmd);
	execve(cmd->args[0], cmd->args, data->envp);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_cmd_list(data);
	free_data(data);
	exit(127);
}

void	ft_restore_std(t_exec_fd *fds)
{
	if (fds->saved_stdin != STDIN_FILENO)
	{
		dup2(fds->saved_stdin, STDIN_FILENO);
		close(fds->saved_stdin);
	}
	if (fds->saved_stdout != STDOUT_FILENO)
	{
		dup2(fds->saved_stdout, STDOUT_FILENO);
		close(fds->saved_stdout);
	}
}

void	ft_check_directory(t_data *data, t_cmd *cmd)
{
	struct stat	stat_info;

	if (stat(cmd->args[0], &stat_info) == 0 && S_ISDIR(stat_info.st_mode))
	{
		is_a_directory(cmd->args[0]);
		free_cmd_list(data);
		free_data(data);
		exit(126);
	}
}

void	ft_exit_with_error(t_data *data, t_cmd *cmd, char *msg, int code)
{
	(void)cmd;
	ft_putstr_fd(msg, 2);
	free_cmd_list(data);
	free_data(data);
	exit(code);
}
