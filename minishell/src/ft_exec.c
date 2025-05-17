/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:09:23 by garside           #+#    #+#             */
/*   Updated: 2025/05/17 16:55:45 by broboeuf         ###   ########.fr       */
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

void	exec_child_process(t_data *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_get_cmd(data);
	path = get_cmd_path(data, cmd);
	if (!path)
	{
		ft_putstr_fd(data->token->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_data(data);
		free_split(cmd);
		exit(127);
	}
	execve(path, cmd, data->envp);
	ft_putstr_fd("execve failed\n", 2);
	free_data(data);
	free_split(cmd);
	free(path);
	exit(127);
}

int	ft_shell(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("fork failed\n", 2), 1);
	if (pid == 0)
		exec_child_process(data);
	waitpid(pid, &status, 0);
	return ((status >> 8) & 0xFF);
}

int	which_command(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(data));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(data));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(data));
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(data));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(data));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(data));
	if (ft_strncmp(cmd->args[0], "./", 2) == 0)
		return (ft_executables(data));
	return (ft_shell(data));
}

static int	execute_single_cmd_logic(t_data *data, t_cmd *cmd, int prev_fd)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd->args[0]) && (ft_strcmp(cmd->args[0], "cd") == 0
			|| ft_strcmp(cmd->args[0], "export") == 0 || ft_strcmp(cmd->args[0],
				"unset") == 0 || ft_strcmp(cmd->args[0], "exit") == 0))
	{
		data->last_status = run_builtin(data, cmd);
	}
	else /* Commandes externes ou builtins exécutables dans un sous-processus */
	{
		pid = ft_process(data, cmd, prev_fd); /* Utilise ft_process corrigé */
		if (pid > 0)
		/* Si le fork a réussi et que ce n'est pas une erreur pré-fork */
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				data->last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->last_status = 128 + WTERMSIG(status);
			/* data->last_status est déjà mis à jour par ft_process si pid == PID_ERROR_PRE_FORK */
		}
	}
	return (data->last_status);
}

/* Fonction auxiliaire pour exec_line: gestion d'une commande unique (avec I/O) */
static int	handle_single_command(t_data *data, t_cmd *cmd_iterator)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
	{
		error_message("dup for saved_std_io in handle_single_command");
		if (saved_stdin >= 0)
			close(saved_stdin);
		if (saved_stdout >= 0)
			close(saved_stdout);
		return (1); /* Erreur critique */
	}
	if (redirect_management(cmd_iterator, -1) == CODE_FAIL) /* prev_fd est -1 */
		data->last_status = 1;
	/* Erreur de redirection */
	else
		execute_single_cmd_logic(data, cmd_iterator, -1);
	/* Restaurer stdin/stdout quoi qu'il arrive */
	if (dup2(saved_stdin, STDIN_FILENO) < 0)
		error_message("dup2 restore_stdin in handle_single_command");
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		error_message("dup2 restore_stdout in handle_single_command");
	close(saved_stdin);
	close(saved_stdout);
	return (data->last_status);
}

/* Fonction auxiliaire pour exec_line: exécution d'une commande dans un pipeline */
static pid_t	exec_pipeline_cmd_step(t_data *data, t_cmd *cmd_iterator,
		int *prev_fd_ptr)
{
	pid_t current_pid;              /* Variable locale */
	if (cmd_iterator->next != NULL) /* S'il y a une commande suivante,
		créer un pipe */
	{
		if (pipe(cmd_iterator->pipe_fd) == -1)
		{
			error_message("pipe in exec_pipeline_cmd_step");
			if (*prev_fd_ptr != -1)
				close(*prev_fd_ptr);
			data->last_status = 1;
			return (PID_ERROR_PRE_FORK);
			/* Indique une erreur critique de pipe */
		}
	}
	else /* Dernière commande du pipeline */
	{
		cmd_iterator->pipe_fd[0] = -1;
		cmd_iterator->pipe_fd[1] = -1;
	}
	current_pid = ft_process(data, cmd_iterator, *prev_fd_ptr);
	if (*prev_fd_ptr != -1)
		/* Fermer le read_end du pipe précédent DANS LE PARENT */
		close(*prev_fd_ptr);
	if (current_pid == PID_ERROR_PRE_FORK && cmd_iterator->next != NULL)
	{
		/* Fermer le pipe qu'on vient de créer si erreur avant fork pour cette cmd */
		safe_close(cmd_iterator->pipe_fd[0]);
		safe_close(cmd_iterator->pipe_fd[1]);
		cmd_iterator->pipe_fd[0] = -1;
		cmd_iterator->pipe_fd[1] = -1;
	}
	if (cmd_iterator->next != NULL && current_pid != PID_ERROR_PRE_FORK)
	{
		/* S'il y a une suite ET que le fork a réussi pour cette cmd */
		close(cmd_iterator->pipe_fd[1]);
		/* Write end plus nécessaire dans le parent */
		*prev_fd_ptr = cmd_iterator->pipe_fd[0];
		/* Read end pour la prochaine cmd */
	}
	else
		*prev_fd_ptr = -1; /* Pas de pipe suivant ou erreur */
	return (current_pid);
}

