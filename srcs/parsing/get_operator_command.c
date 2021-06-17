#include "minishell.h"

void	print_prompt()
{
	printf("\033[32m\033[1mbash_des_freros$ \033[0m");
}

void	get_operator_command(t_main *main)
{
	int		ret;
	t_list	*new_elem;
	char	*new_line;

	print_prompt();
	ret = get_next_line(0, &main->line);
	if (ret == -1)
	{
		free(main->line);
		quit_prog("Error read operator command\n", main);
	}
	new_line = ft_strdup(&main->free, main->line);
	new_elem = ft_calloc_lst(&main->free, 1, sizeof(t_list));
	new_elem->content = new_line;
	ft_lstadd_front(&main->histo, new_elem);
}