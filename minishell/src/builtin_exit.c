/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:11:06 by garside           #+#    #+#             */
/*   Updated: 2025/06/03 17:07:12 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalldigit(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (0);
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
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	close(stdin);
	close(stdout);
	free_cmd_list(data);
	free_data(data);
	exit(2);
}

int	ft_exit(t_data *data, t_cmd *cmd, int stdin, int stdout)
{
	int	code;

	ft_printf("exit\n");
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (cmd->args[1] && !ft_isalldigit(cmd->args[1]))
		error_allnum(data, cmd, stdin, stdout);
	if (cmd->args[1])
		code = ft_atoi(cmd->args[1]);
	else
		code = 0;
	close(stdin);
	close(stdout);
	free_cmd_list(data);
	free_data(data);
	exit(code);
}
