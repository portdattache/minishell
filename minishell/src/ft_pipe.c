/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:49:38 by broboeuf          #+#    #+#             */
/*   Updated: 2025/05/17 17:51:05 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  Gère les redirections d'entrée et de sortie pour la commande `cmd`.
//  Appelée dans le processus enfant avant l'exécution de la commande.
//  `prev_fd` est le descripteur de lecture du pipe de la commande précédente.
//  `cmd->pipe_fd` est le pipe pour la sortie de `cmd` vers la commande suivante.

static int	process_pre_fork_error(t_data *data, t_cmd *cmd, int code_stat)
{
	data->last_status = code_stat;
	if (cmd && cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	return (PID_ERROR_PRE_FORK);
}

static int	prepare_cmd_path(t_data *data, t_cmd *cmd)
{
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		if (access(cmd->args[0], F_OK) == -1)
		{
			no_such_file_or_directory(cmd->args[0]);
			return (process_pre_fork_error(data, cmd, 127));
		}
		cmd->path = ft_strdup(cmd->args[0]);
		if (!cmd->path)
		{
			error_message("ft_strdup in prepare_cmd_path");
			return (process_pre_fork_error(data, cmd, 1));
		}
	}
	else
	{
		cmd->path = find_cmd_path(cmd->args[0], data);
		if (!cmd->path)
		{
			command_not_found(cmd->args[0]);
			return (process_pre_fork_error(data, cmd, 127));
		}
	}
	return (0);
}

int	redirect_management(t_cmd *cmd, int prev_fd)
{
	/* Gère les redirections d'entrée (fichier ou pipe précédent) */
	if (manag_infile(cmd, prev_fd) == CODE_FAIL)
	{
		if (cmd->pipe_fd[0] != -1)
			safe_close(cmd->pipe_fd[0]);
		if (cmd->pipe_fd[1] != -1)
			safe_close(cmd->pipe_fd[1]);
		return (CODE_FAIL);
	}
	/* Gère les redirections de sortie (fichier ou pipe suivant) */
	if (manag_outfile(cmd, cmd->pipe_fd) == CODE_FAIL)
	{
		if (cmd->pipe_fd[0] != -1)
			safe_close(cmd->pipe_fd[0]);
		if (cmd->pipe_fd[1] != -1)
			safe_close(cmd->pipe_fd[1]);
		return (CODE_FAIL);
	}
	if (cmd->pipe_fd[0] != -1)
		safe_close(cmd->pipe_fd[0]);
	if (cmd->pipe_fd[1] != -1)
		safe_close(cmd->pipe_fd[1]);
	return (CODE_SUCCESS);
}

void	ft_exit_exec(int code, t_data *data, t_cmd *cmd)
{
	if (cmd && cmd->path)
		free(cmd->path);
	if (data)
	{
		/* Pas de free_cmd_list ou free_data ici pour l'enfant typiquement */
	}
	exit(code);
}

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

bool	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	return (false);
}

int	run_builtin(t_data *data, t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (CODE_FAIL);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(data));
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(data));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(data));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(data));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(data));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(data));
	return (CODE_FAIL);
}

//  s'assure d'appeler redirect_management

void	exec_child(t_data *data, t_cmd *cmd, int prev_fd)
{
	reset_signals_child();
	if (redirect_management(cmd, prev_fd) == CODE_FAIL)
		ft_exit_exec(1, data, cmd);
	if (!cmd->args || !cmd->args[0])
		ft_exit_exec(0, data, cmd);
	if (is_builtin(cmd->args[0]))
		ft_exit_exec(run_builtin(data, cmd), data, cmd);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
	{
		if (access(cmd->args[0], F_OK) == -1)
			no_such_file_or_directory(cmd->args[0]);
		else if (access(cmd->args[0], X_OK) == -1)
			permission_denied(cmd->args[0]);
		else
			execve(cmd->args[0], cmd->args, data->envp);
		ft_exit_exec(126, data, cmd);
	}
	if (cmd->path)
	{
		execve(cmd->path, cmd->args, data->envp);
		error_message(cmd->args[0]);
		ft_exit_exec(126, data, cmd);
	}
	command_not_found(cmd->args[0]);
	ft_exit_exec(127, data, cmd);
}

int	ft_process(t_data *data, t_cmd *cmd, int prev_fd)
{
	pid_t	pid;
	int		path_status;

	cmd->path = NULL;
	if (cmd->args && cmd->args[0] && !is_builtin(cmd->args[0]))
	{
		path_status = prepare_cmd_path(data, cmd);
		if (path_status == PID_ERROR_PRE_FORK)
			return (PID_ERROR_PRE_FORK);
	}
	pid = fork();
	if (pid < 0)
	{
		error_message("fork in ft_process");
		return (process_pre_fork_error(data, cmd, 1));
	}
	if (pid == 0)
		exec_child(data, cmd, prev_fd);
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	return (pid);
}
