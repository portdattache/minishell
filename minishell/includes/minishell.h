#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h> /* Pour open, fcntl (si set_fd_cloexec est utilisé) */
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h> /* Pour bool, si autorisé et utilisé. Sinon, int. */
# include <stdio.h>   /* Pour printf, perror (si utilisées directement) */
# include <stdlib.h>  /* Pour malloc, free, exit */
# include <string.h>  /* Pour strerror (si utilisé avec perror) */
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* Assurez-vous que le chemin vers votre libft est correct */
# include "../octolib/includes/libft.h"

/* Valeurs de retour standard pour les fonctions */
# define SUCCESS 0
# define FAIL 1

/* Codes de sortie spécifiques (peuvent être identiques à SUCCESS/FAIL) */
# define CODE_FAIL 1
# define CODE_SUCCESS 0

/* Valeur spéciale pour ft_process en cas d'erreur avant fork */
# define PID_ERROR_PRE_FORK -1

/* Variable globale pour le statut de la dernière commande (pour les signaux) */
extern volatile sig_atomic_t	g_status;

/* Énumération pour les types de tokens */
typedef enum e_token_type
{
	WORD,            /* Mot simple, argument, nom de commande */
	PIPE,            /* | */
	REDIRECTION_IN,  /* < */
	REDIRECTION_OUT, /* > */
	HEREDOC,         /* << */
	APPEND           /* >> */
}								t_TokenType;

/* Structure pour un token lexical */
typedef struct s_token
{
	char						*value;
	t_TokenType					type;
	struct s_token				*next;
}								t_token;

/* Structure pour une variable d'environnement */
typedef struct s_env
{
	char						*name;
	char						*content;
	struct s_env				*next;
	struct s_env *prev; /* Pour la suppression dans unset, si bidirectionnel */
}								t_env;

/* Structure pour une redirection */
typedef struct s_redir
{
	char *file; /* Nom du fichier de redirection */
	int type;   /* Type de redirection (REDIRECTION_IN, etc.) */
	struct s_redir				*next;
}								t_redir;

/* Structure pour une commande (simple ou maillon d'un pipeline) */
typedef struct s_cmd
{
	char **args;       /* Tableau d'arguments (argv style) */
	char *path;        /* Chemin complet de la commande si externe */
	t_redir *infile;   /* Liste des redirections d'entrée */
	t_redir *outfile;  /* Liste des redirections de sortie */
	int here_doc_mode; /* Indicateur pour here-document (si nécessaire) */
	int							pipe_fd[2];
	/* Descripteurs pour le pipe (si partie d'un pipeline) */
	struct s_cmd *next; /* Commande suivante dans le pipeline */
}								t_cmd;

/* Structure principale contenant les données du minishell */
typedef struct s_data
{
	char *input;     /* Ligne de commande lue */
	t_env *env;      /* Liste chaînée de l'environnement */
	t_env *export;   /* Liste pour la commande export (peut différer de env) */
	char **envp;     /* Tableau de l'environnement pour execve */
	t_token *token;  /* Liste chaînée des tokens */
	t_cmd *cmd_list; /* Liste chaînée des commandes parsées */
	int token_count; /* Nombre de tokens (si utile) */
	int last_status; /* Code de sortie de la dernière commande exécutée */
}								t_data;

/*
 * Prototypes de fonctions
 */

/* gestion_signaux.c */
void							init_signal(void);
void							reset_signals_child(void);

/* parsing/ft_parse.c & ft_parse_util.c */
int	parse(t_data *data); /* Fonction principale du parsing */
t_cmd							*parse_tokens(t_data *data);
/* Transforme les tokens en liste de commandes */
t_cmd							*new_cmd_node(void);
void							add_arg(t_cmd *cmd, char *value);
void							add_redir(t_redir **redir_list, char *filename,
									int type);
void							free_cmd_list(t_data *data);
void							free_redir_list(t_redir *redir);
/* Fonctions de débogage (peuvent être retirées pour la soumission finale) */
void							print_cmds(t_cmd *cmd);
void							print_tokens(t_data *data);
/* Déplacé de ft_parse.c pour regroupement */

