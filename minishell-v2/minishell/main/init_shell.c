/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:37:26 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 08:00:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new_env;
	t_env	*prev_env;

	shell->env = NULL;
	shell->cmd = NULL;
	shell->pipex = NULL;
	shell->exit_status = 0;
	i = 0;
	while (envp[i])
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			exit(EXIT_FAILURE);
		new_env->var = ft_strdup(envp[i]);
		new_env->key = NULL;
		new_env->value = NULL;
		new_env->next = NULL;
		new_env->prev = NULL;
		if (!shell->env)
			shell->env = new_env;
		else
		{
			prev_env = shell->env;
			while (prev_env->next)
				prev_env = prev_env->next;
			prev_env->next = new_env;
			new_env->prev = prev_env;
		}
		i++;
	}
}

void	cleanup_shell(t_shell *shell)
{
	t_env	*tmp;
	t_env	*next;

	tmp = shell->env;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key != NULL)
			free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		if (tmp->var != NULL)
			free(tmp->var);
		free(tmp);
		tmp = next;
	}
	shell->env = NULL;
}
