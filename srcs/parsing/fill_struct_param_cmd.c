/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_param_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:22:35 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/27 21:35:25 by tdayde           ###   ########lyon.fr   */
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
	{
		while (param->cmd[i])
		{
			new[i] = ft_strdup_no_list(param->cmd[i]);
			if (!new[i++])
				quit_prog("Fill_struct : command part malloc", main);
		}
	}
	new[i] = ft_strdup_no_list(lex->value);
	if (!new[i])
		quit_prog("Fill_struct : command part malloc", main);
	i++;
	new[i] = NULL;
	if (param->cmd)
	{
		i = -1;
		while (param->cmd[++i])
			free(param->cmd[i]);
		free(param->cmd);
	}
	param->cmd = new;
}

static void	update_redir_input(int i, t_param_cmd *param, t_main *main)
{
	t_list		*index;
	t_lexer		*tmp;
	
	i = 0;
	index = main->lexer;
	while (--i >= 0)
		index = index->next;
	tmp = index->content;
	param->redir_in.fd = ft_atoi(tmp->value);
	index = index->next;
	tmp = index->content;
	if (param->redir_in.file)
		free(param->redir_in.file);
	param->redir_in.file = ft_strdup_no_list(tmp->value);
	if (param->redir_in.file == NULL)
		quit_prog("Fill_struct : redir_in part malloc", main);
}

// static void	update_redir_output(t_lexer *lex, t_param_cmd *param, t_main *main)
// {
// 	t_redir	*new;
// 	int		i;
// 	int		j;
	
// 	param->n_cmd++;
// 	new = ft_calloc(1, sizeof(char*) * (param->n_cmd + 1));
// 	if (param->cmd == NULL)
// 		quit_prog("Fill_struct : command part malloc", main);
// 	i = -1;
// 	while (param->cmd[++i])
// 	{
// 		new[i] = ft_strdup_no_list(param->cmd[i]);
// 		if (!new[i])
// 			quit_prog("Fill_struct : command part malloc", main);
// 	}
// 	new[i] = ft_strdup_no_list(lex->value);
// 	if (!new[i])
// 		quit_prog("Fill_struct : command part malloc", main);
// 	i++;
// 	new[i] = NULL;
// 	i = 0;
// 	while (param->cmd[i])
// 		free(param->cmd[i++]);
// 	free(param->cmd);
// 	param->cmd = new;
// 	return (new);
// }

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
		if (tmp->type == REDIR_INPUT)
			update_redir_input(i, param, main);
		// if (tmp->type == APPEND_REDIR_OUTPUT || tmp->type == REDIR_OUTPUT)
		// 	update_redir_output(tmp, param, main);
		if (tmp->type == PIPE)
			param->pipe = 1;
		index = index->next;
	}
}
