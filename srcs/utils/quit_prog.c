#include "minishell.h"

void	free_all(t_main *main)
{
	// if (main->histo != NULL)
	// 	ft_lstclear(&main->histo, free);
	if (main->line)
		free(main->line);
	if (main->lexer != NULL)
		ft_lstclear(&main->lexer, free);
	if (main->free)
		ft_lstclear(&main->free, free);

	// if (main->env)
	// 	ft_freedoublestr(&main->env);
	// if (main->home_path)
	// 	free(main->home_path);
	if (main->file)
		close(main->file);
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