/* parsing/ft_lexer.c & ft_lexer_utils_*.c */
t_token							*ft_lexer(t_data *data);
t_token							*get_next_token(t_data *data, int *i);
/* Déclarée dans ft_parse.c originalement */
t_token							*handle_cmd_or_arg(t_data *data, int *i);
t_token							*handle_double_redir(char *input, int *i);
t_token							*handle_redirection(char *input, int *i);
t_token							*handle_pipe(int *i);
/* Déclarée dans ft_lexer_utils_2.c originalement */
void							skip_whitespace(const char *input, int *i);
/* Utils 1 */
void							free_one_token(t_token *token);
void							free_token(t_token *head);
t_token							*new_token(char *value, t_TokenType type);
char							*handle_error_code(t_data *data, char *value,
									int *i);
void							add_token_to_list(t_token **head,
									t_token **last, t_token *new_token);
/* Utils 2 */
int								is_skippable_char(char c);
int								is_token_char(char c);
char							*handle_env_value(t_data *data, int *i,
									char *value);
char							*handle_plain_text(t_data *data, int *i,
									char *value);

/* parsing/ft_quote.c & ft_quote_utils_*.c */
char							*handle_quotes(t_data *data, int *i);
char							*extract_word_double(t_data *data, int *i);
char							*extract_word_single(char *input, int *i);
char							*append_env_variable(t_data *data,
									char *extract, int *i, int *first);
char							*append_remaining_segment(t_data *data,
									char *extract, int first, int i);
/* Utils 1 (quote) */
int								check_quotes(char *input);
char							*ft_get_env(char *str, t_data *data);
/* Utilisée par plusieurs modules */
char	*change_env(t_data *data, int *i); /* Utilisée par lexer et quotes */
char							*append_error_code(t_data *data, char *extract,
									int *i, int *first);

/* execution/ft_exec.c & ft_exec_utils_*.c */
int								exec_line(t_data *data, t_cmd *cmd);
int								ft_shell(t_data *data);
/* Exécute une commande externe simple */
void							exec_child_process(t_data *data);
/* Logique enfant pour ft_shell */
char	*get_cmd_path(t_data *data, char **cmd); /* Pour ft_shell */
int								set_fd_cloexec(int fd);
/* Utiliaire pour les descripteurs de fichiers */
/* Utils 1 (exec) */
void							free_data(t_data *data);
/* Libère les structures principales de t_data */
char	**ft_get_cmd(t_data *data); /* Pour ft_shell et ft_executables */
void							ft_replace_in_env(t_data *data, char *name,
									char *value);

/* execution/ft_pipe.c & ft_pipe_utils.c */
int								ft_process(t_data *data, t_cmd *cmd,
									int prev_fd);
void							exec_child(t_data *data, t_cmd *cmd,
									int prev_fd);
void							ft_exit_exec(int code, t_data *data,
									t_cmd *cmd);
bool							is_builtin(char *cmd_name);
int								run_builtin(t_data *data, t_cmd *cmd);
int								redirect_management(t_cmd *cmd, int prev_fd);
void							safe_close(int fd);
/* Utils (pipe) */
int								open_infile(char *str);
int								last_infile(t_cmd *cmd);
int								manag_infile(t_cmd *cmd, int prev_fd);
int								open_outfile(char *file, t_TokenType mode);
int								last_outfile(t_cmd *cmd);
int								manag_outfile(t_cmd *cmd, int *pipe_fd);

/* execution/ft_pipe_error.c (messages d'erreur) */
void							command_not_found(char *cmd);
void							no_such_file_or_directory(char *cmd);
void							permission_denied(char *file);
void	error_message(char *str); /* Wrapper pour perror ou ft_putstr_fd */
void							is_a_directory(char *str);

