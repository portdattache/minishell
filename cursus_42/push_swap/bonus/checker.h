/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:34:16 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/28 15:09:56 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# define BUFFER_SIZE 4

# include "../push_swap.h"
# include "get_next_line/get_next_line.h"

typedef struct s_lst
{
	char			*str_buff;
	struct s_lst	*next;
}					t_lst;

char				*get_next_line_checker(int fd);
void				create_list(t_lst **list, int fd);
void				append(t_lst **list, char *buf);
char				*get_line(t_lst *list);
void				polish_list(t_lst **list);
void				dealloc(t_lst **list, t_lst *clean_node, char *buf);
int					len_to_newline(t_lst *list);
void				copy_str(t_lst *list, char *str);
t_lst				*dernier_noeud_2(t_lst *list);
int					main(int argc, char **argv);
int					found_newline(t_lst *list);

#endif