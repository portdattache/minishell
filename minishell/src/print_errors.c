/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 02:51:50 by garside           #+#    #+#             */
/*   Updated: 2025/06/06 11:28:58 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	command_not_found(char *cmd)
{
	ft_putstr_fd("Minishell:~$ ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Command not found\n", 2);
}

void	no_such_file_or_directory(char *cmd)
{
	char	*message;
	char	*pref;
	char	*suf;

	pref = "Minishell:~$ ";
	suf = ": No such file or directory\n";
	message = ft_strjoin_three(pref, cmd, suf);
	if (message)
	{
		ft_putstr_fd(message, 2);
		free(message);
	}
	else
	{
		ft_putstr_fd(pref, 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(suf, 2);
	}
}

void	permission_denied(char *file)
{
	ft_putstr_fd("Minishell:~$ ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	error_message(char *str)
{
	ft_putstr_fd("Minishell:~$ ", 2);
	perror(str);
}

void	is_a_directory(char *str)
{
	ft_putstr_fd("Minishell:~$ ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}
