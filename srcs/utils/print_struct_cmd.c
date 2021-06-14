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
		// printf("test\n");
		if (tmp->var_err)
		// {
			// printf("print_redir,  var_err\n");
			printf("bash: %s: ambiguous redirect\n", tmp->var_err);
		// }
		else
		{
			printf("fd = %d, file = |%s|, redir = ", tmp->fd, tmp->file);
			if (tmp->type == REDIR_IN)
				printf("<\n");
			if (tmp->type == REDIR_OUT)
				printf(">\n");
			if (tmp->type == APP_REDIR_OUT)
				printf(">>\n");
			if (tmp->type == HERE_DOC)
				printf("<<\n");
		}
		index = index->next;
	}
}

void	print_struct_cmd(t_list *param_lst)
{
	t_param_cmd	*param;
	t_list		*index;
	int			i;
	
	i = 1;
	index = param_lst;
	printf("\033[33m\033[1m--> STRUCTURE FOR COMMAND <--\n\033[0m");
	while (index != NULL)
	{
		param = index->content;
		if (param->cmd)
			print_cmd(param);
		if (param->redir)
			print_redir(param->redir);
		// if (param->pipe == 1)
		// 	printf("\033[1mPIPE:\n\033[0mYes\n");
		// else if (param->pipe == 0)
		// 	printf("\033[1mPIPE:\n\033[0mNo\n");
		if (i < ft_lstsize(param_lst))
			printf("\033[32m\033[1m--PIPE--\n\033[0m");
		else
			printf("\n");
		index = index->next;
		i++;
	}
}