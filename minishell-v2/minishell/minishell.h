/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:47:10 by bcaumont          #+#    #+#             */
/*   Updated: 2025/04/02 07:58:37 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft.h"

# define PROMPT "\033[1;32mminishell$> \033[0m"

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*var;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_cmd
{
	char			**cmds;
	int				pipefd[2];
	t_env			*env;
	pid_t			pid;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipex
{
	char			**envp;
	char			**args;
	int				fd_in;
	int				fd_out;
	int				input;
	int				output;
	char			*infile;
	char			*outfile;
	int				pipefd[2];
	bool			is_first;
	bool			is_middle;
	bool			is_last;
	bool			is_here_doc;
	pid_t			pid;
	t_cmd			*cmd;
	struct s_pipex	*prev;
	struct s_pipex	*next;
}					t_pipex;

typedef struct s_shell
{
	char			*input_terminal;
	t_env			*env;
	t_cmd			*cmd;
	t_pipex			*pipex;
	int				exit_status;
}					t_shell;

/* Redirection */
void				execute_pipex_from_minishell(t_shell *shell);

int					ft_echo(char **args);
int					ft_cd(char **args, t_shell *shell);
int					ft_pwd(void);
int					ft_exit(char **args, t_shell *shell);
int					ft_env(t_shell *shell);
void				add_or_update_env(t_shell *shell, char *key, char *value);
void				remove_env(t_shell *shell, char *key);
int					execute_builtin(char **args, t_shell *shell);
int					ft_export(char **args, t_shell *shell);
int					ft_unset(char **args, t_shell *shell);
int					is_builtin(char *cmd);
void				cleanup_shell(t_shell *shell);
void				init_shell(t_shell *shell, char **envp);
void				shell_node(t_shell *shell);

// /* Initialisation de la struct */
t_pipex				*init_minishell_pipeline(t_cmd *cmd_list, t_shell *shell);
t_pipex				*create_pipe_node(t_cmd *cmd, t_shell *shell);
void				set_first_or_last(t_pipex *head);
void				init_env_list(t_shell *shell, char **envp);
void				init_env_list2(t_shell *shell);
// void				pipe_execution(t_pipex *pipex);
// t_pipex				*add_pipex_node(t_data *data);

// /* Gestion des erreurs & free */
void				ft_free_pipeline(t_pipex *pipeline);
void				error_and_exit(t_pipex *node, char *msg);
void				cleanup(t_pipex *node);
void				cleanup_head(t_pipex *head);
// void				cleanup_here_doc(t_pipex *node);
void				ft_perror(char *msg);

// /* Verifs, secures & utils */
void				secure_close(int fd);
int					secure_open(char *filename, int flags);
void				secure_dup2(int old_fd, int new_fd);
void				secure_dup(t_pipex *current);
pid_t				secure_fork(void);
int					file_is_executable(char *file);

// /* Gestion des pipes & des forks */
void				do_pipe(t_pipex *node);
void				process_pipeline(t_pipex *head);
void				close_pipes(t_pipex *node);

// /* Executeur */
void				exec(t_pipex *node);
void				exec_redirection(t_pipex *node);
void				here_doc_redirection(t_pipex *node);
void				here_doc_outfile(t_pipex *node);
void				last_node_redirection(t_pipex *node);
void				exec_redirection_first(t_pipex *node);

// /* Here_doc*/
// void				here_doc(t_pipex *node);
// void				here_doc_put_in(t_pipex *node, int tmp_fd);

/* Gestion des PATHS */
char				*get_envp(char *name, t_pipex *node);
char				*get_path(t_pipex *node);
char				*search_in_path(t_pipex *node, char **all_path);
char				*check_current_directory(t_pipex *node);
char				*check_absolute_path(t_pipex *node);
char				**convert_env_to_array(t_env *env);
int					env_list_size(t_env *env);

#endif
