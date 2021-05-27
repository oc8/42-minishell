/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 20:52:12 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/27 21:33:00 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_struct_cmd(t_param_cmd *param)
{
	int	i;
	
	i = 0;
	printf("\033[33m\033[1m--> STRUCTURE FOR COMMAND <--\n\033[0m");
	if (param->cmd)
	{
		printf("COMMAND   : | %s |\n", param->cmd[i]);
		printf("ARGUMENTS : | ");
		while (param->cmd[++i])
			printf("%s ", param->cmd[i]);
		printf("|\n");
	}
	if (param->pipe == 1)
		printf("PIPE      : YES\n");
	else if (param->pipe == 0)
		printf("PIPE      : NO\n");
	printf("\n");
}