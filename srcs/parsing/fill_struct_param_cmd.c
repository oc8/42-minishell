/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_param_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:22:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/28 15:00:05 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_command(t_lexer *lex, t_param_cmd *param, t_main *main)
{
	char	**new;
	int		i;
	
	i = 0;
	param->n_cmd++;
	new = malloc(sizeof(char*) * (param->n_cmd + 1));
	if (new == NULL)
		quit_prog("Fill_struct : command part malloc", main);
	if (param->cmd)
		while (param->cmd[i])
		{
			new[i] = ft_strdup_no_list(param->cmd[i]);
			if (!new[i++])
				quit_prog("Fill_struct : command part malloc", main);
		}
	new[i] = ft_strdup_no_list(lex->value);
	if (!new[i])
		quit_prog("Fill_struct : command part malloc", main);
	new[++i] = NULL;
	if (param->cmd)	// METTRE DOUBLESTR FREE !!!!!
	{
		i = -1;
		while (param->cmd[++i])
			free(param->cmd[i]);
		free(param->cmd);
		param->cmd = NULL;
	}
	param->cmd = new;
}

static void	update_redirs_lst(t_list *index, t_param_cmd *param, t_main *main)
{
	t_redir		*redir;
	t_list		*new;
	t_lexer		*lex;
	t_type_lex	type;
	
	redir = malloc(sizeof(t_redir));
	if (!redir)
		quit_prog("Fill_struct : redirection part malloc", main);
	lex = index->content;
	type = lex->type;
	redir->type = type;
	redir->fd = ft_atoi_redirection(lex->value, lex->type);
	index = index->next;
	lex = index->content;
	redir->file = ft_strdup_no_list(lex->value);
	// printf("\n\033[31m   lex->value = %s\n   \033[0m", lex->value);
	if (redir->file == NULL)
		quit_prog("Fill_struct : redirection part malloc", main);
	new = ft_lstnew(redir);
	ft_lstadd_back(&param->redir, new);
}

void	fill_struct(t_param_cmd *param, t_main *main)
{
	t_list		*index;
	t_lexer		*tmp;
	int			i;

	i = 0;
	index = main->lexer;
	while (index != NULL)
	{
		tmp = index->content;
		if (tmp->type == COMMAND || tmp->type == ARGUMENT)
			update_command(tmp, param, main);
		if (tmp->type == REDIR_INPUT || tmp->type == REDIR_OUTPUT
			|| tmp->type == APPEND_REDIR_OUTPUT)
			update_redirs_lst(index, param, main);
		if (tmp->type == PIPE)
			param->pipe = 1;
		index = index->next;
	}
}
