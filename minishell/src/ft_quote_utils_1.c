/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:35:05 by garside           #+#    #+#             */
/*   Updated: 2025/05/17 16:49:22 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*handle_var_expansion(t_data *data, char *name)
{
	char	*value;

	value = ft_get_env(name, data);
	free(name);
	if (!value)
		return (ft_strdup("")); /* Variable non trouvée, retourne "" */
	return (value);
	/* ft_get_env doit retourner une copie allouée */
}

// retournait NULL pour les vars non definies ce qui causait des crashs avec ft_strjoin
// gestion des cas $ pas suivi d'un nom de var ok (genre $ $= $$) fallait ajuster *i
// fix : retourne ft_strdup("") si var pas trouvee
// si $ pas suivi d'un nom de var alphanum (ou _) ou ?,
// decremente *i et retourne ft_strdup("$")
char	*change_env(t_data *data, int *i)
{
	int		first;
	char	*name;

	(*i)++; /* Avance au caractère après '$' */
	first = *i;
	/* Le cas '$?' est normalement géré avant d'appeler change_env,
		par ex. dans handle_env_value. Si ce n'est pas le cas,
		il faudrait l'ajouter ici. Pour cet exemple,
			on suppose qu'il est géré avant.
		if (data->input[*i] == '?') { ... } */
	if (!ft_isalpha(data->input[*i]) && data->input[*i] != '_')
	{
		(*i)--; /* Revenir sur le '$' pour traitement littéral */
		return (ft_strdup("$"));
	}
	/* Boucle pour extraire le nom de la variable */
	while (ft_isalnum(data->input[*i]) || data->input[*i] == '_')
		(*i)++;
	/* 'last' serait *i ici */
	name = ft_substr(data->input, first, (*i) - first);
	if (!name)
		return (ft_strdup("")); /* Erreur d'allocation, retourne "" */
	/* Si le nom extrait est vide (ex: "$ suivi d'un espace"),
		traiter $ littéralement */
	if (ft_strlen(name) == 0)
	{
		free(name);
		(*i) = first - 1; /* Revenir sur le '$' */
		return (ft_strdup("$"));
	}
	return (handle_var_expansion(data, name));
}

int	check_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && (input[i] != '\''))
				i++;
			if (!input[i])
				return (ft_putstr_fd("quote error\n", 2), 1);
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] && (input[i] != '\"'))
				i++;
			if (!input[i])
				return (ft_putstr_fd("quote error\n", 2), 1);
		}
		i++;
	}
	return (0);
}

char	*ft_get_env(char *str, t_data *data)
{
	t_env	*current;
	char	*value;
	int		len;

	current = data->env;
	len = ft_strlen(str);
	while (current)
	{
		if (ft_strcmp(str, current->name) == 0)
		{
			value = ft_strdup(current->content);
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}

char	*append_error_code(t_data *data, char *extract, int *i, int *first)
{
	int		last;
	char	*tmp;
	char	*temp;

	last = *i;
	tmp = ft_substr(data->input, *first + 1, last - *first - 1);
	temp = ft_strjoin(extract, tmp);
	free(tmp);
	free(extract);
	extract = handle_error_code(data, temp, i);
	*first = *i - 1;
	return (extract);
}
