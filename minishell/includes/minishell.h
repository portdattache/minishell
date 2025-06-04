/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:20:24 by garside           #+#    #+#             */
/*   Updated: 2025/06/04 15:18:18 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ========================== 🔹 DÉFINITIONS GÉNÉRALES =========================

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# define SUCCESS 0
# define FAIL 1
# define CODE_FAIL 1
# define CODE_SUCCESS 0
# define PIPE_READ 0
# define PIPE_WRITE 1
# define ERR_SYNT "minishell: syntax error near unexpected token"
# define PROMPT "\033[1;32mminishell$> \033[0m"

extern volatile sig_atomic_t	g_status;

// ======================== 🧠 STRUCTURES DE DONNÉES ===========================

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECTION_IN,
	REDIRECTION_OUT,
	HEREDOC,
	APPEND,
}								t_TokenType;

typedef struct s_token
{
	char						*value;
	t_TokenType					type;
	struct s_token				*next;
}								t_token;

typedef struct s_env
{
	char						*name;
	char						*content;
	struct s_env				*next;
	struct s_env				*prev;
}								t_env;

typedef struct s_redir
{
	char						*file;
	int							type;
	struct s_redir				*next;
}								t_redir;

typedef struct s_cmd
{
	char						**args;
	char						*path;
	t_redir						*infile;
	t_redir						*outfile;
	int							here_doc_mode;
	int							pipe_fd[2];
	int							saved_stdin;
	int							saved_stdout;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_data
{
	char						*input;
	t_env						*env;
	t_env						*export;
	char						**envp;
	t_token						*token;
	t_cmd						*cmd_list;
	int							last_status;
	int							token_count;
}								t_data;

// ======================== 🧠 INITIALISATION DES DONNÉES ======================

t_env							*init_export_list(char **env);
t_env							*init_env_list(char **env);
void							init_data(t_data *data);
t_token							*new_token(char *value, t_TokenType type);
t_cmd							*new_cmd_node(void);
void							add_redir(t_redir **redir_list, char *filename,
									int type);

// ======================= 🔧 SIGNALS & SHELL MGMT =============================

void							reset_signals_child(void);
void							handle_sigint(int sig);
void							init_signal(void);

// ============================ 🧩 LEXING ======================================

t_token							*ft_lexer(t_data *data);
t_token							*get_next_token(t_data *data, int *i);
t_env							*env_new(char *name, char *value);
char							*change_env(t_data *data, int *i);
char							*extract_word_double(t_data *data, int *i);
char							*extract_word_single(char *input, int *i);
int								check_quotes(char *input);
int								is_token_char(char c);
t_token							*handle_pipe(int *i);
t_token							*handle_cmd_or_arg(t_data *data, int *i);
t_token							*handle_double_redir(char *input, int *i);
t_token							*handle_redirection(char *input, int *i);
char							*handle_quotes(t_data *data, int *i);
char							*handle_env_value(t_data *data, int *i,
									char *value);
char							*handle_quotes_part(t_data *data, int *i,
									char *value);
char							*handle_plain_text(t_data *data, int *i,
									char *value);
char							*append_env_variable(t_data *data,
									char *extract, int *i, int *first);
char							*append_remaining_segment(t_data *data,
									char *extract, int first, int i);

// ============================ 🧪 PARSING =====================================

int								parse(t_data *data);
t_cmd							*parse_tokens(t_data *data);
void							add_arg(t_cmd *cmd, char *value);

void							add_token_to_list(t_token **head,
									t_token **last, t_token *new_token);

// ============================ 🛠️ EXECUTION ==================================

int								exec_line(t_data *data, t_cmd *cmd);
void							ft_restore_std(int input_fd, int output_fd);
void							handle_direct_exec(t_data *data, t_cmd *cmd);
void							handle_path_exec(t_data *data, t_cmd *cmd);
int								wait_for_children(pid_t last_pid);
void							maybe_close(t_cmd *cmd, int *prev_fd);
char							**ft_get_cmd(t_data *data);
int								resolve_command_path(t_data *data, t_cmd *cmd);
char							*get_cmd_path(t_data *data, char **cmd);
int								ft_shell(t_data *data, t_cmd *cmd, int prev_fd);
int								exec_child_process(t_data *data, t_cmd *cmd,
									int prev_fd);
int								which_command(t_data *data, t_cmd *cmd,
									int prev_fd);
int								handle_single_command(t_data *data, t_cmd *cmd,
									int prev_fd);
void							handle_useless_command(t_cmd *cmd,
									int *prev_fd);
void							exec_child(t_data *data, t_cmd *cmd,
									int prev_fd);
int								ft_executables(t_data *data, t_cmd *cmd,
									int input_fd, int output_fd);
int								ft_process(t_data *data, t_cmd *cmd,
									int prev_fd);
void							ft_execve_child(t_data *data, t_cmd *cmd,
									int input_fd, int output_fd);

// ============================ 📦 BUILTINS ====================================

bool							is_builtin(char *cmd);
int								run_builtin(t_data *data, t_cmd *cmd);
int								ft_pwd(void);
int								ft_cd(t_data *data);
int								ft_env(t_data *data);
int								ft_echo(t_data *data, t_cmd *cmd);
int								ft_export(t_data *data);
int								ft_unset(t_data *data);
int								ft_isalldigit(char *str);
void							sort(char **tmp);
char							*find_cmd_path(char *cmd, t_data *data);
int								ft_exit(t_data *data, t_cmd *cmd, int stdin,
									int stdout);

// ====================== 📁 REDIRECTIONS & FICHIERS ==========================

int								manag_infile(t_cmd *cmd, int prev_fd);
int								open_infile(char *str);
int								last_infile(t_cmd *cmd);
int								manag_outfile(t_cmd *cmd, int *pipe_fd);
int								open_outfile(char *file, t_TokenType mode);
int								last_outfile(t_cmd *cmd);
void							safe_close(int fd);
int								redirect_management(t_cmd *cmd, int prev_fd);

// ============================ 🐚 HERE-DOC ===================================

void							made_new_file(int *fd, char **name);
void							fill_here_doc_file(int fd, char *delimitor);
char							*get_here_doc(char *str);

// ============================ 📊 UTILITAIRES ================================

void							skip_whitespace(const char *input, int *i);
int								is_skippable_char(char c);
char							*ft_strjoin_three(char *s1, char *s2, char *s3);
char							*try_paths(char **paths, char *cmd);
void							ft_check_directory(t_data *data, t_cmd *cmd);
void							ft_lstadd_back_env(t_env **lst, t_env *new);
char							**translate_in_tab(t_data *data);
int								calcul_dynamique_len(t_env *tmp);
void							ft_lstadd_back_env(t_env **lst, t_env *new);
char							*check_direct_access(char *cmd);
char							*get_content(char *str, int i);
int								ft_is_valid(char *str);
void							ft_replace_in_env(t_data *data, char *name,
									char *value);
int								check_name(char *str, t_env *node,
									char *content);

// ============================= ⚠️ ERREURS ====================================

void							print_cmd_error(char *cmd);
void							is_a_directory(char *str);
void							no_such_file_or_directory(char *cmd);
void							command_not_found(char *cmd);
void							permission_denied(char *file);
void							error_message(char *str);
void							is_not_path(t_data *data);
char							*ft_get_env(char *str, t_data *data);
void							handle_invalid_command(t_data *data, t_cmd *cmd,
									int prev_fd);
char							*handle_error_code(t_data *data, char *value,
									int *i);
char							*append_error_code(t_data *data, char *extract,
									int *i, int *first);

// =========================== 🧹 FREE MEMORY & EXIT ===========================

void							free_env_list(t_env *new_list);
void							free_redir_list(t_redir *redir);
void							free_one_token(t_token *token);
void							free_token(t_token *head);
void							free_split(char **split);
void							free_name_content(char *name, char *content);
void							free_cmd_list(t_data *data);
void							free_data(t_data *data);
void							ft_exit_exec(int code, t_data *data,
									t_cmd *cmd);
void							ft_exit_with_error(t_data *data, t_cmd *cmd,
									char *msg, int code);

#endif