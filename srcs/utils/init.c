#include "minishell.h"

void	init_cmd_fct(t_main *main)
{
	main->cmd_fct[0].build_in = &cmd_echo;
	main->cmd_fct[1].build_in = &cmd_pwd;
	main->cmd_fct[2].build_in = &cmd_cd;
	main->cmd_fct[3].build_in = &cmd_env;
	main->cmd_fct[4].build_in = &cmd_export;
	main->cmd_fct[5].build_in = &cmd_unset;
	main->cmd_fct[6].build_in = &cmd_exit;
	main->cmd_fct[0].name = strdup_secure(&main->free, "echo", quit_prog, main);
	main->cmd_fct[1].name = strdup_secure(&main->free, "pwd", quit_prog, main);
	main->cmd_fct[2].name = strdup_secure(&main->free, "cd", quit_prog, main);
	main->cmd_fct[3].name = strdup_secure(&main->free, "env", quit_prog, main);
	main->cmd_fct[4].name = strdup_secure(&main->free, "export", quit_prog, \
			main);
	main->cmd_fct[5].name = strdup_secure(&main->free, "unset", quit_prog, \
			main);
	main->cmd_fct[6].name = strdup_secure(&main->free, "exit", quit_prog, main);
}
