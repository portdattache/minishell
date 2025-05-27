/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:09:03 by garside           #+#    #+#             */
/*   Updated: 2025/05/27 14:09:37 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_executables(t_data *data, t_cmd *cmd, t_exec_fd *fds)
{
	struct stat	stat_info;
	int			status;
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork failed\n", 2), 127);
	if (pid == 0)
	{
		if (!cmd || !cmd->args || !cmd->args[0])
		{
			ft_putstr_fd("Error: invalid command or arguments\n", 2);
			free_cmd_list(data);
			free_data(data);
			exit(1);
		}
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
		if (stat(cmd->args[0], &stat_info) == 0)
		{
			if (S_ISDIR(stat_info.st_mode))
			{
				is_a_directory(cmd->args[0]);
				free_cmd_list(data);
				free_data(data);
				exit(126);
			}
		}
		execve(cmd->args[0], cmd->args, data->envp);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_cmd_list(data);
		free_data(data);
		exit(127);
	}
	waitpid(pid, &status, 0);
	return ((status >> 8) & 0xFF);
}

void	exec_child_process(t_data *data, t_exec_fd *fds)
{
	char	**cmd;
	char	*path;

	cmd = ft_get_cmd(data);
	path = get_cmd_path(data, cmd);
	close(fds->saved_stdin);
	close(fds->saved_stdout);
	if (!path)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(data->token->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_cmd_list(data);
		free_data(data);
		free_split(cmd);
		exit(127);
	}
	execve(path, cmd, data->envp);
	ft_putstr_fd("execve failed\n", 2);
	free_cmd_list(data);
	free_data(data);
	free_split(cmd);
	free(path);
	exit(127);
}
