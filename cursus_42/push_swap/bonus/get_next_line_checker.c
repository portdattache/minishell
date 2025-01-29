/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_checker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:47:40 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/28 17:06:05 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/* Va recuperer les donnees apres '\n' et creer un
 *  nouveau noeud a partir de ces donnees
 */
void	polish_list(t_lst **lst)
{
	t_lst	*last_node;
	t_lst	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_lst));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = dernier_noeud_2(*lst);
	i = 0;
	k = 0;
	while (last_node->str_buff[i] && last_node->str_buff[i] != '\n')
		i++;
	while (last_node->str_buff[i] && last_node->str_buff[++i])
		buf[k++] = last_node->str_buff[i];
	buf[k] = '\0';
	clean_node->str_buff = buf;
	clean_node->next = NULL;
	dealloc(lst, clean_node, buf);
}

/* Mesure et copie la nouvelle ligne */
char	*get_line(t_lst *lst)
{
	int		str_len;
	char	*next_str;

	if (lst == NULL)
		return (NULL);
	str_len = len_to_newline(lst);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(lst, next_str);
	return (next_str);
}

/* Ajoute un nouveau noeud a la fin de la liste */
void	append(t_lst **lst, char *buf)
{
	t_lst	*new_node;
	t_lst	*last_node;

	last_node = dernier_noeud_2(*lst);
	new_node = malloc(sizeof(t_lst));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->str_buff = buf;
	new_node->next = NULL;
}

/* Va creer une liste sous forme de noeuds a partir du fd
 *  jusqu'au prochain '\n'
 */
void	create_list(t_lst **lst, int fd)
{
	ssize_t	char_read;
	char	*buf;

	while (!found_newline(*lst))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(lst, buf);
	}
}

/* Va lire la la ligne ou le fd et se servir d'une liste
 *  statique pour garder en memoire les residus de donnees
 *  entre chaque appel a la fonction et creer les noeuds
 *  qui constiturons la liste definitive
 */
char	*get_next_line_checker(int fd)
{
	static t_lst	*lst = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&lst, fd);
	if (lst == NULL)
		return (NULL);
	next_line = get_line(lst);
	polish_list(&lst);
	return (next_line);
}
