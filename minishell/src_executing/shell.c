/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:06:27 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/26 18:16:33 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*input;
	t_cmd	*cmd;

	while (true)
	{
		input = read_input();
		if (!input)
			break ;
		if (is_empty_input(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		cmd = parse_input(input, shell);
		free(input);
		if (cmd)
		{
			execute_command(cmd, shell);
			free_command(cmd);
		}
	}
}

char	*read_input(void)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
		ft_putendl_fd("exit", STDOUT_FILENO);
	return (input);
}
