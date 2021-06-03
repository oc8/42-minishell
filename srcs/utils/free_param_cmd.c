/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_param_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:10:40 by tdayde            #+#    #+#             */
/*   Updated: 2021/05/28 15:22:14 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirection(void *to_free)
{
	t_redir	*redir;

	redir = (t_redir*)to_free;
	free(redir->file);
	free(redir);
}

void	free_param_cmd(t_param_cmd *param)
{
	int	i;

	if (param->cmd)	// METTRE DOUBLESTR FREE !!!!!
	{
		i = -1;
		while (param->cmd[++i])
			free(param->cmd[i]);
		free(param->cmd);
		param->cmd = NULL;
	}
	ft_lstclear(&param->redir, free_redirection);
}