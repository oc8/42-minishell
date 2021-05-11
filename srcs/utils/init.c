/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odroz-ba <odroz-ba@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:37:02 by odroz-ba          #+#    #+#             */
/*   Updated: 2021/05/11 18:41:37 by odroz-ba         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_fct(t_main *main)
{
	main->cmd_fct[0].fct = &cmd_echo;
	main->cmd_fct[1].fct = &cmd_pwd;
	main->cmd_fct[2].fct = &cmd_cd;
	main->cmd_fct[3].fct = &cmd_env;
	main->cmd_fct[4].fct = &cmd_export;
	main->cmd_fct[5].fct = &cmd_unset;
	main->cmd_fct[6].fct = &cmd_exit;
	main->cmd_fct[0].cmd = ECHO_CMD;
	main->cmd_fct[1].cmd = PWD_CMD;
	main->cmd_fct[2].cmd = CD_CMD;
	main->cmd_fct[3].cmd = ENV_CMD;
	main->cmd_fct[4].cmd = EXPORT_CMD;
	main->cmd_fct[5].cmd = UNSET_CMD;
	main->cmd_fct[6].cmd = EXIT_CMD;
}
