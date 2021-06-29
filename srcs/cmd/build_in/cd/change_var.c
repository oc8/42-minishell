#include "minishell.h"

static void	save_pwd(t_main *main)
{
	char	cwd[PWD_MAX_SIZE];

	if (main->oldpwd)
	{
		free(main->oldpwd);
		main->oldpwd = 0;
	}
	if (main->pwd)
		main->oldpwd = main->pwd;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	main->pwd = ft_calloc_lst(&main->free, ft_strlen(cwd) + 1, sizeof(char));
	ft_strlcpy(main->pwd, cwd, -1);
}

void	reset_pwd_var(t_main *main)
{
	int		i;
	int		j;
	char	**var;
	char	cwd[PWD_MAX_SIZE];

	save_pwd(main);
	i = var_defined("OLDPWD", main);
	if (i == -1)
		return ;
	j = var_defined("PWD", main);
	if (j == -1)
		return ;
	var = split_var(main->env[j], main);
	edit_var(var[1], i, main);
	ft_freedoublestr(&var);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cmd_error("cd", strerror(errno), 0, 0);
	edit_var(cwd, j, main);
}
