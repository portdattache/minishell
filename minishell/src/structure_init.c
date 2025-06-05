/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:07:49 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/04 22:34:35 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env_list(char **env)
{
	t_env	*env_list;
	t_env	*new_env;
	char	*sep;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		sep = ft_strchr(env[i], '=');
		if (sep)
		{
			*sep = '\0';
			new_env = env_new(env[i], sep + 1);
			*sep = '=';
			if (!new_env)
			{
				i++;
				continue ;
			}
			ft_lstadd_back_env(&env_list, new_env);
		}
		i++;
	}
	return (env_list);
}

t_env	*init_export_list(char **env)
{
	t_env	*export;
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		tmp[i] = ft_strdup(env[i]);
	tmp[i] = NULL;
	sort(tmp);
	export = init_env_list(tmp);
	free_split(tmp);
	return (export);
}

void	init_data(t_data *data)
{
	data->input = NULL;
	data->env = NULL;
	data->export = NULL;
	data->envp = NULL;
	data->token = NULL;
	data->cmd_list = NULL;
	data->token_count = 0;
	data->last_status = 0;
}

t_cmd	*new_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->saved_stdin = -1;
	cmd->saved_stdout = -1;
	return (cmd);
}

t_token	*new_token(char *value, t_TokenType type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}
