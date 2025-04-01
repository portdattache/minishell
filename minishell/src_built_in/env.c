/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:00:07 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/22 11:34:55 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

void	add_or_update_env(t_shell *shell, char *key, char *value)
{
	t_env	*env;
	t_env	*new;

	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->var = ft_strjoin_three(new->key, "=", new->value);
	new->next = shell->env;
	shell->env = new;
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
