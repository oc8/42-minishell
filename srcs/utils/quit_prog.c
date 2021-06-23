#include "minishell.h"

void	free_all(t_main *main)
{
	if (main->lexer != NULL)
		ft_lstclear(&main->lexer, free);
	// if (main->histo != NULL)
	// 	ft_lstclear(&main->histo, free);
	if (main->file)
		close(main->file);
	ft_lstclear(&main->free, free);
}

void	quit_prog(char *str, t_main *main)
{
	if (str)
		printf("Error : %s\n", str);
	free_all(main);
	if (str)
		exit(1);
	exit(0);
}
