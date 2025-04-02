/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:09:48 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 09:00:56 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	main_cleaner(char **args, t_shell *shell)
{
	ft_args_split_free(args);
	ft_free_pipeline(shell->pipex);
	cleanup_shell(shell);
	rl_clear_history();
}

static void	exec_direction(char **args, t_shell *shell, char *line)
{
	if (args[0] && is_builtin(args[0]))
		execute_builtin(args, shell);
	else
		execute_pipex_from_minishell(shell);
	ft_args_split_free(args);
	free(line);
}

static void	initialize_minishell(t_shell *shell, char **args, int *shell_init)
{
	if (!*shell_init)
	{
		*shell_init = 1;
		init_shell(shell, args);
	}
}

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
		initialize_minishell(&shell, args, &shell_init);
		exec_direction(args, &shell, line);
	}
	main_cleaner(args, &shell);
	return (0);
}
