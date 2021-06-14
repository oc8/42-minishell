#include "minishell.h"

void	update_lst(t_list *previous, t_list *to_del, t_main *main)
{
	char	*str_with_var;
	char	*new;
	t_lexer	*tmp;
	t_list	*save;
	t_list	*last;
	
	new = NULL;
	save = to_del->next;
	tmp = to_del->content;
	str_with_var = ft_strdup_no_list(tmp->value);
	// printf("tmp->value = %s, str_with_var = %s\n", tmp->value, str_with_var);
	if (!str_with_var)
		quit_prog("strdup of update_lst create_param_cmd", main);
	free_lexer(to_del->content);
	free(to_del);
	if (previous == NULL)
		main->lexer = NULL;
	else
		previous->next = NULL;
	// printf("str_with_value = %s\n", str_with_var);
	remplace_var_value(&new, str_with_var, main);
	// printf("str_with_var = %s, new = %s\n", str_with_var, new);
	if (new)
		tokenization(new, 0, main);
	last = ft_lstlast(main->lexer);
	if (last)
	{
		// printf("last exist\n");
		last->next = save;
	}
	else
		main->lexer = save;
	free(new);
	free(str_with_var);
}

void	contain_var(t_main *main)
{
	t_list		*index;
	t_list		*previous;
	t_list		*next;
	t_lexer		*tmp;
	t_lexer		*tmp2;
	// t_var_info	*var_info;
	int			i;

	i = 1;
	// ft_bzero(&var_info, sizeof(t_var_info));
	// var_info->previous = NULL;
	index = main->lexer;
	previous = NULL;
	// var_info = malloc(sizeof(t_var_info));
	// if (!var_info)
	// 	quit_prog("var_info malloc creation", main);
	while (index!= NULL)
	{
		tmp = index->content;
		if (tmp->type == VAR_ENV)
		{
			if (previous)
			{
				tmp2 = previous->content;
				if ((tmp2->type == REDIR_IN || tmp2->type == REDIR_OUT
					|| tmp2->type == APP_REDIR_OUT)
					&& verif_redirection_var(tmp, previous, main) == -1)
					return ;
			}
			// next = index->next;
			update_lst(previous, index, main);
			// printf("i = %d\n", i);
			contain_var(main);
			return ;
			// var_info->i_lst = i;
			// var_info->value = ft_strdup_no_list(tmp->value);
			// if (i == 1)
			// {
			// 	next = index->next;
			// 	free_lexer(index);
			// 	main->lexer = main->lexer->next;
			// }
			// else
			// {
			// printf("contain_var : i = %d, tmp->value = %s\n", i, tmp->value);
			// 	next = index->next;
			// 	free_lexer(index);
			// 	var_info->previous->next = next;
			// 	// (*var_info->previous)->next = next;
			// }
			// return (var_info);
			// // return (previous)
		}
		previous = index;
		// var_info->previous = index;
		// var_info->previous = &index;
		index = index->next;
		i++;
	}
	// free(var_info);
	// return (NULL);
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
		// print_lexer(main);
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
	// contain_var(main);
	// define_text_types(main);
	// // print_lexer(main);
	// fill_struct(param, main);
	print_struct_cmd(*param_lst);
}