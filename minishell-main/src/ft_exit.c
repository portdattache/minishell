/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:11:06 by garside           #+#    #+#             */
/*   Updated: 2025/06/01 21:30:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	error_allnum(t_data *data, t_cmd *cmd, int stdin, int stdout)
{
	ft_putstr_fd("exit: ", 1);
	ft_putstr_fd(cmd->args[1], 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	close(stdin);
	close(stdout);
	free_cmd_list(data);
	free_data(data);
	exit(2);
}

int	ft_exit(t_data *data, t_cmd *cmd, int stdin, int stdout)
{
	int	code;

	if (!cmd->args[1])
	{
		close(stdin);
		close(stdout);
		free_cmd_list(data);
		free_data(data);
		ft_printf("exit\n");
		exit(0);
	}
	else if (!ft_isalldigit(cmd->args[1]))
		error_allnum(data, cmd, stdin, stdout);
	else if (!cmd->args[1])
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	code = ft_atoi(cmd->args[1]);
	close(stdin);
	close(stdout);
	free_cmd_list(data);
	free_data(data);
	ft_printf("exit\n");
	exit(code);
	return (0);
}
