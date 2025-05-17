/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:41:37 by garside           #+#    #+#             */
/*   Updated: 2025/05/17 16:56:01 by broboeuf         ###   ########.fr       */
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

// memoire libere plusieurs fois ou au mauvais endroit
// correction try_path ne libere plus paths cest find_cmd_path qui le fait
char	*try_paths(char **paths, char *cmd)
{
	int		i;
	char	*res;
	char	*resfinal;

	i = 0;
	if (!paths || !cmd)
		return (NULL);
	while (paths[i])
	{
		res = ft_strjoin(paths[i], "/");
		if (!res)
			return (NULL);
		resfinal = ft_strjoin(res, cmd);
		free(res);
		if (!resfinal)
			return (NULL);
		if (access(resfinal, X_OK) != -1)
			return (resfinal);
		free(resfinal);
		i++;
	}
	return (NULL);
}
// utilisait try_paths pour free paths le char **ce qui causait des bugs.la gestion des chemins absolus relatifs etait pas top
// free paths le char** apres l'appel a try_paths gere les chemins qui commencent par '/' ou '.' et duplique la chaine pour eviter les probs de memoire
char	*find_cmd_path(char *cmd, t_data *data)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	if (!cmd || !data)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || (cmd[1] == '.'
					&& cmd[2] == '/'))))
	{
		if (access(cmd, X_OK) != -1)
			return (ft_strdup(cmd));
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
	free_split(paths);
	return (cmd_path);
}
