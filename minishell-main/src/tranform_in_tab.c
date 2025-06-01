/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tranform_in_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:12:28 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/01 21:41:28 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../octolib/includes/libft.h"

int	calcul_dynamique_len(t_env *tmp)
{
	int	len_name;
	int	len_content;

	len_name = ft_strlen(tmp->name);
	len_content = ft_strlen(tmp->content);
	return (len_name + len_content + 2);
}

int	size_list(t_env *tmp)
{
	int	count;

	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	**alloc_envp_array(t_env *env)
{
	int		size;
	char	**envp;

	size = size_list(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
	{
		g_status = 1;
		ft_putstr_fd("Error\n:allocation fail\n", 2);
		return (NULL);
	}
	return (envp);
}

static int	fill_envp_array(t_env *env, char **envp)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	while (env)
	{
		len = calcul_dynamique_len(env);
		line = malloc(len);
		if (!line)
		{
			free_split(envp);
			return (0);
		}
		ft_strlcpy(line, env->name, len);
		ft_strlcat(line, "=", len);
		ft_strlcat(line, env->content, len);
		envp[i++] = line;
		env = env->next;
	}
	envp[i] = NULL;
	return (1);
}

char	**translate_in_tab(t_data *data)
{
	char	**envp;

	envp = alloc_envp_array(data->env);
	if (!envp)
		return (NULL);
	if (!fill_envp_array(data->env, envp))
		return (NULL);
	return (envp);
}
