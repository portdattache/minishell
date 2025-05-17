/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:11:06 by garside           #+#    #+#             */
/*   Updated: 2025/05/17 16:55:01 by broboeuf         ###   ########.fr       */
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
// verif "trop d'args" etait fausse !cmd->args[1] au lieu de cmd->args[2]
// fix : check cmd->args[2]
// comportement aligné sur bash quit avec statut ou affiche erreur
int	ft_exit(t_data *data)
{
	t_cmd	*cmd;
	int		code;

	cmd = data->cmd_list;
	ft_printf("exit\n");
	if (!cmd->args[1])
	{
		code = data->last_status;
		free_cmd_list(data);
		free_data(data);
		exit(code);
	}
	if (ft_isalldigit(cmd->args[1]))
	{
		if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		code = ft_atoi(cmd->args[1]);
		free_cmd_list(data);
		free_data(data);
		exit(code % 256);
	}
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_cmd_list(data);
	free_data(data);
	exit(255);
}
