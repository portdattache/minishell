/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:09:48 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/01 14:35:44 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	t_shell	shell;
	char	*line;
	char	**args;
	int		shell_init;

	shell_init = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		args = args_split(line);
		if (!args)
		{
			free(line);
			continue ;
		}
		if (!shell_init)
		{
			shell_init = 1;
			init_shell(&shell, args);
		}
		if (args[0] && is_builtin(args[0]))
			execute_builtin(args, &shell);
		else
			execute_pipex_from_minishell(&shell);
		ft_args_split_free(args);
		free(line);
	}
	ft_args_split_free(args);
	ft_free_pipeline(shell.pipex);
	cleanup_shell(&shell);
	rl_clear_history();
	return (0);
}
