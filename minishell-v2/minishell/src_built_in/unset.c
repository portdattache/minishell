/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:16:20 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 07:47:39 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (!args[i])
	{
		write(2, "unset: missing argument\n", 24);
		return (1);
	}
	while (args[i])
	{
		remove_env(shell, args[i]);
		i++;
	}
	return (0);
}

void	remove_env(t_shell *shell, char *key)
{
	t_env	*env;
	t_env	*prev;

	env = shell->env;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				shell->env = env->next;
			free(env->key);
			free(env->value);
			free(env->var);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}
