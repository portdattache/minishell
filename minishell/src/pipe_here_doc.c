/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:49:33 by garside           #+#    #+#             */
/*   Updated: 2025/06/05 18:56:10 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_here_doc(char *str)
{
	char				*file_name;
	char				*delimitor;
	int					here_doc_fd;
	pid_t				pid;
	int					status;
	struct sigaction	sa;

	file_name = NULL;
	delimitor = ft_strdup(str);
	made_new_file(&here_doc_fd, &file_name);
	if (here_doc_fd == -1)
		return (ft_printf("error to create a tmp file\n"), NULL);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(file_name), free(delimitor), NULL);
	if (pid == 0)
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sa.sa_handler = handle_sigint_heredoc;
		sigaction(SIGINT, &sa, NULL);
		fill_here_doc_file(here_doc_fd, delimitor);
		cleanup_here_doc(file_name, delimitor, here_doc_fd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	free(delimitor);
	close(here_doc_fd);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(file_name);
		free(file_name);
		g_status = 130;
		return (NULL);
	}
	return (file_name);
}

void	made_new_file(int *fd, char **name)
{
	static int	nb_file = 0;
	char		*nb_str;

	nb_str = ft_itoa(nb_file);
	*name = ft_strjoin("/tmp/here_doc_", nb_str);
	free(nb_str);
	*fd = open(*name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	nb_file++;
}

void	fill_here_doc_file(int fd, char *delimitor)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (str == NULL)
		{
			ft_printf("bash: warning: here-document delimited"
						" by end-of-file (wanted `%s')\n",
						delimitor);
			break ;
		}
		if (ft_strcmp(str, delimitor) == 0)
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
		free(str);
	}
}

void	cleanup_here_doc(char *file_name, char *delimitor, int fd)
{
	if (file_name)
		free(file_name);
	if (delimitor)
		free(delimitor);
	if (fd >= 0)
		close(fd);
}