/* Fonction auxiliaire pour exec_line: attente des enfants du pipeline */
static void	wait_pipeline_children(t_data *data, pid_t last_pid_val)
{
	int	pipeline_final_status;

	pid_t wpid; /* Nom de variable original (de la portée parente) */
	int status; /* Nom de variable original (de la portée parente) */
	pipeline_final_status = data->last_status;
	/* Init avec erreur pré-fork si pertinent */
	/* Si last_pid_val est -1 (ex: la dernière cmd a échoué avant fork),
		data->last_status contient déjà le code d'erreur pertinent. */
	while ((wpid = wait(&status)) > 0) /* Attendre tous les enfants */
	{
		if (wpid == last_pid_val)
		/* Si c'est le dernier processus de la pipeline */
		{
			if (WIFEXITED(status))
				pipeline_final_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				pipeline_final_status = 128 + WTERMSIG(status);
		}
	}
	/* Si last_pid_val était
		-1 (aucune commande n'a réellement forké ou la dernière
		a échoué avant fork),
			pipeline_final_status garde la valeur de data->last_status
		qui aurait été mise à jour par la dernière tentative de ft_process. */
	data->last_status = pipeline_final_status;
}

//  interpretait mal les retours de ft_process (codes d'erreur pris pour des pids)
// logique de pipeline et gestion des pids/statuts trop complexe
// fix : gere PID_ERROR_PRE_FORK
// divise en fonctions pour la clarte et la norme
// last_pid garde le pid du dernier process lance dans le pipeline

int	exec_line(t_data *data, t_cmd *cmd) /* `cmd` ici est la tête de liste */
{
	t_cmd *cmd_iterator;   /* Nouvel itérateur pour ne pas modifier `cmd` */
	int prev_fd;           /* Nom de variable original */
	pid_t last_pid;        /* Nom de variable original,
		pour le dernier PID du pipeline */
	pid_t current_cmd_pid; /* PID de la commande en cours de traitement */

	cmd_iterator = cmd;
	if (!cmd_iterator)
		return (data->last_status); /* Aucune commande à exécuter */
	/* Cas d'une seule commande (pas de pipe) */
	if (cmd_iterator->next == NULL)
		return (handle_single_command(data, cmd_iterator));
	/* Cas de plusieurs commandes (pipeline) */
	prev_fd = -1;
	last_pid = -1; /* Initialiser à une valeur non-PID valide */
	while (cmd_iterator)
	{
		current_cmd_pid = exec_pipeline_cmd_step(data, cmd_iterator, &prev_fd);
		if (prev_fd == PID_ERROR_PRE_FORK)
			/* Erreur critique de pipe dans l'auxiliaire */
			break ;
		/* Arrêter le traitement du pipeline */
		if (current_cmd_pid != PID_ERROR_PRE_FORK)
			last_pid = current_cmd_pid; /* Mémoriser le dernier PID réel */
		/* Si current_cmd_pid est PID_ERROR_PRE_FORK,
			data->last_status a été mis.
			Si c'est la dernière commande du pipeline qui échoue avant fork,
			last_pid ne sera pas mis à jour, et wait_pipeline_children
			utilisera data->last_status. */
		else if (cmd_iterator->next == NULL)
			/* Erreur sur la dernière commande */
			break ;
		/* Pas besoin d'attendre si la dernière cmd n'a pas forké */
		cmd_iterator = cmd_iterator->next;
	}
	wait_pipeline_children(data, last_pid);
	return (data->last_status);
}
