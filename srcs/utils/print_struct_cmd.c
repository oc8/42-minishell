/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 20:52:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/28 15:04:53 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmd(t_param_cmd *param)
{
	int i;
	
	i = 0;
	printf("\033[1mCOMMAND:\n\033[0m");
	printf("|%s|\n", param->cmd[i]);
	printf("\033[1mARGUMENTS:\n\033[0m");
	while (param->cmd[++i])
	{
		if (param->cmd[i + 1])
			printf("|%s|, ", param->cmd[i]);
		else
			printf("|%s|\n", param->cmd[i]);
	}
}

static void print_redir(t_list *redir)
{
	t_list	*index;
	t_redir *tmp;

	printf("\033[1mREDIRECTION:\n\033[0m");
	index = redir;
	while (index != NULL)
	{
		tmp = index->content;
		printf("fd = %d, file = |%s|, redir = ", tmp->fd, tmp->file);
		if (tmp->type == REDIR_INPUT)
			printf("<\n");
		if (tmp->type == REDIR_OUTPUT)
			printf(">\n");
		if (tmp->type == APPEND_REDIR_OUTPUT)
			printf(">>\n");
		index = index->next;
	}
}

void	print_struct_cmd(t_param_cmd *param)
{
	int	i;
	
	i = 0;
	printf("\033[33m\033[1m--> STRUCTURE FOR COMMAND <--\n\033[0m");
	if (param->cmd)
		print_cmd(param);
	if (param->redirection)
		print_redir(param->redirection);
	if (param->pipe == 1)
		printf("\033[1mPIPE:\n\033[0mYes\n");
	else if (param->pipe == 0)
		printf("\033[1mPIPE:\n\033[0mNo\n");
	printf("\n");
}