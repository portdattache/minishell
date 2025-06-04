/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:09:23 by garside           #+#    #+#             */
/*   Updated: 2025/06/04 10:30:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_line(t_data *data, t_cmd *cmd)
{
	int		prev_fd;
	pid_t	last_pid;

	prev_fd = -1;
	last_pid = -1;
	if (cmd->next == NULL)
		return (handle_single_command(data, cmd, prev_fd));
	while (cmd)
	{
		if (cmd->next != NULL && pipe(cmd->pipe_fd) == -1)
			return (perror("pipe error"), 1);
		handle_useless_command(cmd, &prev_fd);
		last_pid = ft_process(data, cmd, prev_fd);
		if (prev_fd != -1)
			safe_close(prev_fd);
		if (cmd->next != NULL)
			maybe_close(cmd, &prev_fd);
		else
			prev_fd = -1;
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		safe_close(prev_fd);
	return (wait_for_children(last_pid));
}

int	exec_child_process(t_data *data, t_cmd *cmd, int prev_fd)
{
	char	**args;
	char	*path;

	reset_signals_child();
	signal(SIGPIPE, SIG_IGN);
	args = cmd->args;
	path = get_cmd_path(data, args);
	if (redirect_management(cmd, prev_fd) == -1)
		return (CODE_FAIL);
	if (cmd->saved_stdin != STDIN_FILENO)
		close(cmd->saved_stdin);
	if (cmd->saved_stdout != STDOUT_FILENO)
		close(cmd->saved_stdout);
	if (!path)
		is_not_path(data);
	execve(path, args, data->envp);
	ft_putstr_fd("execve failed\n", 2);
	if (data->cmd_list)
		free_cmd_list(data);
	if (data)
		free_data(data);
	free(path);
	exit(127);
}

int	ft_shell(t_data *data, t_cmd *cmd, int prev_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork failed\n", 2), 1);
	if (pid == 0)
		exec_child_process(data, cmd, prev_fd);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (WIFSIGNALED(status))
	{
		g_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		g_status = WEXITSTATUS(status);
	return (g_status);
}

int	handle_single_command(t_data *data, t_cmd *cmd, int prev_fd)
{
	if (cmd->next == NULL)
	{
		cmd->saved_stdin = dup(STDIN_FILENO);
		cmd->saved_stdout = dup(STDOUT_FILENO);
		if (cmd->saved_stdin < 0 || cmd->saved_stdout < 0)
			return (perror("dup"), CODE_FAIL);
		if (redirect_management(cmd, prev_fd) == 1)
		{
			safe_close(cmd->saved_stdin);
			safe_close(cmd->saved_stdout);
			return (CODE_FAIL);
		}
		g_status = which_command(data, cmd, prev_fd);
		dup2(cmd->saved_stdin, STDIN_FILENO);
		dup2(cmd->saved_stdout, STDOUT_FILENO);
		safe_close(cmd->saved_stdin);
		safe_close(cmd->saved_stdout);
		return (g_status);
	}
	return (0);
}

void	handle_useless_command(t_cmd *cmd, int *prev_fd)
{
	int	tmp_fd;

	if (!cmd->args)
	{
		if (cmd->outfile)
		{
			tmp_fd = last_outfile(cmd);
			if (tmp_fd != -1)
			{
				safe_close(tmp_fd);
				safe_close(*prev_fd);
			}
		}
		if (cmd->infile)
		{
			tmp_fd = last_infile(cmd);
			if (tmp_fd != -1)
			{
				safe_close(*prev_fd);
				safe_close(tmp_fd);
			}
		}
	}
}
