#include "minishell.h"

void	update_lst(t_utils_var *utils, t_main *main)
{
	utils->new = NULL;
	utils->save = utils->index->next;
	utils->tmp3 = utils->index->content;
	utils->str_with_var = ft_strdup_no_list(utils->tmp3->value);
	if (!utils->str_with_var)
		quit_prog("strdup of update_lst create_param_cmd", main);
	free_lexer(utils->index->content);
	free(utils->index);
	if (utils->previous == NULL)
		main->lexer = NULL;
	else
		utils->previous->next = NULL;
	remplace_var_value(&utils->new, utils->str_with_var, main);
	if (utils->new)
		tokenization(utils->new, 0, main);
	utils->last = ft_lstlast(main->lexer);
	if (utils->last)
		utils->last->next = utils->save;
	else
		main->lexer = utils->save;
	free(utils->new);
	free(utils->str_with_var);
}

void	contain_var(t_main *main)
{
	t_utils_var	util;

	ft_bzero(&util, sizeof(t_utils_var));
	util.index = main->lexer;
	util.previous = NULL;
	while (util.index != NULL)
	{
		util.tmp = util.index->content;
		if (util.tmp->type == VAR_ENV)
		{
			if (util.previous)
			{
				util.tmp2 = util.previous->content;
				if ((util.tmp2->type == REDIR_IN || util.tmp2->type == REDIR_OUT
						|| util.tmp2->type == APP_REDIR_OUT)
					&& verif_redir_var(util.tmp, util.previous, main) == -1)
					return ;
			}
			update_lst(&util, main);
			contain_var(main);
			return ;
		}
		util.previous = util.index;
		util.index = util.index->next;
	}
}

void	create_param_cmd(t_list **param_lst, t_main *main)
{	
	t_param_cmd	*param;
	t_list		*save;
	t_list		*new;

	save = main->lexer;
	while (main->lexer != NULL)
	{
		update_main_lexer(PIPE, &save);
		contain_var(main);
		define_text_types(main);
		param = ft_calloc(1, sizeof(t_param_cmd));
		if (!param)
			quit_prog("Malloc param struct in create_param_cmd", main);
		fill_struct(param, main);
		new = ft_calloc(1, sizeof(t_list));
		if (!new)
			quit_prog("Malloc new_element of lst in create_param_cmd", main);
		new->content = param;
		ft_lstadd_back(param_lst, new);
		ft_lstclear(&main->lexer, free_lexer);
		main->lexer = save;
	}
	print_struct_cmd(*param_lst);
}
