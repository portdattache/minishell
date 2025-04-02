/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:00:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 07:47:14 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(char **args, t_shell *shell)
{
	int		i;
	char	*equal;

	i = 1;
	if (!args[i])
		return (ft_env(shell));
	while (args[i])
	{
		equal = ft_strchr(args[i], '=');
		if (equal)
		{
			*equal = '\0';
			add_or_update_env(shell, args[i], equal + 1);
			*equal = '=';
		}
		i++;
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
		if (env->key && ft_strcmp(env->key, key) == 0)
		{
			free(env->var);
			free(env->value);
			env->value = ft_strdup(value);
			env->var = ft_strjoin_three(env->key, "=", env->value);
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
