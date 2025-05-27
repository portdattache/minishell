/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:09:23 by garside           #+#    #+#             */
/*   Updated: 2025/05/27 14:13:02 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_fd_cloexec(int fd)
{
	int	flags;

	flags = fcntl(fd, F_GETFD);
	if (flags == -1)
		return (-1);
	flags |= FD_CLOEXEC;
	if (fcntl(fd, F_SETFD, flags) == -1)
		return (-1);
	return (0);
}

char	*get_cmd_path(t_data *data, char **cmd)
{
	if (data->token->value[0] == '/')
		return (ft_strdup(cmd[0]));
	return (find_cmd_path(cmd[0], data));
}

int	ft_shell(t_data *data, t_exec_fd *fds)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork failed\n", 2), 1);
	if (pid == 0)
		exec_child_process(data, fds);
	waitpid(pid, &status, 0);
	return ((status >> 8) & 0xFF);
}

int	which_command(t_data *data, t_cmd *cmd, t_exec_fd *fds)
{
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(data));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(data));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(data, cmd, fds));
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(data, cmd));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(data));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(data));
	if (ft_strncmp(cmd->args[0], "./", 2) == 0)
		return (ft_executables(data, cmd, fds));
	return (ft_shell(data, fds));
}

int	handle_single_command(t_data *data, t_cmd *cmd)
{
	t_exec_fd	fds;
	int			ret;

	fds.prev_fd = -1;
	fds.saved_stdin = dup(STDIN_FILENO);
	fds.saved_stdout = dup(STDOUT_FILENO);
	if (fds.saved_stdin < 0 || fds.saved_stdout < 0)
		return (perror("dup"), CODE_FAIL);
	if (redirect_management(cmd, fds.prev_fd) == -1)
	{
		set_fd_cloexec(fds.saved_stdin);
		set_fd_cloexec(fds.saved_stdout);
		return (CODE_FAIL);
	}
	g_status = which_command(data, cmd, &fds);
	dup2(fds.saved_stdin, STDIN_FILENO);
	dup2(fds.saved_stdout, STDOUT_FILENO);
	close(fds.saved_stdin);
	close(fds.saved_stdout);
	return (g_status);
}
