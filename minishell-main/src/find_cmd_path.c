/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:41:37 by garside           #+#    #+#             */
/*   Updated: 2025/05/23 11:33:39 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **tmp)
{
	int	i;

	i = 0;
	if (tmp)
	{
		while (tmp[i])
		{
			free(tmp[i]);
			i++;
		}
		free(tmp);
	}
}

char	*try_paths(char **paths, char *cmd)
{
	int		i;
	char	*resfinal;

	i = 0;
	while (paths[i])
	{
		resfinal = ft_strjoin_three(paths[i], "/", cmd);
		if (!resfinal)
		{
			free_split(paths);
			return (NULL);
		}
		if (access(resfinal, X_OK) != -1)
		{
			free_split(paths);
			return (resfinal);
		}
		free(resfinal);
		i++;
	}
	free_split(paths);
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_data *data)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) != -1)
			return (cmd);
		else
			return (NULL);
	}
	path_env = ft_get_env("PATH", data);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	cmd_path = try_paths(paths, cmd);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}
