/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:11:28 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/25 18:42:25 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_histo(t_main *main)
{
	t_list *tmp;

	tmp = main->histo;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	print_lexer(t_main *main)
{
	t_lexer	*tmp;
	t_list	*iter;
	
	printf("Lexer , size = %d : \n", ft_lstsize(main->lexer));
	iter = main->lexer;
	while (iter != NULL)
	{
		tmp = iter->content;
		printf("Value = |%s|\n", tmp->value);
		if (tmp->type == COMMAND)
			printf("Type = COMMAND\n");
		else if (tmp->type == ARGUMENT)
			printf("Type = ARGUMENT\n");
		else if (tmp->type == NEW_COMMAND)
			printf("Type = NEW_COMMAND\n");
		else if (tmp->type == FILE_NAME)
			printf("Type = FILE_NAME\n");
		else if (tmp->type == REDIRECTION)
			printf("Type = REDIRECTION\n");
		else if (tmp->type == TO_DEFINE)
			printf("Type = TO_DEFINE\n");
		else if (tmp->type == VAR_ENV)
			printf("Type = VAR_ENV\n");
		printf("\n");
		iter = iter->next;
	}
}

void	print_env(t_main *main)
{
	size_t	i;

	i = -1;
	while (main->env[++i] != NULL)
		printf("%s\n", main->env[i]);
}

void	create_cmd(t_main *main)
{
	t_param_cmd	param;
	t_list		*save;
	t_list		*tmp_lst;
	t_lexer		*tmp_lex;

	ft_bzero(&param, sizeof(t_param_cmd));
	while (main->lexer != NULL)
	{
		save = main->lexer;
		tmp_lex = save->content;
		while (save != NULL && tmp_lex->type != NEW_COMMAND && tmp_lex->type != PIPE)
			save = save->next;
		if (tmp_lex->type == NEW_COMMAND || tmp_lex->type == PIPE)
		{
			if (tmp_lex->type == PIPE)
				param.pipe = 1;
			tmp_lst = save;
			save = save->next;
			tmp_lst->next = NULL;
		}
		// else if (save == NULL)
		// 	save = main->lexer;
		create_param_cmd(&param, main);
		ft_lstclear(&main->lexer, free_lexer);
		if (save != NULL)
			main->lexer = save;
		// cmd_exec(&param, main);
	}
}

void	loop(t_main *main)
{
	while (ft_strncmp_minishell(main->line, "exit", 5))
	{
		if (main->line != NULL)
			free(main->line);
		get_operator_command(main);
		tokenization(main);
		print_lexer(main);
		// create_cmd(main);
		if(main->lexer != NULL)
			ft_lstclear(&main->lexer, free_lexer);
	}
}

char	**cpy_env(char *env[], t_main *main)
{
	char	**rs;
	size_t	i;
	size_t	len;

	len = ft_doublelen((const void **)env) + 1;
	main->nbr_env = len - 1;
	rs = ft_calloc_lst(&main->free, len, sizeof(char *));
	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]) + 1;
		rs[i] = ft_calloc_lst(&main->free, len, sizeof(char));
		ft_strlcpy(rs[i], env[i], len);
		// printf("%s | %s : %zu\n", env[i], rs[i], len);
		i++;
	}
	rs[i] = 0;
	return (rs);
}

int	main(int argc, char *argv[], char *env[])
{
	t_main	main;

	(void)argv;
	setbuf(stdout, NULL);
	if (argc != 1)
		quit_prog("minishell as to be launch without args\n", &main);
	ft_bzero(&main, sizeof(t_main));
	main.env = cpy_env(env, &main);
	init_cmd_fct(&main);
	loop(&main);
	print_histo(&main);
	free(main.line);
	ft_lstclear(&main.free, free);
	return (0);
}
