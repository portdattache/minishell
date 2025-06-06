/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:20:10 by garside           #+#    #+#             */
/*   Updated: 2025/06/06 15:46:41 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_status = 0;

void	sort(char **tmp)
{
	char	*swap;
	int		i;
	int		j;

	j = 0;
	while (tmp[j])
	{
		i = 1;
		while (tmp[i])
		{
			if (ft_strcmp(tmp[i - 1], tmp[i]) > 0)
			{
				swap = tmp[i - 1];
				tmp[i - 1] = tmp[i];
				tmp[i] = swap;
			}
			i++;
		}
		j++;
	}
}

void	read_prompt(t_data *data)
{
	while (1)
	{
		data->token = NULL;
		data->cmd_list = NULL;
		data->input = readline(PROMPT);
		if (!data->input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (data->input[0] && !check_quotes(data->input))
		{
			add_history(data->input);
			if (parse(data) == 0)
			{
				data->last_status = exec_line(data, data->cmd_list);
			}
			if (data->cmd_list)
				free_cmd_list(data);
			if (data->token)
				free_token(data->token);
		}
		free(data->input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data);
	data.envp = env;
	data.env = init_env_list(env);
	data.export = init_export_list(env);
	init_signal();
	read_prompt(&data);
	free_env_list(data.env);
	free_env_list(data.export);
	rl_clear_history();
	return (g_status);
}