/* builtins/ */
int								ft_cd(t_data *data);
int								ft_echo(t_data *data);
int								ft_env(t_data *data);
int								ft_exit(t_data *data);
int								ft_export(t_data *data);
int								ft_pwd(void);
int								ft_unset(t_data *data);
/* Utils pour builtins (peuvent être statiques ou ici si partagés) */
int	ft_isalldigit(char *str); /* Utilisé par ft_exit */
int								ft_is_valid(char *str);
/* Utilisé par ft_export et ft_unset (pour la validation du nom) */
char	*get_content(char *str, int i);                   /* Pour ft_export */
int	check_name(char *str, t_env *node, char *content); /* Pour ft_export */
void	free_name_content(char *name, char *content);     /* Pour ft_export */

/* env_management.c (ou similaire, pour la gestion de t_env) */
t_env							*env_new(char *name, char *value);
/* Déclarée dans ft_parse.c originalement */
void							ft_lstadd_back_env(t_env **lst, t_env *new);
void							free_env_list(t_env *env_list);
t_env	*init_env_list(char **env);      /* Pour initialiser data->env */
t_env	*init_export_list(char **env);   /* Pour initialiser data->export */
char	**translate_in_tab(t_data *data); /* Pour mettre à jour data->envp */
void	sort(char **tmp);                 /* Utilisé par init_export_list */

/* utils_general.c (fonctions utilitaires générales non-libft) */
char							*find_cmd_path(char *cmd, t_data *data);
/* Recherche de chemin (déplacé ici pour regroupement) */
void							free_split(char **tmp);
/* Si pas dans libft ou comportement spécifique */
int	ft_executables(t_data *data); /* Exécution de ./cmd ou
/path/to/cmd */
/* La fonction `which_command` de ft_exec.c est un dispatcher interne,
   elle n'a pas besoin d'être dans le .h si elle est statique ou
   appelée uniquement depuis ft_exec.c. Si elle est globale, la déclarer.
   Pour l'instant, je la considère comme interne à la logique d'exécution. */
/* int		which_command(t_data *data, t_cmd *cmd); */

#endif

// ```

// **Changements et clarifications apportés au `.h` :**

// 1.  **`PID_ERROR_PRE_FORK`** : Ajouté.
// 2.  **Includes** : J'ai ajouté des includes standards (`fcntl.h`, `stdio.h`,
// 	`stdlib.h`,
// 	`string.h`) qui sont souvent nécessaires pour les opérations effectuées. Vous devrez vérifier si ceux-ci sont autorisés par la norminette de votre école ou si vous devez utiliser des équivalents de votre `libft`. `stdbool.h` est inclus pour `bool`,
// 	si vous l'utilisez.
// 3.  **Organisation des Prototypes** : J'ai tenté de regrouper les prototypes de manière plus logique par fonctionnalité ou par fichier d'origine (par exemple,
// 	`parsing/`, `execution/`, `builtins/`,
// 	`env_management/`). Cela peut aider à la navigation. Les commentaires originaux comme `//ryew` ont été retirés ou remplacés par des groupements plus descriptifs.
// 4.  **Doublons de Prototypes** : J'ai vérifié qu'il n'y a pas de prototypes en double.
// 5.  **Visibilité des Fonctions** : Les fonctions qui sont purement internes à un fichier `.c` (et donc déclarées `static` dans ce fichier) ne doivent pas apparaître dans le `.h`. J'ai gardé les fonctions qui semblaient faire partie de l'API publique entre les modules. Par exemple,
// 	`which_command` de `ft_exec.c` est probablement interne à la logique d'exécution et n'a pas besoin d'être dans le `.h` si elle n'est pas appelée depuis d'autres fichiers.
// 6.  **Commentaires** : Tous les commentaires sont en style C. J'ai ajouté des commentaires descriptifs pour les sections et certaines structures/énumérations.

// Assurez-vous que ce fichier d'en-tête correspond bien à la manière dont vos fichiers `.c` s'appellent et s'incluent mutuellement. La structure d'un projet Minishell peut varier,
// 	donc ajustez les groupements si nécessaire pour qu'ils reflètent votre organisati