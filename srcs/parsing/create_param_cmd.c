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
	if (!str_with_var)
		quit_prog("strdup of update_lst create_param_cmd", main);
	free_lexer(to_del->content);
	free(to_del);
	if (previous == NULL)
		main->lexer = NULL;
	else
		previous->next = NULL;
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

void	create_param_cmd(t_param_cmd *param, t_main *main)
{
	// t_var_info	*var_info;
	// char		*to_treat;
	
	contain_var(main);
	// to_treat = NULL;
	// var_info = contain_var(main);
	// while (var_info != NULL)
	// {
		// remplace_var_value(&to_treat, var_info->value, main);
	// 	printf("to_treat = %s\n", to_treat);
	// 	if (to_treat)
	// 		tokenization(to_treat, var_info->i_lst, main);
	// 	free(var_info->value);
	// 	free(var_info);
	// 	free(to_treat);
	// 	var_info = contain_var(main);
	// }
	define_text_types(main);
	// print_lexer(main);
	fill_struct(param, main);
	// print_struct_cmd(param);
}