#include "minishell.h"

static void	cpy_prompt(int i, int j, char *current_dir, char *cwd)
{
	j = i - j;
	current_dir[--j] = '\0';
	while (--i && j)
	{
		j--;
		if (cwd[i] == '/')
			break ;
		current_dir[j] = cwd[i];
	}
	if (!i && !ft_strlen(current_dir))
		current_dir[j] = '/';
}

static char	*prompt(char *cwd, t_main *main)
{
	char	*current_dir;
	char	*prompt;
	char	*color;
	size_t	i;
	size_t	j;

	i = ft_strlen(cwd);
	j = i;
	while (--j)
		if (cwd[j] == '/')
			break ;
	current_dir = ft_calloc(i - j, sizeof(char));
	if (!current_dir)
		quit_prog("malloc() error", main);
	cpy_prompt(i, j, current_dir, cwd);
	color = ft_strjoin("\033[32m\033[1m", current_dir);
	free(current_dir);
	prompt = ft_strjoin(color, "$> \033[0m");
	free(color);
	return (prompt);
}

char	*location(t_main *main)
{
	char	cwd[PWD_MAX_SIZE];

	if (main->pwd)
	{
		ft_lstdel_content(&main->free, main->pwd);
		free(main->pwd);
		main->pwd = 0;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup_no_list("."));
	main->pwd = ft_calloc_lst(&main->free, ft_strlen(cwd) + 1, sizeof(char));
	ft_strlcpy(main->pwd, cwd, -1);
	return (prompt(cwd, main));
}
